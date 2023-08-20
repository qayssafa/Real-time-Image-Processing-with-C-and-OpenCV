
#pragma once

#include <opencv2/opencv.hpp>
#include <sstream>

class Camera {
private:
    cv::VideoCapture cap;
    cv::Mat frame;
    cv::Mat blueFrame;
    cv::Mat noBlueFrame;
    cv::Mat logoFrame;
    cv::Mat frameWithLogo;
    cv::Mat grayFrame;
    cv::Mat flippedFrame;

    double fps;
    double lastTime;

public:
    Camera(int cameraIndex = 0, const std::string& logoPath = "");
    void calculateFPS();
    void captureFrame();
    void extractBlueChannel();
    void removeBlueChannel();
    void addLogoToFrame();
    void overlayFPS();
    void convertToGray();
    void splitAndFlipFrame();
    void displayFrame();
    bool isEscapeKeyPressed();
    ~Camera();
};


