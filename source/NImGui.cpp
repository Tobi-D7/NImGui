#include <NImGui/NImGui.hpp>

namespace NImGui
{
  App::App(std::string name, Vec2i size, NWindowFlags flags, ImFlags imflags)
  {
    this->title = name;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGuiStyle &style = ImGui::GetStyle();
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
    // Controls
    if (imflags & ImDOCKING)
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

    if (imflags & ImVIEWPORT)
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport /
                                                          // Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;
    //  Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    //  When viewports are enabled we tweak WindowRounding/WindowBg so platform
    //  windows can look identical to regular ones.
    style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
#if defined(__DESKTOP__)
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    if (flags & NImGui::BORDERLESS)
    {
      glfwWindowHint(GLFW_DECORATED, 0);
    }

    if (flags & NImGui::TRANSPARENT)
    {
      transparent = true;
      glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    }

    if (flags & NImGui::NORESIZE)
    {
      glfwWindowHint(GLFW_RESIZABLE, 0);
    }

    if (flags & NImGui::FULLSCREEN)
    {
    }

    if (flags & NImGui::MAXIMIZED)
    {
      glfwWindowHint(GLFW_MAXIMIZED, 1);
    }

    if (flags & NImGui::BORDERLESSFULLSCREEN)
    {
      glfwWindowHint(GLFW_DECORATED, 0);
      glfwWindowHint(GLFW_MAXIMIZED, 1);
    }

    win = glfwCreateWindow(size.x, size.y, this->title.c_str(), NULL, NULL);
    if (flags & NImGui::BORDERLESSFULLSCREEN)
    {
      const GLFWvidmode *vm = glfwGetVideoMode(glfwGetPrimaryMonitor());
      glfwSetWindowSize(win, vm->width, vm->height);
    }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);
    gladLoadGL();
    std::cout << "Loadet OpenGL -> " << GLVersion.major << "." << GLVersion.minor
              << "\n";
    this->UpdateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
#endif
    ImGui_ImplOpenGL3_Init();
  }
  App::~App()
  {
    ImGui_ImplOpenGL3_Shutdown();
#if defined(__DESKTOP__)
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
#endif
  }

  bool App::IsRunning()
  {
    glViewport(0, 0, windowsize.x, windowsize.y);
    glClearColor(clearcl.x, clearcl.y, clearcl.z, clearcl.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
#if defined(__DESKTOP__)
    ImGui_ImplGlfw_NewFrame();
#endif
    ImGui::NewFrame();
#if defined(__DESKTOP__)
    this->UpdateContext();
    glfwPollEvents();
    return !glfwWindowShouldClose(this->win);
#endif
  }

  void App::UpdateContext()
  {
    int x, y;
#if defined(__DESKTOP__)
    glfwGetWindowPos(win, &x, &y);
    windowpos = Vec2i(x, y);
    glfwGetWindowSize(win, &x, &y);
    windowsize = Vec2i(x, y);
#endif
  }

  Vec2i App::GetWindowSize() { return this->windowsize; }

  Vec2i App::GetWindowPos() { return this->windowpos; }

  void App::SwapBuffers()
  {
    ImGui::Render();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#if defined(__DESKTOP__)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow *backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
    glfwSwapBuffers(win);
#endif
  }

  void App::SetWindowSize(Vec2i size) { glfwSetWindowSize(win, size.x, size.y); }

  void App::SetWindowPos(Vec2i pos) { glfwSetWindowPos(win, pos.x, pos.y); }

  bool App::IsKeyDown(KeyCode keycode)
  {
    int state = glfwGetKey(win, (int)keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool App::IsMouseButtonDown(MouseButton button)
  {
    int state = glfwGetMouseButton(win, (int)button);
    return state == GLFW_PRESS;
  }

  Vec2f App::GetMousePosition()
  {
    double x, y;
    glfwGetCursorPos(win, &x, &y);
    return {(float)x, (float)y};
  }

  void App::SetCursorMode(CursorMode mode)
  {
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
  }

  void App::SetVsync(bool vs)
  {
    vsync = vs;
    glfwSwapInterval((int)vsync);
  }

  bool App::GetVsync() { return vsync; }

  Vec2i App::GetMonitorSize()
  {
    const GLFWvidmode *vm = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return Vec2i(vm->width, vm->height);
  }

  void App::LoadIcon(std::string path)
  {
    int w, h;
    GLFWimage img[1];
    img->pixels = stbi_load(path.c_str(), &w, &h, 0, 4);
    if (img->pixels == NULL)
    {
      std::cout << "Failed to load " << path << std::endl;
      return;
    }
    // img->width = w;
    // img->height = h;
    glfwSetWindowIcon(win, 1, img);
  }

  void App::SetFullScreen(bool fsc)
  {
    GLFWmonitor *mw = glfwGetPrimaryMonitor();
    const GLFWvidmode *vm = glfwGetVideoMode(mw);
    glfwSetWindowMonitor(win, mw, 0, 0, vm->width, vm->height, vm->refreshRate);
  }
} // namespace NImGui