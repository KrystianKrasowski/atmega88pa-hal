include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.0
)

FetchContent_Declare(
    avrhal
    GIT_REPOSITORY https://github.com/KrystianKrasowski/avrhal.git
    GIT_TAG release/3.2.0
)

FetchContent_MakeAvailable(unity)
FetchContent_MakeAvailable(avrhal)
