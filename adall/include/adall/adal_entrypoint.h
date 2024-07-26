#ifndef ADALLGL_ENTRYPOINT_H
#define ADALLGL_ENTRYPOINT_H

#include "adal_application.h"

extern adlApplication& adlMakeApplication();

int main(int argc, char** argv) {
    auto& application = adlMakeApplication();
    application.run();

    return 0;
}

#endif //ADALLGL_ENTRYPOINT_H
