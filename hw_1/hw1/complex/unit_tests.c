#include "complex.h"
#include "gtest/gtest.h"
#include <cmath>

namespace {

    TEST(Complex, BasicsAdd) {
        Complex a = { 2.0, 3.0 },
                b = { 4.0, 5.0 };
        EXPECT_DOUBLE_EQ(add(a, b).real, 6.0);
        EXPECT_DOUBLE_EQ(add(a, b).im, 8.0);
    }

    TEST(Complex, BasicsNegate) {
        Complex a = { 2.0, 3.0 };
        EXPECT_DOUBLE_EQ(negate(a).real, -2.0);
        EXPECT_DOUBLE_EQ(negate(a).im, -3.0);
    }

    TEST(Complex, BasicsMultiply) {
        Complex a = { 2.0, 3.0 },
                b = { 4.0, 5.0 };
        EXPECT_DOUBLE_EQ(multiply(a, b).real, -7.0);
        EXPECT_DOUBLE_EQ(multiply(a, b).im, 22.0);
    }

    TEST(Complex, BasicsMagnitude) {
        Complex a = { 3.0, 4.0 };
        EXPECT_DOUBLE_EQ(magnitude(a), 5.0);
    }

}  // namespace

