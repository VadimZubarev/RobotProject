#pragma once
#include "Translator.h"
#include <cmath>
# define M_PI           3.14159265358979323846

class Detector : Translator
{
    Mat frame_HSV, frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue, frame_threshold_Green;
    //for red
    /*int hminR = 169, sminR = 100, vminR = 20;
    int hmaxR = 189, smaxR = 255, vmaxR = 255;*/
    Scalar minRedHSV = Scalar(169, 100, 20);
    Scalar maxRedHSV = Scalar(189, 255, 255);
    //for blue
    Scalar minBlueHSV = Scalar(89, 163, 59);
    Scalar maxBlueHSV = Scalar(111, 255, 215);
    /*int hminB = 89, sminB = 163, vminB = 59;
    int hmaxB = 111, smaxB = 255, vmaxB = 215;*/
    //for green
    Scalar minGreenHSV = Scalar(36, 0, 0);
    Scalar maxGreenHSV = Scalar(86, 255, 255);
    /*int hminG = 36, sminG = 0, vminG = 0;
    int hmaxG = 86, smaxG = 255, vmaxG = 255;*/
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect rect_front;
    Rect rect_rear;
    Rect rect_target;
    Rect rect_home;

    Point robotCenter;
    Point targetCenter;
    Point homeCenter;

    int angleBot;
    int angleTarget;
    int angleHome;


public:
    Detector() {
        while (true) {
            getFrame();
            findObject(frame);
            drawContours(frame, detect_rect(minRedHSV, maxRedHSV));
            drawContours(frame, detect_rect(minBlueHSV, maxBlueHSV));
            showMesures();
            /*getContours(frame_threshold_Red, frame);
            getContours(frame_threshold_Blue, frame);
            getContours(frame_threshold_Green, frame);*/
            showObjects();
        }
    }
    void showObjects();
    void findObject(Mat& frame);
    void getContours(Mat imgDil, Mat img);
    Point find_rect_centre(Rect r);
    Point find_centre_beetwen_point(Point p1, Point p2);
    int calc_distance_between_point(Point p_a, Point p_b);
    int distance_beetween_centroids(Point a, Point b);
    Rect detect_rect(Scalar min, Scalar max);
    void drawContours(Mat img, Rect r);

    Point getRobotCentre();
    Point getTargetCentre();
    Point getHomeCentre();
    void showMesures();

    int calc_angle_beetwen_point(Point p_a, Point p_b);
    int getAngleBot();
    int getAngleToTarget();
    int getAngleToHome();
};
