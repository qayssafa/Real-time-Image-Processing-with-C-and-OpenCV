
#include "Camera.h"
int main() {
    Camera camera(0, "/home/qays/Downloads/Imagry_Logo.jpg");

    while (true) {
        camera.captureFrame();
        camera.extractBlueChannel();
        camera.removeBlueChannel();
        camera.convertToGray();
        camera.addLogoToFrame();
        camera.splitAndFlipFrame();
        camera.overlayFPS();
        camera.displayFrame();

        if (camera.isEscapeKeyPressed()) {
            break;
        }
    }

    return 0;
}