/**
 * @file graphics_engine.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "engine_defines.h"
#include "game/config.h"
#include "game/state_machine_defines.h"
#include "system/exceptions.h"
#include "system/graphics/color.h"
#include "system/graphics/sprite_manager.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <pspdisplay.h>
#include <pspgu.h>

namespace PS::Game
{

/**
 * @brief Graphics engine responsible for rendering the game
 *
 */
class Graphics_Engine
{
    using Sprite_Manager = System::Graphics::Sprite_Manager<Config::Sprites>;

    struct Vertex
    {
        float u;
        float v;
        std::uint32_t color;
        float x;
        float y;
        float z;
    };

    struct Color_Vertex
    {
        std::uint32_t color;
        float x;
        float y;
        float z;
    };

  public:
    Graphics_Engine()
    {
        m_frame_buffer = guGetStaticVramBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, GU_PSM_8888);
        m_display_buffer = guGetStaticVramBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, GU_PSM_8888);
        sceGuInit();

        sceGuStart(GU_DIRECT, m_display_list);
        sceGuDrawBuffer(GU_PSM_8888, m_frame_buffer, BUFFER_WIDTH);
        sceGuDispBuffer(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, m_display_buffer, BUFFER_WIDTH);
        sceGuDepthBuffer(m_frame_buffer, 0);
        sceGuDisable(GU_DEPTH_TEST);
        sceGuOffset(2048 - Config::SCREEN_WIDTH / 2, 2048 - Config::SCREEN_HEIGHT / 2);
        sceGuViewport(2048, 2048, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
        sceGuEnable(GU_SCISSOR_TEST);
        sceGuScissor(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
        sceGuEnable(GU_BLEND);
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuDisable(GU_TEXTURE_2D);
        sceGuFinish();
        sceGuSync(0, 0);
        sceGuDisplay(GU_TRUE);

        m_sprite_manager = std::make_unique<Sprite_Manager>();
    }

    void clear_screen_color(std::uint32_t color)
    {
        sceGuStart(GU_DIRECT, m_display_list);
        sceGuClearColor(to_abgr(color));
        sceGuClear(GU_COLOR_BUFFER_BIT);
    }

    void present()
    {
        sceGuFinish();
        sceGuSync(0, 0);
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    void load_sprite(Config::Sprites sprite, char const *file)
    {
        m_sprite_manager->make_sprite(sprite, file);
    }

    Library::Vector_2D sprite_dimensions(Config::Sprites sprite) const
    {
        return m_sprite_manager->get_sprite(sprite).get_dimensions();
    }

    void update(States state, Actors const &actors, int score)
    {
        clear_screen_color(to_rgb(Config::SKY_COLOR));
        draw_rectangle(0.0F, static_cast<float>(Config::GROUND_LEVEL), static_cast<float>(Config::SCREEN_WIDTH),
                       static_cast<float>(Config::SCREEN_HEIGHT - Config::GROUND_LEVEL), to_rgb(Config::GROUND_COLOR));

        switch (state)
        {
        case States::START:
            draw_text_centered(72, "Dino Game");
            draw_text_centered(104, "Press X to start");
            break;
        case States::GAME:
            render_actors(actors);
            draw_score(score);
            break;
        case States::END:
            render_actors(actors);
            draw_text_centered(72, "You have died!");
            draw_text_centered(104, "Press X to restart");
            draw_score(score);
            break;
        default:
            assert(false);
            break;
        }

        (void)score;
        present();
    }

  private:
    static std::uint32_t to_abgr(std::uint32_t color)
    {
        return 0xFF000000U | ((color & 0x0000FFU) << 16) | (color & 0x0000FF00U) | ((color >> 16) & 0x0000FFU);
    }

    static char const *glyph(char character)
    {
        static char const empty[] = "\0\0\0\0\0\0\0";
        static char const glyphs[][8] = {"\x0e\x11\x11\x1f\x11\x11\x11",
                                         "\x1e\x11\x11\x1e\x11\x11\x1e",
                                         "\x0e\x11\x10\x10\x10\x11\x0e",
                                         "\x1e\x11\x11\x11\x11\x11\x1e",
                                         "\x1f\x10\x10\x1e\x10\x10\x1f",
                                         "\x1f\x10\x10\x1e\x10\x10\x10",
                                         "\x0e\x11\x10\x17\x11\x11\x0f",
                                         "\x11\x11\x11\x1f\x11\x11\x11",
                                         "\x1f\x04\x04\x04\x04\x04\x1f",
                                         "\x01\x01\x01\x01\x11\x11\x0e",
                                         "\x11\x12\x14\x18\x14\x12\x11",
                                         "\x10\x10\x10\x10\x10\x10\x1f",
                                         "\x11\x1b\x15\x15\x11\x11\x11",
                                         "\x11\x19\x15\x13\x11\x11\x11",
                                         "\x0e\x11\x11\x11\x11\x11\x0e",
                                         "\x1e\x11\x11\x1e\x10\x10\x10",
                                         "\x0e\x11\x11\x11\x15\x12\x0d",
                                         "\x1e\x11\x11\x1e\x14\x12\x11",
                                         "\x0f\x10\x10\x0e\x01\x01\x1e",
                                         "\x1f\x04\x04\x04\x04\x04\x04",
                                         "\x11\x11\x11\x11\x11\x11\x0e",
                                         "\x11\x11\x11\x11\x11\x0a\x04",
                                         "\x11\x11\x11\x15\x15\x15\x0a",
                                         "\x11\x11\x0a\x04\x0a\x11\x11",
                                         "\x11\x11\x0a\x04\x04\x04\x04",
                                         "\x1f\x01\x02\x04\x08\x10\x1f",
                                         "\x0e\x11\x13\x15\x19\x11\x0e",
                                         "\x1e\x11\x11\x1e\x11\x11\x1e",
                                         "\x0e\x11\x10\x10\x10\x11\x0e",
                                         "\x1e\x11\x11\x11\x11\x11\x1e",
                                         "\x1f\x10\x10\x1e\x10\x10\x1f",
                                         "\0\0\0\0\0\0\0",
                                         "\x04\x04\x04\0\0\x04\x04",
                                         "\x0e\x11\x01\x0e\x10\x11\x0e",
                                         "\x00\x00\x00\x00\x00\x00\x00",
                                         "\x04\0\0\0\0\0\0",
                                         "\0\0\0\0\0\0\x04"};
        static char const digits[][8] = {"\x0e\x11\x13\x15\x19\x11\x0e", "\x04\x0c\x04\x04\x04\x04\x1f",
                                         "\x0e\x11\x01\x02\x04\x08\x1f", "\x1e\x01\x01\x0e\x01\x01\x1e",
                                         "\x02\x06\x0a\x12\x1f\x02\x02", "\x1f\x10\x10\x1e\x01\x01\x1e",
                                         "\x06\x08\x10\x1e\x11\x11\x0e", "\x1f\x01\x02\x04\x08\x08\x08",
                                         "\x0e\x11\x11\x0e\x11\x11\x0e", "\x0e\x11\x11\x0f\x01\x02\x0c"};
        static char const punctuation[][8] = {"\0\0\x04\0\0\x04\0", "\x04\x04\x04\x04\0\x04\0"};
        if (character >= 'a' && character <= 'z')
        {
            character = static_cast<char>(character - 'a' + 'A');
        }
        if (character >= 'A' && character <= 'Z')
        {
            return glyphs[character - 'A'];
        }
        if (character >= '0' && character <= '9')
        {
            return digits[character - '0'];
        }
        if (character == ':')
        {
            return punctuation[0];
        }
        if (character == '!')
        {
            return punctuation[1];
        }
        return empty;
    }

    void draw_text_centered(int y, char const *text)
    {
        auto const width = static_cast<int>(std::strlen(text)) * 12 - 2;
        draw_text((Config::SCREEN_WIDTH - width) / 2, y, text);
    }

    void draw_text(int x, int y, char const *text)
    {
        while (*text != '\0')
        {
            auto const *rows = glyph(*text++);
            for (int row = 0; row < 7; ++row)
            {
                for (int column = 0; column < 5; ++column)
                {
                    if ((rows[row] & (1 << (4 - column))) != 0)
                    {
                        draw_rectangle(static_cast<float>(x + column * 2), static_cast<float>(y + row * 2), 2.0F, 2.0F,
                                       0xFFFFFFU);
                    }
                }
            }
            x += 12;
        }
    }

    void draw_score(int score)
    {
        char score_text[32];
        std::snprintf(score_text, sizeof(score_text), "Score: %d", score);
        draw_text(16, 16, score_text);
    }

    static std::uint32_t to_rgb(System::Graphics::Color color)
    {
        return (static_cast<std::uint32_t>(color.r) << 16) | (static_cast<std::uint32_t>(color.g) << 8) |
               static_cast<std::uint32_t>(color.b);
    }

    void draw_rectangle(float x, float y, float width, float height, std::uint32_t color)
    {
        auto *vertices = static_cast<Color_Vertex *>(sceGuGetMemory(2 * sizeof(Color_Vertex)));
        vertices[0] = {.color = to_abgr(color), .x = x, .y = y, .z = 0.0F};
        vertices[1] = {.color = to_abgr(color), .x = x + width, .y = y + height, .z = 0.0F};
        sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, nullptr, vertices);
    }

    void render_actors(Actors const &actors)
    {
        for (auto actor = actors.rbegin(); actor != actors.rend(); ++actor)
        {
            auto const &sprite = m_sprite_manager->get_sprite(actor->ptr->get_sprite());
            auto const &rectangle = actor->ptr->get_rectangle();
            auto *vertices = static_cast<Vertex *>(sceGuGetMemory(2 * sizeof(Vertex)));
            vertices[0] = {.u = 0.0F, .v = 0.0F, .color = 0xFFFFFFFFU, .x = rectangle.x, .y = rectangle.y, .z = 0.0F};
            vertices[1] = {.u = rectangle.w,
                           .v = rectangle.h,
                           .color = 0xFFFFFFFFU,
                           .x = rectangle.x + rectangle.w,
                           .y = rectangle.y + rectangle.h,
                           .z = 0.0F};

            sceGuTexMode(GU_PSM_8888, 0, 0, GU_FALSE);
            sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
            sceGuTexFilter(GU_NEAREST, GU_NEAREST);
            sceGuTexImage(0, sprite.texture_width(), sprite.texture_height(), sprite.texture_width(),
                          sprite.get_data());
            sceGuEnable(GU_TEXTURE_2D);
            sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2,
                           nullptr, vertices);
            sceGuDisable(GU_TEXTURE_2D);
        }
    }

    static constexpr int BUFFER_WIDTH = 512;
    static constexpr int BUFFER_HEIGHT = 272;
    alignas(64) inline static char m_display_list[0x20000]{};
    void *m_frame_buffer{nullptr};
    void *m_display_buffer{nullptr};
    std::unique_ptr<Sprite_Manager> m_sprite_manager;
};

} // namespace PS::Game