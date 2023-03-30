#include "app.h"

GLFWwindow *window = nullptr;

namespace Nuru {
    App::App(WindowParams params) {
        Init(params);
    }

    App::~App() {
        Destroy(window);
    }

    void App::Init(WindowParams params) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        window = glfwCreateWindow(params.WIDTH, params.HEIGHT, params.title, nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create a GLFW window" << std::endl;
            return;
        }

        glfwMakeContextCurrent(window);

        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            printf("Failed to initialize OpenGL context\n");
            return;
        }
        printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;

	// Font
	ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	//io.Fonts->AddFontFromFileTTF("../assets/fonts/inter/Inter-Regular.otf", 18.0f);
	ImFont *ubu_font = io.Fonts->AddFontFromFileTTF("assets/fonts/ubuntu/Ubuntu-R.ttf", 17.0f);
	io.FontDefault = ubu_font;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Style
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.WindowRounding = 3;
        style.WindowRounding = 3;
        style.ChildRounding = 3;
        style.FrameRounding = 3;
        style.PopupRounding = 3;
        style.ScrollbarRounding = 3;
        style.GrabRounding = 3;
        style.TabRounding = 3;

        //ImGui::StyleColorsDark();
        ImGui::StyleColorsLight();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void App::Destroy(GLFWwindow *window) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void App::Loop() {

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // ImGui window drawing
            {
                for (auto &draw_ele: drawElements) {
                    draw_ele->UIElement();
                }
            }

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
            //GLFWwindow *backup_current_context = glfwGetCurrentContext();
            //ImGui::UpdatePlatformWindows();
            //ImGui::RenderPlatformWindowsDefault();
            //glfwMakeContextCurrent(backup_current_context);

            glfwSwapInterval(1);
            glfwSwapBuffers(window);
        }
    }
}
