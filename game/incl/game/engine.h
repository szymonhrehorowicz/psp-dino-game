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

#include "actor.h"
#include "controller_manager.h"
#include "engine_defines.h"
#include "game/collision_detector.h"
#include "game/config.h"
#include "game/obstacle.h"
#include "game/player.h"
#include "library/coordinates.h"
#include "library/obstacle_position_generator.h"
#include "library/signal.h"
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace PS::Game
{

/**
 * @brief Game Engine
 *
 */
class Engine
{
  public:
    Engine(Library::Vector_2D player_dimensions, Library::Vector_2D dead_player_dimensions,
           Library::Vector_2D obstacle_dimensions)
        : m_player_dimensions(player_dimensions), m_dead_player_dimensions(dead_player_dimensions),
          m_obstacle_dimensions(obstacle_dimensions)
    {
        m_obstacle_position_generator.set_period(100);
        m_obstacle_position_generator.set_starting_x(Config::SCREEN_WIDTH + obstacle_dimensions.x);

        int const lower_level = Config::OBSTACLE_POSITION_Y;
        int const upper_level = lower_level - m_player_dimensions.y;
        m_obstacle_position_generator.set_levels(lower_level, upper_level);
        m_obstacle_position_generator.on_new_obstacle().connect(this, &Engine::add_obstacle);
    };

    /**
     * @brief Update state of the game engine.
     *
     */
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

        // Collisions
        m_collision_detector.update(m_actors);

        // Cleanup
        for (auto it = m_actors.begin(); it != m_actors.end();)
        {
            if (it->ptr->get_sprite() == Config::Sprites::OBSTACLE)
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

    /**
     * @brief Get vector of data associated with each existing Actor
     *
     * @return Actors const&
     */
    Actors const &get_actors() const
    {
        return m_actors;
    }

    /**
     * @brief Add player.
     *
     */
    void add_player()
    {
        auto player = std::make_unique<Player>(m_dead_player_dimensions);

        player->set_dimensions(m_player_dimensions);

        m_controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS)
            .connect(player.get(), &Game::Player::jump);

        int const on_collision_id = m_collision_detector.on_collision().connect(player.get(), &Player::die);

        m_actors.emplace_back(Actor_Data{
            .ptr = std::move(player),
            .signals = {{Config::Signals::COLLISION, on_collision_id}},
        });
    }

  private:
    /**
     * @brief Add new obstacle.
     *
     * @param position - (optional) position where the obstacle is to be created
     */
    void add_obstacle(Library::Vector_2D position = {
                          Config::OBSTACLE_POSITION_X,
                          Config::OBSTACLE_POSITION_Y,
                      })
    {
        auto obstacle = std::make_unique<Obstacle>(position);

        obstacle->set_dimensions(m_obstacle_dimensions);

        int const on_game_tick_id = m_game_tick.connect(obstacle.get(), &Obstacle::move_left);

        m_actors.emplace_back(Actor_Data{
            .ptr = std::move(obstacle),
            .signals = {{Config::Signals::GAME_TICK, on_game_tick_id}},
        });
    }

    Library::Vector_2D m_player_dimensions;
    Library::Vector_2D m_dead_player_dimensions;
    Library::Vector_2D m_obstacle_dimensions;

    Controller_Manager m_controller_manager{};
    Library::Obstacle_Position_Generator m_obstacle_position_generator{};
    Collision_Detector<Game::Config::SCREEN_WIDTH, Game::Config::SCREEN_HEIGHT> m_collision_detector{};

    Actors m_actors{};
    Library::Signal<> m_game_tick{};
};

} // namespace PS::Game