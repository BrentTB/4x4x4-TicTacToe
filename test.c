#include <iostream>
#include <chrono>
#include <thread>

const int numRows = 10;  // Number of rows in the animation
const int animationSpeed = 100;  // Animation speed in milliseconds

void clearScreen() {
    // Clear the terminal screen
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

void displayFrame(int frameNumber, int ballPosition) {
    clearScreen();  // Clear the screen before displaying the new frame

    // ASCII frames for a bouncing ball
    const char* ballFrames[] = {
        "   o   ",
        "  ooo  ",
        " ooooo ",
        "ooooooo",
        " ooooo ",
        "  ooo  ",
        "   o   ",
    };

    // Number of frames
    int numFrames = sizeof(ballFrames) / sizeof(ballFrames[0]);

    // Display the current frame
    for (int i = 0; i < numRows; ++i) {
        if (i == ballPosition) {
            std::cout << ballFrames[frameNumber];
        } else {
            std::cout << "       ";  // Empty space for other rows
        }
        std::cout << '\n';
    }

    std::cout.flush();
}

int main() {
    // Number of frames
    int numFrames = 7;

    // Number of animation cycles
    int numCycles = 5;

    for (int cycle = 0; cycle < numCycles; ++cycle) {
        for (int frameNumber = 0; frameNumber < numFrames; ++frameNumber) {
            // Display the frame at different positions
            for (int position = 0; position < numRows; ++position) {
                displayFrame(frameNumber, position);

                // Pause for a short duration
                std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
            }
        }
    }

    return 0;
}
