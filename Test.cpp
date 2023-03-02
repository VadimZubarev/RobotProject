//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;

////// Images //////
//int main() {
//    string path = "donut.jpg";
//    Mat img = imread(path);
//    imshow("Image", img);
//    waitKey(0);
//    return 0;
//}

////// Videos //////
//int main() {
//    string path = "TestVid.mp4";
//    VideoCapture cap(path);
//    Mat img;
//    while (true)
//    {
//        cap.read(img);
//        imshow("Image", img);
//        waitKey(20);
//    }
//    
//    return 0;
//}

////// Webcam //////
//int main() {
//    VideoCapture cap(0);
//    Mat img;
//    while (true)
//    {
//        cap.read(img);
//        imshow("Image", img);
//        waitKey(1);
//    }
//
//    return 0;
//}

////// Images //////
//int hmin = 110, smin = 64, vmin = 135; for red
//int hmax = 179, smax = 255, vmax = 255;
//Mat imgHSV, mask, img;
//int hmin = 110, smin = 64, vmin = 135;
//int hmax = 179, smax = 255, vmax = 255;
//void main() {
//    string path = "redBlue.jpg";
//    Mat img = imread(path);
//    cvtColor(img, imgHSV, COLOR_BGR2HSV);
//    namedWindow ("TrackBars", (640, 200));
//    
//    createTrackbar("Hue Min", "TrackBars", &hmin, 179);
//    createTrackbar("Hue Max", "TrackBars", &hmax, 179);
//    createTrackbar("Sat Min", "TrackBars", &smin, 255);
//    createTrackbar("Sat Max", "TrackBars", &smax, 255);
//    createTrackbar("Val Min", "TrackBars", &vmin, 255);
//    createTrackbar("Val Max", "TrackBars", &vmax, 255);
//    while (true)
//    {
//        Scalar lower(hmin, smin, vmin);
//        Scalar upper(hmax, smax, vmax);
//        inRange(imgHSV, lower, upper, mask);
//        imshow("Image", img);
//        imshow("Image HSV", imgHSV);
//        imshow("Image Mask", mask);
//        waitKey(1);
//    }
//}

//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/videoio.hpp"
//#include <iostream>
//using namespace cv;
//
//
//const int max_value_H = 360 / 2;
//const int max_value = 255;
//const String window_capture_name = "Video Capture";
//const String window_detection_name = "Object Detection";
//int low_H = 0, low_S = 0, low_V = 0;
//int high_H = max_value_H, high_S = max_value, high_V = max_value;
//static void on_low_H_thresh_trackbar(int, void*)
//{
//    low_H = min(high_H - 1, low_H);
//    setTrackbarPos("Low H", window_detection_name, low_H);
//}
//static void on_high_H_thresh_trackbar(int, void*)
//{
//    high_H = max(high_H, low_H + 1);
//    setTrackbarPos("High H", window_detection_name, high_H);
//}
//static void on_low_S_thresh_trackbar(int, void*)
//{
//    low_S = min(high_S - 1, low_S);
//    setTrackbarPos("Low S", window_detection_name, low_S);
//}
//static void on_high_S_thresh_trackbar(int, void*)
//{
//    high_S = max(high_S, low_S + 1);
//    setTrackbarPos("High S", window_detection_name, high_S);
//}
//static void on_low_V_thresh_trackbar(int, void*)
//{
//    low_V = min(high_V - 1, low_V);
//    setTrackbarPos("Low V", window_detection_name, low_V);
//}
//static void on_high_V_thresh_trackbar(int, void*)
//{
//    high_V = max(high_V, low_V + 1);
//    setTrackbarPos("High V", window_detection_name, high_V);
//}
//int main()
//{
//    VideoCapture cap(0);
//    namedWindow(window_capture_name);
//    namedWindow(window_detection_name);
//    // Trackbars to set thresholds for HSV values
//    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
//    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
//    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
//    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
//    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
//    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
//    Mat frame, frame_HSV, frame_threshold;
//    while (true) {
//        cap >> frame;
//        if (frame.empty())
//        {
//            break;
//        }
//        // Convert from BGR to HSV colorspace
//        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
//        // Detect the object based on HSV Range Values
//        inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
//        // Show the frames
//        imshow(window_capture_name, frame);
//        imshow(window_detection_name, frame_threshold);
//        char key = (char)waitKey(30);
//        if (key == 'q' || key == 27)
//        {
//            break;
//        }
//    }
//    return 0;
//}

