cmake_minimum_required(VERSION 3.30)
project(TEP_AG)

set(CMAKE_CXX_STANDARD 20)

add_executable(TEP_AG main.cpp
        GroupingChallenge/GaussianGroupingEvaluatorFactory.cpp
        GroupingChallenge/Point.h
        GroupingChallenge/Point.cpp
        GroupingChallenge/Optimizer.h
        GroupingChallenge/Optimizer.cpp
        GroupingChallenge/GroupingEvaluator.h
        GroupingChallenge/GroupingEvaluator.cpp
        GroupingChallenge/GroupingChallenge.cpp
        GroupingChallenge/GaussianGroupingEvaluatorFactory.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0  # Możesz zmienić na najnowszą wersję
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_tests test.cpp test.cpp
        GroupingChallenge/GaussianGroupingEvaluatorFactory.cpp
        GroupingChallenge/Point.h
        GroupingChallenge/Point.cpp
        GroupingChallenge/Optimizer.h
        GroupingChallenge/Optimizer.cpp
        GroupingChallenge/GroupingEvaluator.h
        GroupingChallenge/GroupingEvaluator.cpp
        GroupingChallenge/GroupingChallenge.cpp
        GroupingChallenge/GaussianGroupingEvaluatorFactory.h
)
target_link_libraries(my_tests gtest gtest_main)
add_test(NAME MyTests COMMAND my_tests)