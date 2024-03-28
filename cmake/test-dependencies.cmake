include(FetchContent)

option(${UNITY_EXTENSION_FIXTURE} ON)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.0
)

FetchContent_MakeAvailable(unity)
