#ifndef ADALLGL_ENTRYPOINT_H
#define ADALLGL_ENTRYPOINT_H

#include "adal_application.h"

extern adlglApplication& adlglMakeApplication();

int main(int argc, char** argv) {
    auto& application = adlglMakeApplication();
    application.run();

    return 0;
}

#endif //ADALLGL_ENTRYPOINT_H
