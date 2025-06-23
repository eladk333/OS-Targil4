#include "CoEditor.h"
#include <unistd.h>
#include <string>

void* co_editor_thread(void* arg) {
    CoEditorArgs* args = static_cast<CoEditorArgs*>(arg);

    while (true) {
        std::string msg = args->inputQueue->remove();

        if (msg == "DONE") {
            args->outputQueue->insert("DONE");
            break;
        }

        usleep(100000); // simulate editing delay: 0.1 second
        args->outputQueue->insert(msg);
    }

    return nullptr;
}
