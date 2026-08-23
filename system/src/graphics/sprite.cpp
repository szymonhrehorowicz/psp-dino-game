#include "system/graphics/sprite.h"
#include "system/exceptions.h"
#include <cstdlib>
#include <cstring>
#include <pspkernel.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace PS::System::Graphics
{

namespace
{
int next_power_of_two(int value)
{
    int result = 1;
    while (result < value)
    {
        result *= 2;
    }
    return result;
}
} // namespace

Sprite::Sprite(const char *file)
{
    int width = 0;
    int height = 0;
    int channels = 0;
    auto *pixels = stbi_load(file, &width, &height, &channels, STBI_rgb_alpha);

    if (pixels)
    {
        m_dimensions = Library::Vector_2D{static_cast<float>(width), static_cast<float>(height)};
        m_texture_width = next_power_of_two(width);
        m_texture_height = next_power_of_two(height);
        auto const size = static_cast<std::size_t>(m_texture_width) * m_texture_height * sizeof(std::uint32_t);
        m_data = static_cast<std::uint32_t *>(std::calloc(1, size));
        if (m_data)
        {
            for (int row = 0; row < height; ++row)
            {
                std::memcpy(m_data + row * m_texture_width, pixels + row * width * 4,
                            static_cast<std::size_t>(width) * 4);
            }
            stbi_image_free(pixels);
            sceKernelDcacheWritebackInvalidateAll();
        }
        else
        {
            stbi_image_free(pixels);
            throw Graphics_Exception("Couldn't allocate texture");
        }
    }
    else
    {
        throw Graphics_Exception("Couldn't load pixels");
    }
}

Sprite::~Sprite()
{
    if (m_data)
    {
        std::free(m_data);
    }
}

} // namespace PS::System::Graphics