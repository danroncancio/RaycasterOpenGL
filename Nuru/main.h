#ifndef NURU_MAIN_H
#define NURU_MAIN_H

bool app_running = true;

namespace Nuru {
    int Entry(int argc, char **argv) {
        Nuru::App *app = Nuru::CreateApp(argc, argv);
        app->Loop();
        delete app;
        return 0;
    }
}

int main(int argc, char **argv) {
    return Nuru::Entry(argc, argv);
}

#endif //NURU_MAIN_H
