//
//  main.cpp
//  ObjFind
//
//  Created by Алан Савушкин on 06.03.17.
//  Copyright © 2017 Алан Савушкин. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace std;
using namespace cv;

void obj_find(Mat &image, Mat &temp);

int main(int argc, const char * argv[]) {
    
    if (argc != 2) {
        cout << "Use: " << argv[0] << "template_file" << endl;
        return -1;
    }
    Mat temp = imread(argv[1]);
    Mat frame;
    
    VideoCapture capture(0);
    if(!capture.isOpened()){
        cout << "Error: can't open camera" << endl;
        return -1;
    }
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 640);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 480);
    
    namedWindow("Template matching");
    while (1) {
        capture >> frame;
        flip(frame, frame, 1);
        obj_find1(frame, temp);
        imshow("Template matching", frame);
        if(waitKey(1) == 32){
                break;
        }
    }

    return 0;
}

void obj_find(Mat &image, Mat &temp){
    
    Mat res(Size(image.cols - temp.cols + 1, image.rows - temp.rows + 1), CV_32FC1);
    Point min_loc;
    matchTemplate(image, temp, res, 0);
    minMaxLoc(res,nullptr, nullptr, &min_loc);
    rectangle(image, min_loc, Point(min_loc.x + temp.cols, min_loc.y + temp.rows), Scalar(0, 0, 255));
    
}



