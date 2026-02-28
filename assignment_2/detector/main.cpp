#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/calib3d.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace cv;
using namespace std;

Scalar lower_green(35, 70, 70);
Scalar upper_green(85, 255, 255);

const double REAL_DIAMETER_MM = 17.0;

const Mat cameramatrix = (Mat_<double>(3,3) << 1284.547433507284, 0.0, 651.7508235222139, 0.0, 1284.2364120767988, 526.5637803861928, 0.0, 0.0, 1.0);

const Mat distcoeffs = (Mat_<double>(1,5) << -0.37358321087789575, 0.17992488578084675, -0.0003940895801771612, -0.0007097534681170694, 0.0);

int main(){
    vector<string> images = {"/home/kkk/Desktop/assessment_winter_2026/assignment_2/detector/imgs/test1.jpg","/home/kkk/Desktop/assessment_winter_2026/assignment_2/detector/imgs/test2.jpg"};

    for(const string& img_path : images){
        Mat img = imread(img_path);
        if(img.empty()){
            cout << "Cannot read" << endl;
            continue;
        }


        Mat hsv,mask;
        cvtColor(img,hsv,COLOR_BGR2HSV);
        inRange(hsv,lower_green,upper_green,mask);

        Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
        morphologyEx(mask,mask,MORPH_OPEN,kernel);
        erode(mask, mask, kernel, Point(-1,-1),2);
        dilate(mask, mask, kernel, Point(-1,-1), 1);

        vector<Vec3f> circles;
        HoughCircles(mask, circles, HOUGH_GRADIENT, 1.2, 28, 50, 20, 15, 80);
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        
        Mat result = img.clone();

        for(size_t i = 0; i < circles.size(); ++i){
            Point2f center(cvRound(circles[i][0]),cvRound(circles[i][1]));

            float radius = circles[i][2];

            if(radius < 15) continue;

            circle(result,center,(int)radius,Scalar(0,255,0),4);

        
            double r = REAL_DIAMETER_MM / 2.0;

            vector<Point3f> object_points;
            object_points.push_back(Point3f(0, 0, 0));

            for(int k = 0; k < 11; ++k){
                double angle = k * (2 * CV_PI / 11);
                object_points.push_back(Point3f(r * cos(angle), r * sin(angle), 0));
            }

            vector<Point2f> image_points;
            image_points.push_back(center);
            for(int n = 0; n < 11; ++n){
                double angle = n * (2 * CV_PI / 11);
                float dx = radius * cos(angle);
                float dy = radius * sin(angle);

                image_points.push_back(Point2f(center.x + dx, center.y + dy));
            }

            Mat rvec,tvec;
            bool success = solvePnPRansac(object_points, image_points,cameramatrix,distcoeffs,rvec,tvec,false,200,1.5);

            if(success){
                double distance_mm = tvec.at<double>(2,0);
                double distance_m = distance_mm / 1000.0;
                ostringstream oss;
                oss << fixed << setprecision(5) << distance_m << " m";
                string dist_text = oss.str();
                putText(result, dist_text,Point(center.x + 10, center.y + 35),FONT_HERSHEY_SIMPLEX,0.75,Scalar(0,255,255),2);

                cout << img_path << distance_m << " m" << endl;
            }
            else{
                cout << img_path << "faild" << endl;
            }
    }

    string output_path = "/home/kkk/Desktop/assessment_winter_2026/assignment_2/detector/imgs/result_" + img_path.substr(img_path.find_last_of('/')+1);
        imwrite(output_path, result);
        cout << "Finished " << output_path << endl;

}
return 0;

}