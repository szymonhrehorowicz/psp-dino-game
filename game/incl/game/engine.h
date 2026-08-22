#pragma once

#include "actor.h"
#include "controller_manager.h"
#include "game/config.h"
#include "game/obstacle.h"
#include "game/player.h"
#include "library/obstacle_position_generator.h"
#include "library/signal.h"
#include "system/graphics/sprite_manager.h"
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace PS::Game
{

class Engine
{
    using Sprites_Manager = System::Graphics::Sprite_Manager<Game::Config::Sprites>;

    struct Actor_Data
    {
        std::unique_ptr<Actor> ptr;
        Config::Sprites sprite;
        std::map<Config::Signals, int> signals;
    };

    using Actors = std::vector<Actor_Data>;

  public:
    Engine(Sprites_Manager const &sprites_manager) : m_sprites_manager(sprites_manager)
    {
        auto const obstacle_dimensions = m_sprites_manager.get_sprite(Config::Sprites::OBSTACLE).get_dimensions();
        auto const player_dimensions = m_sprites_manager.get_sprite(Config::Sprites::PLAYER).get_dimensions();

        m_obstacle_position_generator.set_period(100);
        m_obstacle_position_generator.set_starting_x(Config::SCREEN_WIDTH + obstacle_dimensions.x);

        int const lower_level = Config::OBSTACLE_POSITION_Y;
        int const upper_level = lower_level - player_dimensions.y;
        m_obstacle_position_generator.set_levels(lower_level, upper_level);
        m_obstacle_position_generator.on_new_obstacle().connect(this, &Engine::add_obstacle);
    };

    void update()
    {
        m_controller_manager.update();
        m_obstacle_position_generator.update();
        m_game_tick.emit();

        // Animations
        for (auto &actor : m_actors)
        {
            actor.ptr->animate();
        }

        // Cleanup
        for (auto it = m_actors.begin(); it != m_actors.end();)
        {
            if (it->sprite == Config::Sprites::OBSTACLE)
            {
                auto const &rectangle = it->ptr->get_rectangle();

                if (rectangle.x + rectangle.w <= 0)
                {
                    m_game_tick.disconnect(it->signals[Config::Signals::GAME_TICK]);
                    it = m_actors.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            else
            {
                ++it;
            }
        }
    }

    Actors const &get_actors() const
    {
        return m_actors;
    }

    void add_player()
    {
        auto player = std::make_unique<Player>();
        auto const sprite = Config::Sprites::PLAYER;

        auto const dimensions = m_sprites_manager.get_sprite(sprite).get_dimensions();
        player->set_dimensions(dimensions);

        m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
            .connect(player.get(), &Game::Player::jump);

        m_actors.emplace_back(Actor_Data{
            .ptr = std::move(player),
            .sprite = sprite,
            .signals = {},
        });
    }

    void add_obstacle(Library::Vector_2D position = {
                          Config::OBSTACLE_POSITION_X,
                          Config::OBSTACLE_POSITION_Y,
                      })
    {
        auto obstacle = std::make_unique<Obstacle>(position);
        auto const sprite = Config::Sprites::OBSTACLE;

        auto const dimensions = m_sprites_manager.get_sprite(sprite).get_dimensions();
        obstacle->set_dimensions(dimensions);

        int on_game_tick_id = m_game_tick.connect(obstacle.get(), &Obstacle::move_left);

        m_actors.emplace_back(Actor_Data{
            .ptr = std::move(obstacle),
            .sprite = sprite,
            .signals = {{Config::Signals::GAME_TICK, on_game_tick_id}},
        });
    }

  private:
    Sprites_Manager const &m_sprites_manager;
    Controller_Manager m_controller_manager{};
    Library::Obstacle_Position_Generator m_obstacle_position_generator{};

    Actors m_actors{};
    Library::Signal<> m_game_tick{};
};

} // namespace PS::Game