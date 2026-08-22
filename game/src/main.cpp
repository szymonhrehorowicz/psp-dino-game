#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "game/config.h"
#include "game/engine.h"
#include "system/graphics/sprite_manager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void render_background(SDL_Renderer *renderer);

int main(int /*argc*/, char * /*argv*/[])
{
    using namespace PS;

    // [SDL]
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("window", Game::Config::SCREEN_WIDTH, Game::Config::SCREEN_HEIGHT, 0, &window,
                                     &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    // [SCENE]
    System::Graphics::Sprite_Manager<Game::Config::Sprites> sprite_manager{*renderer};
    sprite_manager.make_sprite(Game::Config::Sprites::PLAYER, Game::Config::PLAYER_SPRITE);
    sprite_manager.make_sprite(Game::Config::Sprites::OBSTACLE, Game::Config::OBSTACLE_SPRITE);

    // [ENGINE]
    Game::Engine engine{sprite_manager};
    engine.add_player();
    engine.add_obstacle();
    engine.add_obstacle({
        Game::Config::OBSTACLE_POSITION_X / 2,
        Game::Config::OBSTACLE_POSITION_Y / 2,
    });

    int running = 1;
    SDL_Event event;

    while (running)
    {
        // [SDL]
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                // End the loop if the programs is being closed
                running = 0;
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                // Connect a controller when it is connected
                SDL_OpenGamepad(event.cdevice.which);
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                if (event.gbutton.button == SDL_GAMEPAD_BUTTON_START)
                {
                    // Close the program if start is pressed
                    running = 0;
                }
                break;
            }
        }

        // [GAME]
        engine.update();

        // [RENDERING]
        render_background(renderer);

        auto &actors = engine.get_actors();

        for (auto &actor : actors)
        {
            auto &sprite = sprite_manager.get_sprite(actor.sprite);
            SDL_RenderTexture(renderer, sprite.get_texture(), NULL, &actor.ptr->get_rectangle());
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void render_sky(SDL_Renderer *renderer)
{
    using namespace PS::Game::Config;
    SDL_SetRenderDrawColor(renderer, SKY_COLOR_R, SKY_COLOR_G, SKY_COLOR_B, SKY_COLOR_A);
    SDL_RenderClear(renderer);
}

void render_ground(SDL_Renderer *renderer)
{
    using namespace PS::Game::Config;
    static SDL_FRect const ground_rectangle{0.0F, static_cast<float>(GROUND_LEVEL), static_cast<float>(SCREEN_WIDTH),
                                            static_cast<float>(SCREEN_HEIGHT - GROUND_LEVEL)};

    SDL_SetRenderDrawColor(renderer, GROUND_COLOR_R, GROUND_COLOR_G, GROUND_COLOR_B, GROUND_COLOR_A);
    SDL_RenderFillRect(renderer, &ground_rectangle);
}

void render_background(SDL_Renderer *renderer)
{
    render_sky(renderer);
    SDL_RenderClear(renderer);
    render_ground(renderer);
}