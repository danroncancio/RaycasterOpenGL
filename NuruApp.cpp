#include "app.h"
#include "main.h"

class DemoWindow : public Nuru::Draw {
    void UIElement() {
        ImGui::Begin("Info");
        ImGui::Text("Hello!");
        ImGui::End();
        ImGui::ShowDemoWindow();
    }
};

Nuru::App *Nuru::CreateApp(int argc, char **argv) {
    Nuru::WindowParams params;
    // params.WIDTH = 1270;
    // params.HEIGHT = 720;
    params.title = "Nuru App Framework";
    auto *app = new Nuru::App(params);

    app->DrawUI<DemoWindow>();

    return app;
}
