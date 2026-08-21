#include "game/config.h"
#include "game/controller_manager.h"
#include "game/obstacle.h"
#include "game/player.h"
#include "library/signal.h"
#include "system/graphics/sprite_manager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    using namespace PS;

    // This prevents compiler warnings
    // We don't actually need these variables, but they do need to be there so SDL_main works
    (void)argc;
    (void)argv;

    // Initialize sdl
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("window", 480, 272, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    // Actors
    Game::Player player{*renderer};
    Game::Obstacle obstacle{*renderer};

    // Controls
    Game::Controller_Manager controller_manager{};

    // Scene
    System::Graphics::Sprite_Manager<Game::Config::Sprites> sprite_manager{*renderer};
    sprite_manager.make_sprite(Game::Config::Sprites::PLAYER, Game::Config::PLAYER_SPRITE,
                               {Game::Config::PLAYER_POSITION_X, Game::Config::PLAYER_POSITION_Y});
    sprite_manager.make_sprite(Game::Config::Sprites::OBSTACLE, Game::Config::OBSTACLE_SPRITE,
                               {Game::Config::OBSTACLE_POSITION_X, Game::Config::OBSTACLE_POSITION_Y});

    // Signals
    controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS).connect(&player, &Game::Player::jump);
    Library::Signal<> game_tick{};
    game_tick.connect(&obstacle, &Game::Obstacle::move_left);

    int running = 1;
    SDL_Event event;
    while (running)
    {

        // Process input
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

        // Game
        controller_manager.update();
        game_tick.emit();

        player.animate();
        obstacle.animate();

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw Actors
        SDL_RenderTexture(renderer, player.get_sprite().get_texture(), NULL, player.get_sprite().get_rectangle());
        SDL_RenderTexture(renderer, obstacle.get_sprite().get_texture(), NULL, obstacle.get_sprite().get_rectangle());

        // Draw everything on a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
