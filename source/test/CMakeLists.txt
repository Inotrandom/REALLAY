project(REALLAYTest)

add_executable(
    ${PROJECT_NAME}
    test.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ..
)