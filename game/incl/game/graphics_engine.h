/**
 * @file engine.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "engine_defines.h"
#include "game/config.h"
#include "system/exceptions.h"
#include "system/graphics/color.h"
#include "system/graphics/sprite_manager.h"
#include <cassert>
#include <memory>

namespace PS::Game
{

/**
 * @brief Graphics engine responsible for rendering the game
 *
 */
class Graphics_Engine
{
    using Sprite_Manager = System::Graphics::Sprite_Manager<Config::Sprites>;
    using Window_Ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using Renderer_Ptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

  public:
    Graphics_Engine(int screen_width, int screen_height)
        : m_screen_width(screen_width), m_screen_height(screen_height), m_ground_level(Config::GROUND_LEVEL)
    {
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;

        if (!SDL_CreateWindowAndRenderer("window", screen_width, screen_height, 0, &window, &renderer))
        {
            throw System::SDL_Exception("Couldn't create window/renderer");
        }

        m_window.reset(window);
        m_renderer.reset(renderer);
        m_sprite_manager = std::make_unique<Sprite_Manager>(*m_renderer);
    }

    void load_sprite(Config::Sprites sprite, char const *file)
    {
        m_sprite_manager->make_sprite(sprite, file);
    }

    Library::Vector_2D sprite_dimensions(Config::Sprites sprite) const
    {
        return m_sprite_manager->get_sprite(sprite).get_dimensions();
    }

    void update(Actors const &actors)
    {
        render_background();

        for (auto const &actor : actors)
        {
            auto const &sprite = m_sprite_manager->get_sprite(actor.sprite);
            SDL_RenderTexture(m_renderer.get(), sprite.get_texture(), nullptr, &actor.ptr->get_rectangle());
        }

        SDL_RenderPresent(m_renderer.get());
    }

    void set_ground_level(int level)
    {
        m_ground_level = level;
    }

  private:
    void render_sky()
    {
        SDL_SetRenderDrawColor(m_renderer.get(), Config::SKY_COLOR.r, Config::SKY_COLOR.g, Config::SKY_COLOR.b,
                               Config::SKY_COLOR.a);
        SDL_RenderClear(m_renderer.get());
    }

    void render_ground()
    {
        static SDL_FRect const ground_rectangle{0.0F, static_cast<float>(m_ground_level),
                                                static_cast<float>(m_screen_width),
                                                static_cast<float>(m_screen_height - m_ground_level)};

        SDL_SetRenderDrawColor(m_renderer.get(), Config::GROUND_COLOR.r, Config::GROUND_COLOR.g, Config::GROUND_COLOR.b,
                               Config::GROUND_COLOR.a);
        SDL_RenderFillRect(m_renderer.get(), &ground_rectangle);
    }

    void render_background()
    {
        render_sky();
        render_ground();
    }

    Window_Ptr m_window{nullptr, SDL_DestroyWindow};
    Renderer_Ptr m_renderer{nullptr, SDL_DestroyRenderer};
    std::unique_ptr<Sprite_Manager> m_sprite_manager;

    int m_screen_width;
    int m_screen_height;
    int m_ground_level{};
};

} // namespace PS::Game