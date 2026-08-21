#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace PS::Library
{

template <typename Enum, typename Value> class Enum_Array
{
    static_assert(std::is_enum_v<Enum>, "Enum_Array requires an enum type");
    static_assert(!std::is_convertible_v<Enum, std::underlying_type_t<Enum>>,
                  "Enum_Array requires a scoped enum class");

  public:
    using enum_type = Enum;
    using value_type = Value;
    using size_type = std::size_t;

    static constexpr size_type count = static_cast<size_type>(Enum::LAST);

    constexpr Value &operator[](Enum index)
    {
        return m_values[static_cast<size_type>(index)];
    }

    constexpr Value const &operator[](Enum index) const
    {
        return m_values[static_cast<size_type>(index)];
    }

    Value &at(Enum index)
    {
        auto const position = static_cast<size_type>(index);
        if (position >= count)
        {
            throw std::out_of_range("Enum_Array index out of range");
        }

        return m_values[position];
    }

    Value const &at(Enum index) const
    {
        auto const position = static_cast<size_type>(index);
        if (position >= count)
        {
            throw std::out_of_range("Enum_Array index out of range");
        }

        return m_values[position];
    }

    constexpr size_type size() const noexcept
    {
        return count;
    }

    constexpr auto begin() noexcept
    {
        return m_values.begin();
    }

    constexpr auto begin() const noexcept
    {
        return m_values.begin();
    }

    constexpr auto end() noexcept
    {
        return m_values.end();
    }

    constexpr auto end() const noexcept
    {
        return m_values.end();
    }

  private:
    std::array<Value, count> m_values{};
};

} // namespace PS::Library