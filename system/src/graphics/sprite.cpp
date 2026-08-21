#include "system/graphics/sprite.h"
#include "SDL3/SDL_surface.h"
#include "system/exceptions.h"

namespace PS::System::Graphics
{

Sprite::Sprite(SDL_Renderer &renderer, const char *file)
{
    SDL_Surface *pixels = SDL_LoadPNG(file);

    if (pixels)
    {
        m_sprite = SDL_CreateTextureFromSurface(&renderer, pixels);

        SDL_DestroySurface(pixels);
        if (m_sprite != nullptr)
        {
            SDL_GetTextureSize(m_sprite, &m_dimensions.x, &m_dimensions.y);
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

Sprite::~Sprite()
{
    if (m_sprite)
    {
        SDL_DestroyTexture(m_sprite);
    }
}

} // namespace PS::System::Graphics