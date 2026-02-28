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

        
    }

return 0;

}