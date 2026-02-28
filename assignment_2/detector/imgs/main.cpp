#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/calib3d.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

Scalar lower_green(40, 80, 80);
Scalar upper_green(80, 255, 255);

const double REAL_DIAMETER_MM = 42.0;

const Mat cameramatrix = (Mat_<double>(3,3) << 1284.547433507284, 0.0, 651.7508235222139, 0.0, 1284.2364120767988, 526.5637803861928, 0.0, 0.0, 1.0);

const Mat distcoeffs = (Mat_<double>(1,5) << -0.37358321087789575, 0.17992488578084675, -0.0003940895801771612, -0.0007097534681170694, 0.0);

int main(){
    vector<string> images = {"imgs/test1.jpg","imgs/test2.jpg"};

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

         vector<vector<Point>>contours;
        findContours(mask,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

        Mat result = img.clone();
        for(size_t i = 0; i < contours.size(); ++i){
            double area = contourArea(contours[i]);
            if(area < 200) continue;

            Point2f center;
            float radius;
            minEnclosingCircle(contours[i],center,radius);

            if(radius < 15) continue;

            circle(result,center,(int)radius,Scalar(0,255,0),2);
            circle(result,center,4,Scalar(0,0,255),-1);

            string text = "r="+to_string((int)radius);
            putText(result,text,Point(center.x+10,center.y-10),FONT_HERSHEY_SIMPLEX,0.7,Scalar(0,255,255),2);
        
            double r = REAL_DIAMETER_MM / 2.0;

            vector<Point3f> object_points = {
                Point3f(0, 0, 0),
                Point3f(r, 0, 0),
                Point3f(0, r, 0),
                Point3f(0, 0, r)
            };

            vector<Point2f> image_points = {
                center,
                Point2f(center.x + radius,center.y),
                Point2f(center.x,center.y-radius),
                Point2f(center.x - radius,center.y)
            };

            Mat rvec,tvec;
            bool pnp_success = solvePnP(object_points, image_points,cameramatrix,distcoeffs,rvec,tvec);

            if(pnp_success){
                double distance_mm = tvec.at<double>(2,0);

                string dist_text = "dist(PnP)= " + to_string((int)distance_mm) + "mm";putText(result, dist_text,Point(center.x + 10, center.y + 30),FONT_HERSHEY_SIMPLEX,0.7,Scalar(0,255,255),2);

                cout << img_path << distance_mm << "mm" << endl;
            }
            else{
                cout << img_path << "faild" << endl;
            }
    }
    
    string output_path = "imgs/result_" + img_path.substr(img_path.find_last_of('/')+1);
        imwrite(output_path, result);
        cout << "Finished" << output_path << endl;

}
return 0;

}