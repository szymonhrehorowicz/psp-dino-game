#include "library/edge_detector.h"
#include <gtest/gtest.h>

namespace PS::Testing
{

TEST(EdgeDetector, StartsWithoutAnEdge)
{
    Library::Edge_Detector detector;

    EXPECT_FALSE(detector.is_rising());
    EXPECT_FALSE(detector.is_falling());
}

TEST(EdgeDetector, DetectsRisingEdge)
{
    Library::Edge_Detector detector;

    EXPECT_TRUE(detector.update(true));
    EXPECT_TRUE(detector.is_rising());
    EXPECT_FALSE(detector.is_falling());
}

TEST(EdgeDetector, DetectsFallingEdge)
{
    Library::Edge_Detector detector;

    detector.update(true);

    EXPECT_TRUE(detector.update(false));
    EXPECT_FALSE(detector.is_rising());
    EXPECT_TRUE(detector.is_falling());
}

TEST(EdgeDetector, ClearsEdgeFlagsWhenStateDoesNotChange)
{
    Library::Edge_Detector detector;

    detector.update(true);
    EXPECT_TRUE(detector.is_rising());

    EXPECT_FALSE(detector.update(true));
    EXPECT_FALSE(detector.is_rising());
    EXPECT_FALSE(detector.is_falling());
}

} // namespace PS::Testing
