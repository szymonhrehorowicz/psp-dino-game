#pragma once

#include "SDL3/SDL_render.h"
#include "system/coordinates.h"

namespace PS::System::Graphics
{

class Sprite
{
  public:
    explicit Sprite(SDL_Renderer &renderer, const char *file);

    ~Sprite();

    SDL_Texture *get_texture() const
    {
        return m_sprite;
    }

    /**
     * @brief Get the dimensions of the sprite
     *
     * @return Vector_2D, where x - width; y - height
     */
    [[nodiscard]] Vector_2D get_dimensions() const
    {
        return m_dimensions;
    }

  private:
    SDL_Texture *m_sprite{nullptr};
    Vector_2D m_dimensions{0, 0};
};

} // namespace PS::System::Graphics