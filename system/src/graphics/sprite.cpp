#include "system/graphics/sprite.h"
#include "SDL3/SDL_surface.h"
#include "system/exceptions.h"

namespace PS::System::Graphics
{

Sprite::Sprite(SDL_Renderer &renderer, const char *file, Position position)
{
    SDL_Surface *pixels = SDL_LoadPNG(file);

    if (pixels)
    {
        m_sprite = SDL_CreateTextureFromSurface(&renderer, pixels);

        SDL_DestroySurface(pixels);
        if (m_sprite != nullptr)
        {
            SDL_GetTextureSize(m_sprite, &m_rectangle.w, &m_rectangle.h);

            m_rectangle.x = position.x;
            m_rectangle.y = position.y;
        }
        else
        {
            throw Sprite_Exception("Couldn't create texture");
        }
    }
    else
    {
        throw Sprite_Exception("Couldn't load pixels");
    }
}

void Sprite::set_position(Position position)
{
    m_rectangle.x = position.x;
    m_rectangle.y = position.y;
}

} // namespace PS::System::Graphics