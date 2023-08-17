#include <iostream>
#include <opencv2/opencv.hpp>

class Camera {
private:
    cv::VideoCapture cap;
    cv::Mat frame;

public:
    Camera(int cameraIndex = 0) : cap(cameraIndex) {
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open the camera." << std::endl;
            exit(-1);
        }
        cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);
    }

    void captureFrame() {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Could not retrieve frame." << std::endl;
            exit(-1);
        }
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