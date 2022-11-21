#ifndef __NIMGUI_H__
#define __NIMGUI_H__
#if __DESKTOP__

#else
#define __DESKTOP__
#endif
// Basic Includes
#include <iostream>
#include <string>

#include <NImGui/Image.hpp>
#include <NImGui/KeyCodes.hpp>
#include <NImGui/Timer.hpp>

// Adobe Design
#include <NImGui/spectrum.hpp>

#if defined(__DESKTOP__)
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <glad.h>

#endif

#include <backends/imgui_impl_opengl3.h>

#include <imgui.h>

namespace NImGui {
typedef int NWindowFlags;

enum WindowFlags {
  NONE = 0,
  FULLSCREEN = 1 << 1,
  BORDERLESS = 1 << 2,
  NORESIZE = 1 << 3,
  TRANSPARENT = 1 << 4,
  MAXIMIZED = 1 << 5,
  BORDERLESSFULLSCREEN = 1 << 6,
};

struct Vec2i {
  Vec2i(int ix = 0, int iy = 0) {
    x = ix;
    y = iy;
  }
  int x;
  int y;
};
struct Vec2f {
  Vec2f(float ix = 0, float iy = 0) {
    x = ix;
    y = iy;
  }
  float x;
  float y;
};

struct Vec4f {
  Vec4f(float ix = 0, float iy = 0, float iz = 0, float iw = 0) {
    x = ix;
    y = iy;
    z = iz;
    w = iw;
  }
  float x;
  float y;
  float z;
  float w;
};

class App {
public:
  App(std::string name = "NImGui App", Vec2i size = Vec2i(700, 400),
      NWindowFlags flags = 0);
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
  void SetFullScreen(bool fsc);
  inline Vec4f GetClearColor() { return clearcl; }
  inline void SetClearColor(Vec4f col) { clearcl = col; }
  // Input
  bool IsKeyDown(KeyCode keycode);
  bool IsMouseButtonDown(MouseButton button);
  Vec2f GetMousePosition();
  void SetCursorMode(CursorMode mode);

private:
  void UpdateContext();
  std::string title;
  Vec2i windowpos;
  Vec2i windowsize;
  Vec4f clearcl = Vec4(0, 0, 0, 0);
  bool transparent = false;
  bool vsync = true;
#if defined(__DESKTOP__)
  GLFWwindow *win;
#endif
};

} // namespace NImGui

#endif // __NIMGUI_H__