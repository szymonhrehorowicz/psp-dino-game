#include "library/obstacle_position_generator.h"
#include <gtest/gtest.h>

namespace PS::Testing
{

TEST(ObstaclePositionGenerator, DoesNotEmitBeforePeriod)
{
    Library::Obstacle_Position_Generator generator{};
    int obstacles_generated{0};

    generator.set_period(3);
    generator.on_new_obstacle().connect([&obstacles_generated](Library::Vector_2D) { ++obstacles_generated; });

    generator.update();
    generator.update();

    EXPECT_EQ(obstacles_generated, 0);
}

TEST(ObstaclePositionGenerator, EmitsAtEachPeriod)
{
    Library::Obstacle_Position_Generator generator{};
    int obstacles_generated{0};

    generator.set_period(3);
    generator.on_new_obstacle().connect([&obstacles_generated](Library::Vector_2D) { ++obstacles_generated; });

    for (int i = 0; i < 6; ++i)
    {
        generator.update();
    }

    EXPECT_EQ(obstacles_generated, 2);
}

TEST(ObstaclePositionGenerator, GeneratesConfiguredStartingPositions)
{
    Library::Obstacle_Position_Generator generator{};
    int const starting_x{400};
    int const lower_level{200};
    int const upper_level{150};
    int generated{0};

    generator.set_period(1);
    generator.set_starting_x(starting_x);
    generator.set_levels(lower_level, upper_level);
    generator.on_new_obstacle().connect([&](Library::Vector_2D position) {
        ++generated;
        EXPECT_FLOAT_EQ(position.x, starting_x);
        EXPECT_TRUE(position.y == lower_level || position.y == upper_level);
    });

    for (int i = 0; i < 10; ++i)
    {
        generator.update();
    }

    EXPECT_EQ(generated, 10);
}

} // namespace PS::Testing