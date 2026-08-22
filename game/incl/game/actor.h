/**
 * @file actor.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "SDL3/SDL_rect.h"
#include "config.h"
#include "library/action.h"
#include "library/coordinates.h"
#include <memory>
#include <vector>

namespace PS::Game
{

/**
 * @brief Base class for all actors. Actor is responsible for executing different actions.
 * Actions can, between others, modify the rectangle of an Actor.
 *
 */
class Actor
{
  public:
    /**
     * @brief Construct a new Actor object
     *
     * @param rectangle - inital rectangle of an Actor
     */
    explicit Actor(SDL_FRect rectangle, Config::Sprites sprite) : m_rectangle(rectangle), m_sprite(sprite) {};

    /**
     * @brief Executes registered action if any in the queue.
     * If action is finished, it is removed from the queue.
     *
     */
    virtual void animate()
    {
        if (m_actions.empty())
        {
            return;
        }

        auto const &action = m_actions.front();
        action->execute();

        if (action->is_finished())
        {
            m_actions.erase(m_actions.begin());
        }
    };

    void set_dimensions(Library::Vector_2D dimensions)
    {
        m_rectangle.w = dimensions.x;
        m_rectangle.h = dimensions.y;
        m_rectangle.x -= dimensions.x;
        m_rectangle.y -= dimensions.y;
    }

    /**
     * @brief Get (X,Y,W,H) rectangle of an Actor
     *
     * @return SDL_FRect const&
     */
    SDL_FRect const &get_rectangle() const
    {
        return m_rectangle;
    }

    /**
     * @brief Get (X,Y,W,H) rectangle of an Actor
     *
     * @return SDL_FRect&
     */
    SDL_FRect &get_rectangle()
    {
        return m_rectangle;
    }

    Config::Sprites &get_sprite()
    {
        return m_sprite;
    }

  protected:
    /**
     * @brief Is Actor currently executing some action
     *
     * @return true
     * @return false
     */
    bool has_active_action() const
    {
        return !m_actions.empty();
    }

    /**
     * @brief Request actor to execute an action
     *
     * @param action
     */
    void request_action(std::unique_ptr<Library::Action> action)
    {
        m_actions.push_back(std::move(action));
    }

  private:
    SDL_FRect m_rectangle;
    Config::Sprites m_sprite;
    std::vector<std::unique_ptr<Library::Action>> m_actions{};
};

} // namespace PS::Game