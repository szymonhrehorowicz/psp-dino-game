#pragma once

#include "SDL3/SDL_render.h"
#include "system/coordinates.h"

namespace PS::System::Graphics
{

class Sprite
{
  public:
    explicit Sprite(SDL_Renderer &renderer, const char *file, Position position);

    void set_position(Position position);

    SDL_Texture *get_texture() const
    {
        return m_sprite;
    }

    SDL_FRect const *get_rectangle() const
    {
        return &m_rectangle;
    }

  private:
    SDL_Texture *m_sprite{nullptr};
    SDL_FRect m_rectangle{};
};

} // namespace PS::System::Graphics