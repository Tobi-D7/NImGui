#ifndef __IMAGE_H__
#define __IMAGE_H__

#if defined(__DESKTOP__)
#include <glad.h>
#endif
#include <string>

#include <NImGui/stb_image.h>

#include <imgui.h>

namespace NImGui
{
    class Image
    {
        public:
        Image(std::string path = "")
        {
            if(path != "")
            {
                LoadImage(path);
            }
        }
        ~Image()
        {
            glDeleteTextures(1, &regid);
        }
        void LoadImage(std::string path)
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
                size = ImVec2(width, height);
                regid = textureID;
                std::cout << "Generated Texture: " << std::to_string(regid) << " -> Size: " << std::to_string(size.x) << ", " << std::to_string(size.y) << std::endl;
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }
        }
        ImTextureID GetTextureID()
        {
            return (ImTextureID)regid;
        }

        ImVec2 GetSize()
        {
            return size;
        }
        private:
        ImVec2 size;
        unsigned regid = 0;
    };
}
#endif // __IMAGE_H__