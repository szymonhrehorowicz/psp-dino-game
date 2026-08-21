#include "SDL3/SDL_rect.h"
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
    Game::Player player{};
    Game::Obstacle obstacle1{};
    Game::Obstacle obstacle2{{Game::Config::OBSTACLE_POSITION_X / 2, Game::Config::OBSTACLE_POSITION_Y / 2}};

    // Controls
    Game::Controller_Manager controller_manager{};

    // Scene
    System::Graphics::Sprite_Manager<Game::Config::Sprites> sprite_manager{*renderer};
    sprite_manager.make_sprite(Game::Config::Sprites::PLAYER, Game::Config::PLAYER_SPRITE);
    sprite_manager.make_sprite(Game::Config::Sprites::OBSTACLE, Game::Config::OBSTACLE_SPRITE);

    // Signals
    controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS).connect(&player, &Game::Player::jump);
    Library::Signal<> game_tick{};
    game_tick.connect(&obstacle1, &Game::Obstacle::move_left);
    game_tick.connect(&obstacle2, &Game::Obstacle::move_left);

    int running = 1;
    SDL_Event event;

    SDL_FRect player_rectangle{};
    SDL_FRect obstacle1_rectangle{};
    SDL_FRect obstacle2_rectangle{};

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
        obstacle1.animate();
        obstacle2.animate();

        auto const player_dimensions = sprite_manager.get_sprite(Game::Config::Sprites::PLAYER).get_dimensions();
        player_rectangle.w = player_dimensions.x;
        player_rectangle.h = player_dimensions.y;
        auto const player_position = player.get_position();
        player_rectangle.x = player_position.x;
        player_rectangle.y = player_position.y;

        auto const obstacle_dimensions = sprite_manager.get_sprite(Game::Config::Sprites::PLAYER).get_dimensions();
        obstacle1_rectangle.w = obstacle_dimensions.x;
        obstacle1_rectangle.h = obstacle_dimensions.y;
        obstacle2_rectangle.w = obstacle_dimensions.x;
        obstacle2_rectangle.h = obstacle_dimensions.y;
        auto const obstacle_1 = obstacle1.get_position();
        obstacle1_rectangle.x = obstacle_1.x;
        obstacle1_rectangle.y = obstacle_1.y;
        auto const obstacle_2 = obstacle2.get_position();
        obstacle2_rectangle.x = obstacle_2.x;
        obstacle2_rectangle.y = obstacle_2.y;

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw Actors
        auto &player_sprite = sprite_manager.get_sprite(Game::Config::Sprites::PLAYER);
        auto &obstacle_sprite = sprite_manager.get_sprite(Game::Config::Sprites::OBSTACLE);
        SDL_RenderTexture(renderer, player_sprite.get_texture(), NULL, &player_rectangle);
        SDL_RenderTexture(renderer, obstacle_sprite.get_texture(), NULL, &obstacle1_rectangle);
        SDL_RenderTexture(renderer, obstacle_sprite.get_texture(), NULL, &obstacle2_rectangle);

        // Draw everything on a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
