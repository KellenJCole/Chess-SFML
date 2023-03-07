cmake_minimum_required(VERSION 3.21)
project(CMakeSFMLProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/KellenJCole/Chess-SFML/Chess-SFML.git/
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Chess src/main.cpp)
target_link_libraries(Chess-SFML PRIVATE sfml-graphics)
target_compile_features(Chess-SFML PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Chess-SFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Chess-SFML> $<TARGET_FILE_DIR:Chess-SFML> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Chess-SFML)
