#pragma once

#include "library/enum_array.h"
#include "sprite.h"
#include <cassert>
#include <memory>

namespace PS::System::Graphics
{

template <typename Enum> class Sprite_Manager
{
    static_assert(std::is_enum_v<Enum>, "Enum_Array requires an enum type");
    static_assert(!std::is_convertible_v<Enum, std::underlying_type_t<Enum>>,
                  "Enum_Array requires a scoped enum class");

  public:
    Sprite_Manager(SDL_Renderer &renderer) : m_renderer(renderer) {};

    void make_sprite(Enum const value, const char *file)
    {
        auto &sprite = m_sprites[value];
        assert(!sprite);

        sprite = std::make_unique<Sprite>(m_renderer, file);
    }

    Sprite &get_sprite(Enum const value)
    {
        auto &sprite = m_sprites[value];
        assert(sprite);

        return *sprite;
    }

  private:
    SDL_Renderer &m_renderer;
    Library::Enum_Array<Enum, std::unique_ptr<Sprite>> m_sprites;
};

} // namespace PS::System::Graphics