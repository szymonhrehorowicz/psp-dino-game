#pragma once

#include "library/coordinates.h"
#include <cstdint>

namespace PS::System::Graphics
{

/**
 * @brief Handles the sprite. Loads it from a file and grants access to it.
 *
 */
class Sprite
{
  public:
    explicit Sprite(const char *file);

    ~Sprite();

    /**
     * @brief Get texture of a Sprite.
     *
     * @return SDL_Texture*
     */
    std::uint32_t const *get_data() const
    {
        return m_data;
    }

    /**
     * @brief Get the dimensions of the Sprite
     *
     * @return Library::Vector_2D, where x - width; y - height
     */
    [[nodiscard]] Library::Vector_2D get_dimensions() const
    {
        return m_dimensions;
    }

  private:
    std::uint32_t *m_data{nullptr};
    int m_texture_width{0};
    int m_texture_height{0};
    Library::Vector_2D m_dimensions{0, 0};

  public:
    int texture_width() const
    {
        return m_texture_width;
    }

    int texture_height() const
    {
        return m_texture_height;
    }
};

} // namespace PS::System::Graphics