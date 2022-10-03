#include <NImGui/NImGui.hpp>
#include <map>

#include <imgui_stdlib.h>

std::map<int, std::string> archs = {
    {8, "64-Bit"},
    {4, "32-Bit"},
    {2, "16-Bit"},
    {1, " 8-Bit"},
};


int main()
{
    NImGui::App app;

    std::cout << "Architecture -> " << archs.at(sizeof(void*)) << std::endl;

    std::cout << "Window Position -> " << app.GetWindowPos().x << ":" << app.GetWindowPos().y << std::endl;
    std::cout << "Window Size -> " << app.GetWindowSize().x << ":" << app.GetWindowSize().y << std::endl; 
    std::string testtt = "imgui-std";
    while (app.IsRunning())
    {
        ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize(ImVec2(app.GetWindowSize().x, app.GetWindowSize().y));
        ImGui::SetWindowPos(ImVec2(app.GetWindowPos().x, app.GetWindowPos().y));
        ImGui::Text("Hello NImGui");
        ImGui::InputText("Test", &testtt);

        ImGui::End();
        
        app.SwapBuffers();
    }

    std::cout << "Window Position -> " << app.GetWindowPos().x << ":" << app.GetWindowPos().y << std::endl;
    std::cout << "Window Size -> " << app.GetWindowSize().x << ":" << app.GetWindowSize().y << std::endl; 
    
    exit(EXIT_SUCCESS);
}