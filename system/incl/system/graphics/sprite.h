#pragma once

#include "SDL3/SDL_render.h"
#include "library/coordinates.h"

namespace PS::System::Graphics
{

/**
 * @brief Handles the sprite. Loads it from a file and grants access to it.
 *
 */
class Sprite
{
  public:
    explicit Sprite(SDL_Renderer &renderer, const char *file);

    ~Sprite();

    /**
     * @brief Get texture of a Sprite.
     *
     * @return SDL_Texture*
     */
    SDL_Texture *get_texture() const
    {
        return m_sprite;
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
    SDL_Texture *m_sprite{nullptr};
    Library::Vector_2D m_dimensions{0, 0};
};

} // namespace PS::System::Graphics