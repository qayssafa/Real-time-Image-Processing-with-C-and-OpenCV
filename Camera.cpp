#include "Camera.h"

Camera::Camera(int cameraIndex, const std::string& logoPath)
        : cap(cameraIndex), lastTime(0.0), fps(0.0) {
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        exit(-1);
    }
    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);

    logoFrame = cv::imread(logoPath, cv::IMREAD_UNCHANGED);
    if (logoFrame.empty()) {
        std::cerr << "Error: Could not load the logo image." << std::endl;
        exit(-1);
    }

    double scale = 0.3;
    cv::resize(logoFrame, logoFrame, cv::Size(), scale, scale, cv::INTER_CUBIC);
}

void Camera::calculateFPS() {

    double currentTime = (double)cv::getTickCount();
    if (lastTime > 0) {
        fps = cv::getTickFrequency() / (currentTime - lastTime);
    }
    lastTime = currentTime;
}

void Camera::captureFrame() {
    cap >> frame;
    calculateFPS();

    if (frame.empty()) {
        std::cerr << "Error: Could not retrieve frame." << std::endl;
        exit(-1);
    }
}

void Camera::extractBlueChannel() {
    std::vector<cv::Mat> channels(3);
    cv::split(frame, channels);
    channels[1] = cv::Mat::zeros(channels[1].size(), channels[1].type());
    channels[2] = cv::Mat::zeros(channels[2].size(), channels[2].type());
    cv::merge(channels, blueFrame);
}

void Camera::removeBlueChannel() {
    std::vector<cv::Mat> channels(3);
    cv::split(frame, channels);
    channels[0] = cv::Mat::zeros(channels[0].size(), channels[0].type());
    cv::merge(channels, noBlueFrame);
}


void Camera::addLogoToFrame() {
    frameWithLogo = frame.clone();

    int x = frame.cols - logoFrame.cols;
    int y = frame.rows - logoFrame.rows;

    cv::Mat roi = frameWithLogo(cv::Rect(x, y, logoFrame.cols, logoFrame.rows));

    cv::addWeighted(roi, 1.0, logoFrame, 1.0, 0.0, roi);
}


void Camera::overlayFPS() {
    std::stringstream ss;
    ss << "FPS: " << fps;
    cv::putText(frame, ss.str(), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
}

void Camera::convertToGray() {
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(grayFrame, grayFrame, cv::COLOR_GRAY2BGR);
}

void Camera::splitAndFlipFrame() {
    cv::Mat newFrame = frame.clone();
    cv::Mat topHalf = newFrame(cv::Rect(0, 0, newFrame.cols, newFrame.rows / 2));
    cv::Mat bottomHalf = newFrame(cv::Rect(0, newFrame.rows / 2, newFrame.cols, newFrame.rows / 2));
    cv::flip(bottomHalf, bottomHalf, 0);
    cv::vconcat(topHalf, bottomHalf, flippedFrame);
}

void Camera::displayFrame() {
    double scale = 0.5;
    cv::Mat combinedFrameHorizontal1, combinedFrameHorizontal2, combinedFrameHorizontal3, combinedFrameVertical;
    cv::hconcat(frame, blueFrame, combinedFrameHorizontal1);
    cv::hconcat(noBlueFrame, frameWithLogo, combinedFrameHorizontal2);
    cv::hconcat(grayFrame, flippedFrame, combinedFrameHorizontal3);
    cv::vconcat(combinedFrameHorizontal1, combinedFrameHorizontal2, combinedFrameVertical);
    cv::vconcat(combinedFrameVertical, combinedFrameHorizontal3, combinedFrameVertical);
    cv::resize(combinedFrameVertical, combinedFrameVertical, cv::Size(), scale, scale, cv::INTER_CUBIC);
    cv::imshow("Camera Feed", combinedFrameVertical);
}

bool Camera::isEscapeKeyPressed() {
    return cv::waitKey(27) >= 0;
}

Camera::~Camera() {
    cap.release();
    cv::destroyAllWindows();
}
