#pragma once

#include "actor.h"
#include "game/config.h"
#include "game/obstacle.h"
#include "game/player.h"
#include "library/signal.h"
#include "system/graphics/sprite_manager.h"
#include <memory>
#include <utility>
#include <vector>

namespace PS::Game
{

class Engine
{
    using Sprites_Manager = System::Graphics::Sprite_Manager<Game::Config::Sprites>;

    struct Actor_Sprite_Association
    {
        std::unique_ptr<Actor> ptr;
        Config::Sprites sprite;
    };

    using Actors = std::vector<Actor_Sprite_Association>;

  public:
    Engine(Sprites_Manager const &sprites_manager) : m_sprites_manager(sprites_manager) {};

    void update()
    {
        m_game_tick.emit();

        for (auto &actor : m_actors)
        {
            actor.ptr->animate();
        }
    }

    void add_player()
    {
        auto player = std::make_unique<Player>();
        auto const sprite = Config::Sprites::PLAYER;

        auto const dimensions = m_sprites_manager.get_sprite(sprite).get_dimensions();
        player->set_dimensions(dimensions);

        m_actors.emplace_back(Actor_Sprite_Association{
            .ptr = std::move(player),
            .sprite = sprite,
        });
    }

    void add_obstacle(System::Vector_2D position = {
                          Config::OBSTACLE_POSITION_X,
                          Config::OBSTACLE_POSITION_Y,
                      })
    {
        auto obstacle = std::make_unique<Obstacle>(position);
        auto const sprite = Config::Sprites::OBSTACLE;

        auto const dimensions = m_sprites_manager.get_sprite(sprite).get_dimensions();
        obstacle->set_dimensions(dimensions);

        m_game_tick.connect(obstacle.get(), &Obstacle::move_left);

        m_actors.emplace_back(Actor_Sprite_Association{
            .ptr = std::move(obstacle),
            .sprite = sprite,
        });
    }

    Actors &get_actors()
    {
        return m_actors;
    }

  private:
    Actors m_actors{};

    Sprites_Manager const &m_sprites_manager;

    Library::Signal<> m_game_tick{};
};

} // namespace PS::Game