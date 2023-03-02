#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace cv;
using namespace std;

class Detector
{
    Mat frame, frame_HSV, frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue, frame_threshold_Blue_Gray;
    VideoCapture cap;
    //for red
    int hminR = 169, sminR = 100, vminR = 20;
    int hmaxR = 189, smaxR = 255, vmaxR = 255;
    //for blue
    int hminB = 105, sminB = 100, vminB = 20;
    int hmaxB = 130, smaxB = 255, vmaxB = 255;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

public:
    Detector() {
        cap.open(0);
        while (true) {
            getFrame();
            findObject(frame);
            showFrames();
        }
    }
    void getFrame()
    {

        cap >> frame;
        if (frame.empty())
        {
            throw;
        }
        this->frame = frame;
        this->frame_HSV = frame_HSV;
    }
    void findObject(Mat& frame)
    {
        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
        inRange(frame_HSV, Scalar(hminR, sminR, vminR), Scalar(hmaxR, smaxR, vmaxR), frame_threshold_Red);
        inRange(frame_HSV, Scalar(hminB, sminB, vminB), Scalar(hmaxB, smaxB, vmaxB), frame_threshold_Blue);
    }
    void showFrames()
    {
        imshow("Frame", frame);
        bitwise_or(frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue);
        //imshow("Image HSV", frame_HSV);
        imshow("Image ThresholdRed", frame_threshold_Red);
        imshow("Image ThresholdRedBlue", frame_threshold_Red_And_Blue);
        waitKey(1);
    }
};

int main()
{
    Detector robot;
    return 0;
}
