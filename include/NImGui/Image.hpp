#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <vector>

#include <stb_image.h>

#include <imgui.h>

namespace NImGui {
class Image {
public:
  Image(std::string path = "");
  ~Image();
  void LoadImage(std::string path);
  void LoadBuffer(std::vector<unsigned char> buffer, int w, int h, int bpp = 4);
  void LoadFromMem(std::vector<unsigned char> buffer);
  ImTextureID GetTextureID();

  ImVec2 GetSize();

private:
  ImVec2 size;
  unsigned regid = 0;
};
} // namespace NImGui
#endif // __IMAGE_H__