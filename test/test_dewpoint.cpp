#include "unity.h"
#include "dht22.h"

void setUp() {}

void tearDown() {}

void test_dewpoint() {
    float dp = dewPoint(30, 30);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 10.5, dp);
}

int runUnityTests() {
    UNITY_BEGIN();
    RUN_TEST(test_dewpoint);
    return UNITY_END();
}
