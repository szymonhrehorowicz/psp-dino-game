#include "game/config.h"
#include "game/engine.h"
#include "game/graphics_engine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int /*argc*/, char * /*argv*/[])
{
    using namespace PS;

    // [SDL]
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    Game::Graphics_Engine graphics_engine{};

    // [SCENE]
    graphics_engine.load_sprite(Game::Config::Sprites::PLAYER, Game::Config::PLAYER_SPRITE);
    graphics_engine.load_sprite(Game::Config::Sprites::PLAYER_DEAD, Game::Config::PLAYER_DEAD_SPRITE);
    graphics_engine.load_sprite(Game::Config::Sprites::OBSTACLE, Game::Config::OBSTACLE_SPRITE);

    // [ENGINE]
    Game::Engine engine{graphics_engine.sprite_dimensions(Game::Config::Sprites::PLAYER),
                        graphics_engine.sprite_dimensions(Game::Config::Sprites::PLAYER_DEAD),
                        graphics_engine.sprite_dimensions(Game::Config::Sprites::OBSTACLE)};
    engine.add_player();

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
        graphics_engine.update(engine.get_actors());
    }

    SDL_Quit();

    return 0;
}