//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/videoio.hpp"
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//class Detection: public Mat
//{
//    Mat frame, frame_HSV, frame_threshold;
//    VideoCapture cap; 
//    int low_H = 0, low_S = 0, low_V = 0;
//    int high_H = 360/2, high_S = 255, high_V = 255;
//    const String window_capture_name = "Video Capture";
//    const String window_detection_name = "Object Detection";
//    //int hmin = 110, smin = 64, vmin = 135; for red
//    //    int hmax = 179, smax = 255, vmax = 255;
//    
//public:
//    Detection(int cam) {
//        cap.open(0);
//    }
//    Detection(Mat frame, Mat frame_HSV) {
//        cvtColor(frame, frame_HSV, ColorConversionCodes::COLOR_BGR2HSV);
//    }
//    Detection(Mat frame_HSV) {
//        inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
//    }
//    Detection(string winCap, Mat frame) {
//        imshow(window_capture_name, frame);
//    }
//    
//};
//
////const int max_value_H = 360 / 2;
////const int max_value = 255;
//const String window_capture_name = "Video Capture";
//const String window_detection_name = "Object Detection";
////int low_H = 0, low_S = 0, low_V = 0;
////int high_H = max_value_H, high_S = max_value, high_V = max_value;
//static void on_low_H_thresh_trackbar(int, void*)
//{
//    low_H = min(high_H - 1, low_H);
//    setTrackbarPos("Low H", window_detection_name, low_H);
//}
//static void on_high_H_thresh_trackbar(int, void*)
//{
//    high_H = max(high_H, low_H + 1);
//    setTrackbarPos("High H", window_detection_name, high_H);
//}
//static void on_low_S_thresh_trackbar(int, void*)
//{
//    low_S = min(high_S - 1, low_S);
//    setTrackbarPos("Low S", window_detection_name, low_S);
//}
//static void on_high_S_thresh_trackbar(int, void*)
//{
//    high_S = max(high_S, low_S + 1);
//    setTrackbarPos("High S", window_detection_name, high_S);
//}
//static void on_low_V_thresh_trackbar(int, void*)
//{
//    low_V = min(high_V - 1, low_V);
//    setTrackbarPos("Low V", window_detection_name, low_V);
//}
//static void on_high_V_thresh_trackbar(int, void*)
//{
//    high_V = max(high_V, low_V + 1);
//    setTrackbarPos("High V", window_detection_name, high_V);
//}
//int main()
//{
//    
//    namedWindow(window_capture_name);
//    namedWindow(window_detection_name);
//    // Trackbars to set thresholds for HSV values
//    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
//    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
//    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
//    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
//    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
//    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
//    
//    while (true) {
//        cap >> frame;
//        if (frame.empty())
//        {
//            break;
//        }
//        // Convert from BGR to HSV colorspace
//        //cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
//        // Detect the object based on HSV Range Values
//        //inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
//        // Show the frames
//        /*imshow(window_capture_name, frame);
//        imshow(window_detection_name, frame_threshold);*/
//        char key = (char)waitKey(30);
//        if (key == 'q' || key == 27)
//        {
//            break;
//        }
//    }
//    return 0;
//}

//
//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/videoio.hpp"
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//class Detector
//{
//    Mat frame, frame_HSV, frame_threshold_Red, frame_threshold_Blue;
//    VideoCapture cap;
//    //for red
//    int hminR = 169, sminR = 100, vminR = 100;
//    int hmaxR = 189, smaxR = 255, vmaxR = 255; 
//
//
//public:
//    Detector() {
//
//        cap.open(0);
//        namedWindow("TrackBarsRed", (640, 200));
//        createTrackbar("Hue Min", "TrackBarsRed", &hminR, 179);
//        createTrackbar("Hue Max", "TrackBarsRed", &hmaxR, 179);
//        createTrackbar("Sat Min", "TrackBarsRed", &sminR, 255);
//        createTrackbar("Sat Max", "TrackBarsRed", &smaxR, 255);
//        createTrackbar("Val Min", "TrackBarsRed", &vminR, 255);
//        createTrackbar("Val Max", "TrackBarsRed", &vmaxR, 255);
//        
//        while (true) {
//            getFrame();
//            findObject(frame);
//            showFrames();
//        }
//    }
//    void getFrame()
//    {
//            
//            cap >> frame;
//            if (frame.empty())
//            {
//                throw;
//            }    
//            this->frame = frame;
//            this->frame_HSV = frame_HSV;
//    }
//    void findObject(Mat&frame)
//    {
//        cvtColor(frame, frame_HSV, ColorConversionCodes::COLOR_BGR2HSV);
//        inRange(frame_HSV, Scalar(hminR, sminR, vminR), Scalar(hmaxR, smaxR, vmaxR), frame_threshold_Red);
//    }
//    void showFrames()
//    {
//        imshow("Frame", frame);
//        //imshow("Image HSV", frame_HSV);
//        imshow("Image ThresholdRed", frame_threshold_Red);
//        waitKey(1);
//    }
//    void Color()
//    {
//        int hmin = 155, smin = 25, vmin = 0;
//        int hmax = 179, smax = 255, vmax = 255;
//    }
//};
//
//int main()
//{
//    Detector robot;
//    return 0;
//}

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

//void getContours(Mat frameWithFigures, Mat drawOnFrame)
//{
//    findContours(frameWithFigures, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
//    drawContours(drawOnFrame, contours, -1, Scalar(179, 0, 255), 2);
//}
/*namedWindow("TrackBarsRed", (640, 200));*/
        /*createTrackbar("Hue Min", "TrackBarsRed", &hminR, 179);
        createTrackbar("Hue Max", "TrackBarsRed", &hmaxR, 179);
        createTrackbar("Sat Min", "TrackBarsRed", &sminR, 255);
        createTrackbar("Sat Max", "TrackBarsRed", &smaxR, 255);
        createTrackbar("Val Min", "TrackBarsRed", &vminR, 255);
        createTrackbar("Val Max", "TrackBarsRed", &vmaxR, 255);*/