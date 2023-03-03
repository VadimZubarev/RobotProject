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
    vector<vector<Point>> contours1;
    vector<vector<Point>> contours2;
    vector<Vec4i> hierarchy1;
    vector<Vec4i> hierarchy2;

public:
    Detector() {
        cap.open(0);
        while (true) {
            getFrame();
            findObject(frame);
            getContours(frame_threshold_Red, frame);
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
        imshow("Image ThresholdRed", frame_threshold_Red);
        imshow("Image ThresholdRedBlue", frame_threshold_Red_And_Blue);
        waitKey(1);
    }
    /*void getContours()
    {
        findContours(frame_threshold_Red, contours1, hierarchy1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        findContours(frame_threshold_Blue, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(frame, contours1, -1, Scalar(240, 99, 47), 3);
        drawContours(frame, contours2, -1, Scalar(1, 88, 85), 3);
    }*/
    void getContours(Mat imgDil, Mat img)
    {
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        Point pnt(0, 0);
        findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(img, contours, -1, Scalar(255, 0, 150), 3);
        for (int i = 0; i < contours.size(); i++)
        {
            vector<vector<Point>> conPoly(contours.size());
            vector<Rect> boundRect(contours.size());
            string objectType;
            int area = contourArea(contours[i]);
            if (area > 50000)
            {
                float peri = arcLength(contours[i], true);
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
                drawContours(img, conPoly, i, Scalar(255, 0, 150),2);
                boundRect[i] = boundingRect(conPoly[i]);
                rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 150, 0), 3);
                pnt.x = boundRect[i].x + boundRect[i].width / 2;
                pnt.y = boundRect[i].y + boundRect[i].height / 2;
                string center = to_string(pnt.x) + ";" + to_string(pnt.y);
                putText(img, center, { pnt.x, pnt.y }, FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 0), 2);
            }
        }
    }
};

int main()
{
    Detector robot;
    return 0;
}
