// Test cases for the antichattering class

#include "gtest/gtest.h"
#include "rpnengine.hpp"
#include <stdexcept>

namespace rpn_engine
{
    bool key_pressed = false;
    unsigned raw;
    unsigned int col;
    void CallBackStub(unsigned a, unsigned b)
    {
        key_pressed = true;
        raw = a;
        col = b;
    }

    // Checking null pointer triggers assertion
    TEST(AntiChatteringDeathTest, ConstructorWrongPtr)
    {
#ifndef NDEBUG
        // We test only when assert() works.
        ASSERT_DEATH(AntiChattering ac(10, 10, nullptr, 9, 3), "nullptr != key_pressed_call_back_");
#endif
    }

    // Checking null pointer triggers assertion
    TEST(AntiChatteringDeathTest, ConstructorWrongLHThreshold)
    {
#ifndef NDEBUG
        // We test only when assert() works.
        // lh_threashold must be greater than zero
        ASSERT_DEATH(AntiChattering ac(2, 0, &CallBackStub, 9, 3),
                     "lh_threashold_ > 1");
#endif
    }

    // Checking null pointer triggers assertion
    TEST(AntiChatteringDeathTest, ConstructorWrongHLThreshold)
    {
#ifndef NDEBUG
        // We test only when assert() works.
        // hl_threashold must be greater than zero
        ASSERT_DEATH(AntiChattering ac(0, 2, &CallBackStub, 9, 3),
                     "hl_threashold_ > 1");
#endif
    }

    // Checking Simple turn on
    TEST(AntiChattering, SimpleTansit)
    {
        key_pressed = false;
        rpn_engine::AntiChattering ac(
            2, // H->L threashold
            5, // L->H threashold
            &CallBackStub,
            9,  // row
            3); // col

        // 5 continuous H makes transition to H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        EXPECT_EQ(key_pressed, false);
        ac.Input(rpn_engine::KeyLevel::high);
        EXPECT_EQ(key_pressed, true);
        // Check the call back parameters are OK
        EXPECT_EQ(raw, 9);
        EXPECT_EQ(col, 3);
    }

    // Checking short High strobe is killed
    TEST(AntiChattering, DiscontinuedH)
    {
        key_pressed = false;
        rpn_engine::AntiChattering ac(
            2, // H->L threashold
            5, // L->H threashold
            &CallBackStub,
            9,  // row
            3); // col

        // 5 discontinued H doesn't make transition to H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low);  // Chattering
        ac.Input(rpn_engine::KeyLevel::high); // It must be still L state.
        EXPECT_EQ(key_pressed, false);
    }

    // Checking Long H make key pressed event only once.
    TEST(AntiChattering, VeryLongH)
    {
        key_pressed = false;
        rpn_engine::AntiChattering ac(
            2, // H->L threashold
            5, // L->H threashold
            &CallBackStub,
            9,  // row
            3); // col

        // During H, short strobe of L doesn't make transition.
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // Transit to H by fifth High input
        EXPECT_EQ(key_pressed, true);
        key_pressed = false;
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // The fifth High input doesn't make key_pressed event.
        EXPECT_EQ(key_pressed, false);
    }
    // Checking short L strobe is killed
    TEST(AntiChattering, ShortLKilled)
    {
        key_pressed = false;
        rpn_engine::AntiChattering ac(
            2, // H->L threashold
            5, // L->H threashold
            &CallBackStub,
            9,  // row
            3); // col

        // During H, short strobe of L doesn't make transition.
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // Transit to H by fifth High input
        EXPECT_EQ(key_pressed, true);
        key_pressed = false;
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // The fifth High input doesn't make key_pressed event.
        EXPECT_EQ(key_pressed, false);
    }

    // Detection of anti chattering L
    TEST(AntiChattering, AntiChatteringL)
    {
        key_pressed = false;
        rpn_engine::AntiChattering ac(
            2, // H->L threashold
            5, // L->H threashold
            &CallBackStub,
            9,  // row
            3); // col

        // During H, short strobe of L doesn't make transition.
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // Transit to H by fifth High input
        EXPECT_EQ(key_pressed, true);
        key_pressed = false;
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::low); // Still level is H
        ac.Input(rpn_engine::KeyLevel::low); // Now level is L
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high);
        ac.Input(rpn_engine::KeyLevel::high); // Not yeat transit to H
        EXPECT_EQ(key_pressed, false);
        ac.Input(rpn_engine::KeyLevel::high); // The fifth High input  makes key_pressed event.
        EXPECT_EQ(key_pressed, true);
    }
}