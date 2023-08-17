#include "Camera.cpp"

int main() {
    Camera camera;

    while (true) {
        camera.captureFrame();
        camera.displayFrame();

        if (camera.isEscapeKeyPressed()) {
            break;
        }
    }

    return 0;
}