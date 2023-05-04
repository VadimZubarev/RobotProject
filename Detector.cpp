#pragma once
#include "Detector.h"
#include "Translator.h"


void Detector::showObjects()
{
    imshow("Frame", frame);
    bitwise_or(frame_threshold_Red, frame_threshold_Blue, frame_threshold_Red_And_Blue);
    imshow("Image ThresholdRedBlue", frame_threshold_Red_And_Blue);
    imshow("Image ThresholdGreen", frame_threshold_Green);
    waitKey(1);
}
void Detector::findObject(Mat& frame)
{
    cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
    inRange(frame_HSV, minRedHSV, maxRedHSV, frame_threshold_Red);
    inRange(frame_HSV, minBlueHSV, maxBlueHSV, frame_threshold_Blue);
    inRange(frame_HSV, minGreenHSV, maxGreenHSV, frame_threshold_Green);
}
//void Detector::getContours(Mat imgDil, Mat img)
//{
//    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    for (int i = 0; i < (int)contours.size(); i++)
//    {
//        if (contourArea(contours[i]) > 1000)
//        {
//            rectangle(img, boundingRect(contours[i]), Scalar(255, 0, 255), 3);
//        }
//    }
//}

Point Detector::find_rect_centre(Rect r) 
{
    int x = r.x + (r.width / 2);
    int y = r.y + (r.height / 2);
    return Point(x, y);
}

Point Detector::find_centre_beetwen_point(Point p1, Point p2) 
{
    int x = (p1.x + p2.x) / 2;
    int y = (p1.y + p2.y) / 2;
    return Point(x, y);
}

int Detector::calc_distance_between_point(Point p_a, Point p_b) 
{
    return sqrt((p_b.x - p_a.x) * (p_b.x - p_a.x) + (p_b.y - p_a.y) * (p_b.y - p_a.y));
}

int Detector::distance_beetween_centroids(Point a, Point b) 
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}


Rect Detector::detect_rect(Scalar min, Scalar max) 
{
    vector<Mat> stickers;
    Mat image_hsv;
    vector<vector<Point>> contours;
    cvtColor(frame, image_hsv, COLOR_BGR2HSV);
    Mat tmp_img(frame.size(), CV_8U);
    inRange(image_hsv, Scalar(min), max, tmp_img);
    dilate(tmp_img, tmp_img, Mat(), Point(-1, -1), 3);
    erode(tmp_img, tmp_img, Mat(), Point(-1, -1), 1);
    findContours(tmp_img, contours, 0, 1);

    Rect max_rect(0, 0, 0, 0);
    for (uint i = 0; i < contours.size(); i++) 
    {
        Mat sticker;
        Rect rect = boundingRect(contours[i]);
        if (rect.height * rect.width > max_rect.height * max_rect.width) 
        {
            max_rect = rect;
        }
    }
    //return max_rect;
    if (min == minRedHSV)
    {
        rect_front = max_rect;
        return max_rect;
    }
    else if (min == minBlueHSV)
    {
        rect_rear = max_rect;
        return max_rect;
    }
    else
    {
        rect_target = max_rect;
        return max_rect;
    }
}

void Detector::drawContours(Mat img, Rect r)
{
    rectangle(img, r, Scalar(255, 0, 255), 2);
}

Point Detector::getRobotCentre()
{
    Point front_center = find_rect_centre(rect_front);
    Point rear_center = find_rect_centre(rect_rear);
    robotCenter = find_centre_beetwen_point(front_center, rear_center);
    return robotCenter;
}

Point Detector::getTargetCentre()
{
    targetCenter = find_rect_centre(rect_target);
    return targetCenter;
}

Point Detector::getHomeCentre()
{
    homeCenter = find_rect_centre(rect_front);
    return homeCenter;
}

void Detector::showMesures()
{
    Point text_position(20, 35);
    double font_size = 1.0;
    Scalar font_Color(25, 50, 150);
    int font_weight = 2;
    // ------Наносим расстояние до цели-----
    putText(frame, to_string(calc_distance_between_point(getRobotCentre(), getHomeCentre())), text_position, FONT_HERSHEY_COMPLEX, font_size, font_Color, font_weight);
    text_position.x = 20;
    text_position.y = 75;
    putText(frame, to_string(getAngleToTarget()), text_position, FONT_HERSHEY_COMPLEX, font_size, font_Color, font_weight);
    text_position.x = 80;
    text_position.y = 55;
    putText(frame, "o", text_position, FONT_HERSHEY_COMPLEX, font_size-0.5, font_Color, font_weight-1);
    //imshow("tmp", frame);
}

int Detector::calc_angle_beetwen_point(Point p_a, Point p_b) {
    double gipoten = pow((p_b.x - p_a.x) * (p_b.x - p_a.x) + (p_b.y - p_a.y) * (p_b.y - p_a.y), 2);
    double deg = atan2((p_b.x - p_a.x), (p_b.y - p_a.y)) / M_PI * 180;

    if (deg >= 0)
        return deg;
    else
        return 360 + deg;
}

int Detector::getAngleBot()
{
    Point p_a = find_rect_centre(rect_front);
    Point p_b = find_rect_centre(rect_rear);
    this->robotCenter = find_centre_beetwen_point(p_a, p_b);
    this->angleBot = calc_angle_beetwen_point(p_b, p_a);
    return angleBot;
}

int Detector::getAngleToTarget()
{
    Point point_target = find_rect_centre(rect_target);
    int angle_bot_to_target = calc_angle_beetwen_point(this->robotCenter, point_target);
    this->angleTarget = angle_bot_to_target - this->angleBot;
    return angleTarget;
}

int Detector::getAngleToHome()
{
    Point point_home = find_rect_centre(rect_home);
    int angle_bot_to_home = calc_angle_beetwen_point(this->robotCenter, point_home);
    this->angleHome = angle_bot_to_home - this->angleBot;
    return angleHome;
}
