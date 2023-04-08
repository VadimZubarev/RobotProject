#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>


using namespace cv;
using namespace std;

class Translator
{
    VideoCapture cap;
public:
    Mat frame;
    Translator() {
        cap.open(0);
        getFrame();
        showFrames();
    }
    void getFrame()
    {
        cap >> frame;
        if (frame.empty())
        {
            throw;
        }
        this->frame = frame;
    }
    void showFrames()
    {
        imshow("Frame", frame);
        waitKey(1);
    }
};
