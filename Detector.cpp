#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "Translator.cpp"
#include <iostream>


using namespace cv;
using namespace std;

class Detector : Translator
{

    //Mat frame;
    Mat frame_HSV, frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue;
    //VideoCapture cap;
    //for red
    int hminR = 169, sminR = 100, vminR = 20;
    int hmaxR = 189, smaxR = 255, vmaxR = 255;
    //for blue
    int hminB = 89, sminB = 163, vminB = 59;
    int hmaxB = 111, smaxB = 255, vmaxB = 215;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    RotatedRect rect;


public:
    Detector() {
        while (true) {
            getFrame();
            //showFrames();
            findObject(frame);
            getContours(frame_threshold_Red, frame);
            getContours(frame_threshold_Blue, frame);
            showObjects();
        }
    }
    void showObjects()
    {
        imshow("Frame", frame);
        bitwise_or(frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue);
        //imshow("Image ThresholdRed", frame_threshold_Red);
        imshow("Image ThresholdRedBlue", frame_threshold_Red_And_Blue);
        waitKey(1);
    }
    void findObject(Mat& frame)
    {
        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
        inRange(frame_HSV, Scalar(hminR, sminR, vminR), Scalar(hmaxR, smaxR, vmaxR), frame_threshold_Red);
        inRange(frame_HSV, Scalar(hminB, sminB, vminB), Scalar(hmaxB, smaxB, vmaxB), frame_threshold_Blue);
    }
    void getContours(Mat imgDil, Mat img)
    {
        findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < (int)contours.size(); i++)
        {
            if (contourArea(contours[i]) > 500)
            {
                rectangle(img, boundingRect(contours[i]), Scalar(255, 0, 255), 3);
            }
        }
    }
};
