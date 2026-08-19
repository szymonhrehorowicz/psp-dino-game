#include "library/signal.h"
#include <gtest/gtest.h>

namespace PS::Testing
{

TEST(Signal, SingleSlot)
{
    Library::Signal<bool> signal;

    bool test_flag{false};

    signal.connect([&test_flag](bool flag) { EXPECT_EQ(test_flag, flag); });

    signal.emit(test_flag);

    test_flag = true;
    signal.emit(test_flag);
}

TEST(Signal, MultipleSlots)
{
    Library::Signal<bool> signal;

    bool slot_positive_flag{false};
    bool slot_negative_flag{false};

    // Positive slot
    signal.connect([&slot_positive_flag](bool flag) { slot_positive_flag = flag; });
    // Negative slot
    signal.connect([&slot_negative_flag](bool flag) { slot_negative_flag = !flag; });

    signal.emit(true);
    EXPECT_TRUE(slot_positive_flag);
    EXPECT_FALSE(slot_negative_flag);

    signal.emit(false);
    EXPECT_FALSE(slot_positive_flag);
    EXPECT_TRUE(slot_negative_flag);
}

TEST(Signal, OneSpecificSlot)
{
    Library::Signal<bool> signal;

    bool slot_positive_flag{false};
    bool slot_negative_flag{false};

    // Positive slot
    auto const positive_slot = signal.connect([&slot_positive_flag](bool flag) { slot_positive_flag = flag; });
    // Negative slot
    auto const negative_slot = signal.connect([&slot_negative_flag](bool flag) { slot_negative_flag = !flag; });

    signal.emit(positive_slot, true);
    EXPECT_TRUE(slot_positive_flag);
    EXPECT_FALSE(slot_negative_flag);

    signal.emit(positive_slot, false);
    EXPECT_FALSE(slot_positive_flag);
    EXPECT_FALSE(slot_negative_flag);

    signal.emit(negative_slot, true);
    EXPECT_FALSE(slot_positive_flag);
    EXPECT_FALSE(slot_negative_flag);

    signal.emit(negative_slot, false);
    EXPECT_FALSE(slot_positive_flag);
    EXPECT_TRUE(slot_negative_flag);
}

} // namespace PS::Testing