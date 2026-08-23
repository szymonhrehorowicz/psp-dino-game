#include "game/config.h"
#include "game/engine.h"
#include "game/graphics_engine.h"
#include "game/state_machine.h"
#include "system/exit.h"
#include <pspuser.h>

PSP_MODULE_INFO("DinoGame", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);

int main(int /*argc*/, char * /*argv*/[])
{
    using namespace PS;

    System::exit_init();

    Game::Controller_Manager controller_manager{};
    Game::State_Machine state_machine{controller_manager};
    Game::Graphics_Engine graphics_engine{};

    graphics_engine.clear_screen_color(0xFF0000); // solid red
    graphics_engine.present();
    // [SCENE]
    graphics_engine.load_sprite(Game::Config::Sprites::PLAYER, Game::Config::PLAYER_SPRITE);
    graphics_engine.load_sprite(Game::Config::Sprites::PLAYER_DEAD, Game::Config::PLAYER_DEAD_SPRITE);
    graphics_engine.load_sprite(Game::Config::Sprites::OBSTACLE, Game::Config::OBSTACLE_SPRITE);

    // [ENGINE]
    Game::Engine engine{controller_manager, graphics_engine.sprite_dimensions(Game::Config::Sprites::PLAYER),
                        graphics_engine.sprite_dimensions(Game::Config::Sprites::PLAYER_DEAD),
                        graphics_engine.sprite_dimensions(Game::Config::Sprites::OBSTACLE)};
    // engine.add_player();

    // [SIGNALS]
    engine.on_game_end().connect(&state_machine, &Game::State_Machine::set_game_ended);
    state_machine.on_game_start().connect(&engine, &Game::Engine::start_game);

    while (System::running)
    {
        controller_manager.update();
        state_machine.update();
        engine.update();
        graphics_engine.update(state_machine.get_state(), engine.get_actors(), engine.get_score());
        sceKernelDelayThread(32000);
    }

    return 0;
}