#include <ctest.h>

#include <lib.hpp>

CTEST(wrapValue, testNegativeOne)
{
    const int v = -1;
    const int vMax = 10;
    const int expectedResult = vMax - 1;

    const int result = wrapValue(v, vMax);

    ASSERT_EQUAL(expectedResult, result);
}

CTEST(wrapValue, testMaxValue)
{
    const int v = 10;
    const int vMax = 10;
    const int expectedResult = 0;

    const int result = wrapValue(v, vMax);

    ASSERT_EQUAL(expectedResult, result);
}

CTEST(wrapValue, testNonWrappingValue)
{
    const int v = 5;
    const int vMax = 10;
    const int expectedResult = 5;

    const int result = wrapValue(v, vMax);

    ASSERT_EQUAL(expectedResult, result);
}
