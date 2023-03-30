#ifndef NURU_APP_H
#define NURU_APP_H

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ui_drawing.h>
#include <vector>
#include <memory>

namespace Nuru {
    struct WindowParams {
        int32_t WIDTH = 1270;
        int32_t HEIGHT = 720;
        const char *title = "Nuru App";
    };

    class App {
    public:
        explicit App(WindowParams params);

        ~App();

    private:
        static void Init(WindowParams params);

        static void Destroy(GLFWwindow *window);

    public:
        void Loop();

        template<typename T>
        void DrawUI()
        {
            static_assert(std::is_base_of<Draw, T>::value, "Pushed type is not subclass of Layer!");
            drawElements.emplace_back(std::make_shared<T>());
        }

        void DrawUI(const std::shared_ptr<Draw> &drawEl) {
            drawElements.emplace_back(drawEl);
        }

    private:
        std::vector<std::shared_ptr<Draw>> drawElements;
    };

    App *CreateApp(int argc, char **argv);
}

#endif //NURU_APP_H
