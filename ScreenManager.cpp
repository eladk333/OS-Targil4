#include "ScreenManager.h"
#include <iostream>
#include <string>

void* screen_manager_thread(void* arg) {
    ScreenManagerArgs* args = static_cast<ScreenManagerArgs*>(arg);
    int doneCount = 0;

    while (doneCount < 3) {
        std::string msg = args->inputQueue->remove();

        if (msg == "DONE") {
            doneCount++;
        } else {
            std::cout << msg << std::endl;
        }
    }

    std::cout << "DONE" << std::endl;
    return nullptr;
}
