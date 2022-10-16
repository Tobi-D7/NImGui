#ifndef __NIMGUI_H__
#define __NIMGUI_H__
#define __DESKTOP__
//Basic Includes
#include <iostream>
#include <string>

#include <NImGui/Image.hpp>
#include <NImGui/Timer.hpp>
#include <NImGui/KeyCodes.hpp>

#if defined(__DESKTOP__)
#include <glad.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#endif

#include <backends/imgui_impl_opengl3.h>

#include <imgui.h>

namespace NImGui
{
    typedef int NWindowFlags;

    enum WindowFlags
    {
        NONE = 0,
        FULLSCREEN = 1 << 1,
        BORDERLESS = 1 << 2,
        NORESIZE = 1 << 3,
        TRANSPARENT = 1 << 4,
        MAXIMIZED = 1 << 5,
        BORDERLESSFULLSCREEN = 1 << 6,
    };

    struct Vec2i
    {
        Vec2i(int ix = 0, int iy = 0)
        {
            x = ix;
            y = iy;
        }
        int x;
        int y;
    };
    struct Vec2f
    {
        Vec2f(float ix = 0, float iy = 0)
        {
            x = ix;
            y = iy;
        }
        float x;
        float y;
    };
    
    class App
    {
        public:
        App(std::string name = "NImGui App", Vec2i size = Vec2i(700, 400), NWindowFlags flags = 0);
        ~App();
        bool IsRunning();
        Vec2i GetWindowSize();
        Vec2i GetWindowPos();
        Vec2i GetMonitorSize();
        void SetWindowSize(Vec2i size);
        void SetWindowPos(Vec2i pos);
        void SwapBuffers();
        void SetVsync(bool vs);
        bool GetVsync();
        void LoadIcon(std::string path);

        //Input
        bool IsKeyDown(KeyCode keycode);
		bool IsMouseButtonDown(MouseButton button);
        Vec2f GetMousePosition();
        void SetCursorMode(CursorMode mode);

        private:
        void UpdateContext();
        std::string title;
        Vec2i windowpos;
        Vec2i windowsize;
        bool transparent = false;
        bool vsync = true;
        #if defined(__DESKTOP__)
        GLFWwindow* win;
        #endif
    };
    
} // namespace NImGui


#endif // __NIMGUI_H__