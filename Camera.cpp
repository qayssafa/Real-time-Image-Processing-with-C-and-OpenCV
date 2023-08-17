#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>  // For converting numbers to strings

class Camera {
private:
    cv::VideoCapture cap;
    cv::Mat frame;
    double fps;
    double lastTime;

public:
    Camera(int cameraIndex = 0) : cap(cameraIndex), lastTime(0.0), fps(0.0) {
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open the camera." << std::endl;
            exit(-1);
        }
        cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);
    }

    void calculateFPS() {
        double currentTime = (double)cv::getTickCount();
        if (lastTime > 0) {
            fps = cv::getTickFrequency() / (currentTime - lastTime);
        }
        lastTime = currentTime;
    }

    void captureFrame() {
        cap >> frame;
        calculateFPS();

        if (frame.empty()) {
            std::cerr << "Error: Could not retrieve frame." << std::endl;
            exit(-1);
        }

        std::stringstream ss;
        ss << "FPS: " << fps;
        cv::putText(frame, ss.str(), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    }

    void displayFrame() {
        cv::imshow("Camera Feed", frame);
    }

    bool isEscapeKeyPressed() {
        return cv::waitKey(27) >= 0;
    }

    ~Camera() {
        cap.release();
        cv::destroyAllWindows();
    }
};
