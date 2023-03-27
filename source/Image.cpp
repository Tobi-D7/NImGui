#include <NImGui/Image.hpp>
#include <iostream>

#if defined(__DESKTOP__)
#include <glad.h>
#endif

namespace NImGui {
Image::Image(std::string path) {
  if (path != "") {
    LoadImage(path);
  }
}
Image::~Image() { glDeleteTextures(1, &regid); }
void Image::LoadImage(std::string path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    size = ImVec2(width, height);
    regid = textureID;
    std::cout << "Generated Texture: " << std::to_string(regid)
              << " -> Size: " << std::to_string(size.x) << ", "
              << std::to_string(size.y) << std::endl;
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }
}
void Image::LoadBuffer(std::vector<unsigned char> buffer, int w, int h,
                       int bpp) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  std::cout << "Buffer Size -> " << buffer.size() << std::endl;
  std::cout << "w:" << w << "-h:" << h << "-bpp:" << bpp << std::endl;

  int width = w;
  int height = h;
  int nrComponents = bpp;
  if (buffer.size() > 0) {
    GLenum format = GL_RGBA;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    // Texture size must be power of two for the primitive OpenGL version this
    // is written for. Find next power of two.
    size_t u2 = 1;
    while (u2 < width)
      u2 *= 2;
    size_t v2 = 1;
    while (v2 < height)
      v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the
    // non power of two image with proper size.
    double u3 = (double)width / u2;
    double v3 = (double)height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for (size_t y = 0; y < height; y++)
      for (size_t x = 0; x < width; x++)
        for (size_t c = 0; c < 4; c++) {
          image2[4 * u2 * y + 4 * x + c] = buffer[4 * width * y + 4 * x + c];
        }

    // Enable the texture for OpenGL.
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST); // GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 &image2[0]);
    // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
    // GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    size = ImVec2(width, height);
    regid = textureID;
    std::cout << "Generated Texture: " << std::to_string(regid)
              << " -> Size: " << std::to_string(size.x) << ", "
              << std::to_string(size.y) << std::endl;
  } else {
    std::cout << "Texture failed to load from buffer " << std::endl;
  }
}

void NImGui::Image::LoadFromMem(std::vector<unsigned char> buffer)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load_from_memory(buffer.data(), buffer.size(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    size = ImVec2(width, height);
    regid = textureID;
    std::cout << "Generated Texture: " << std::to_string(regid)
              << " -> Size: " << std::to_string(size.x) << ", "
              << std::to_string(size.y) << std::endl;
  } else {
    std::cout << "Texture failed to load from memory!" << std::endl;
    stbi_image_free(data);
  }
}

ImTextureID Image::GetTextureID() { return (ImTextureID)regid; }

ImVec2 Image::GetSize() { return size; }
} // namespace NImGui