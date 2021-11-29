// Test cases for the antichattering class

#include "gtest/gtest.h"
#include "antichattering.hpp"
#include <stdexcept>

namespace rpn_engine
{

    void dummy(int a, int b){};

    // Checking null pointer triggers assertion
    TEST(AntiChattering, ConstructorWrongPtr)
    {
        ASSERT_DEATH(AntiChattering ac(10, 10, nullptr, 9, 3), "nullptr != key_pressed_call_back_");
    }

    // Checking null pointer triggers assertion
    TEST(AntiChattering, ConstructorWrongLHThreshold)
    {
        // lh_threashold must be greater than zero
        ASSERT_DEATH(AntiChattering ac(1, 0, dummy, 9, 3),
                     "lh_threashold_ > 0");
    }

    // Checking null pointer triggers assertion
    TEST(AntiChattering, ConstructorWrongHLThreshold)
    {

        // hl_threashold must be greater than zero
        ASSERT_DEATH(AntiChattering ac(0, 1, dummy, 9, 3),
                     "hl_threashold_ > 0");
    }

}
