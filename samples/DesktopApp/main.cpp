#include <NImGui/NImGui.hpp>
#include <map>

#include <imgui_stdlib.h>

#define MENUBARFLAGS                                                           \
  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |                        \
      ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar |                   \
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking

std::map<int, std::string> archs = {
    {8, "64-Bit"},
    {4, "32-Bit"},
    {2, "16-Bit"},
    {1, " 8-Bit"},
};

NImGui::Timer deltaclock;
NImGui::Timer frameclock;
int frames;
int fps = 0;

//
bool demo = false;

std::string FrameRate() {
  frames++;
  if ((frameclock.GetAsMs() / 1000) >= 1.f) {
    fps = frames;
    frames = 0;
    frameclock.Reset();
  }
  return std::to_string(fps);
}

void DrawMenu() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit", "Exit")) {
        std::cout << "exit" << std::endl;
        exit(EXIT_SUCCESS);
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("ImGui Demo", "ImGui Demo")) {
        demo = true;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

int main() {
  NImGui::App app("Desktop App", NImGui::TRANSPARENT);

  std::cout << "Architecture -> " << archs.at(sizeof(void *)) << std::endl;

  std::cout << "Window Position -> " << app.GetWindowPos().x << ":"
            << app.GetWindowPos().y << std::endl;
  std::cout << "Window Size -> " << app.GetWindowSize().x << ":"
            << app.GetWindowSize().y << std::endl;
  std::string testtt = "test";
  while (app.IsRunning()) {
    deltaclock.Reset();

    ImGui::Begin("Test", NULL, MENUBARFLAGS);
    ImGui::SetWindowSize(ImVec2(app.GetWindowSize().x, app.GetWindowSize().y));
    ImGui::SetWindowPos(ImVec2(app.GetWindowPos().x, app.GetWindowPos().y));
    DrawMenu();
    ImGui::Text("Architecture -> %s", archs.at(sizeof(void *)).c_str());
    ImGui::Text("FPS -> %s", FrameRate().c_str());
    ImGui::InputText("Test", &testtt);

    ImGui::End();

    ImGui::ShowDemoWindow(&demo);

    app.SwapBuffers();
  }

  std::cout << "Window Position -> " << app.GetWindowPos().x << ":"
            << app.GetWindowPos().y << std::endl;
  std::cout << "Window Size -> " << app.GetWindowSize().x << ":"
            << app.GetWindowSize().y << std::endl;

  exit(EXIT_SUCCESS);
}