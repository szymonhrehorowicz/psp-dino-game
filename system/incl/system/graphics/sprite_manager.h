/**
 * @file sprite_manager.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "library/enum_array.h"
#include "sprite.h"
#include <cassert>
#include <memory>

namespace PS::System::Graphics
{

/**
 * @brief Provides access to sprites.
 *
 * @tparam Enum - enumeration representing available sprites.
 */
template <typename Enum> class Sprite_Manager
{
    static_assert(std::is_enum_v<Enum>, "Enum_Array requires an enum type");
    static_assert(!std::is_convertible_v<Enum, std::underlying_type_t<Enum>>,
                  "Enum_Array requires a scoped enum class");

  public:
    Sprite_Manager() = default;

    /**
     * @brief Creates new sprite and stores it.
     *
     * @param value - element of templated enumeration type indicating specific sprite.
     * @param file - name of a `file` with sprite to be loaded and associated with given `value`.
     */
    void make_sprite(Enum const value, const char *file)
    {
        auto &sprite = m_sprites[value];
        assert(!sprite);

        sprite = std::make_unique<Sprite>(file);
    }

    /**
     * @brief Get Sprite object associated with given identifier.
     *
     * @param value - identifier of a specific Sprite.
     * @return Sprite const&
     */
    Sprite const &get_sprite(Enum const value) const
    {
        auto &sprite = m_sprites[value];
        assert(sprite);

        return *sprite;
    }

    /**
     * @brief Get Sprite object associated with given identifier.
     *
     * @param value - identifier of a specific Sprite.
     * @return Sprite&
     */
    Sprite &get_sprite(Enum const value)
    {
        auto &sprite = m_sprites[value];
        assert(sprite);

        return *sprite;
    }

  private:
    Library::Enum_Array<Enum, std::unique_ptr<Sprite>> m_sprites;
};

} // namespace PS::System::Graphics