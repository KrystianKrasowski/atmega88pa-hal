#define RUN_PARAM_TEST(TestFunc, ...)                                          \
    {                                                                          \
        Unity.CurrentTestName       = #TestFunc "(" #__VA_ARGS__ ")";          \
        Unity.CurrentTestLineNumber = __LINE__;                                \
        Unity.NumberOfTests++;                                                 \
        if (TEST_PROTECT())                                                    \
        {                                                                      \
            setUp();                                                           \
            TestFunc(__VA_ARGS__);                                             \
        }                                                                      \
        if (TEST_PROTECT())                                                    \
        {                                                                      \
            tearDown();                                                        \
        }                                                                      \
        UnityConcludeTest();                                                   \
    }

#define TEST_ASSERT_BIT_STATE_MESSAGE(index, expected, actual, message)        \
    TEST_ASSERT_EQUAL_MESSAGE(                                                 \
        (expected >> index) & 1, (actual >> index) & 1, message)