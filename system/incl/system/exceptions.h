/**
 * @file exceptions.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <exception>

namespace PS::System
{

class Graphics_Exception : public std::exception
{
  public:
    explicit Graphics_Exception(const char *message) : m_message(message)
    {
    }

    const char *what() const noexcept override
    {
        return m_message;
    }

  private:
    const char *m_message;
};

} // namespace PS::System
