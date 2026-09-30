cmake_minimum_required(VERSION 4.0)
project(TAIFA_Milli_Myr_converter)

set(CMAKE_CXX_STANDARD 20)

add_executable(TAIFA_Milli_Myr_converter main.cpp
        src/mealyToMoor/MealyToMoorConverter.cpp
        src/mealyToMoor/MealyToMoorConverter.h
        src/moorToMealyConverter/MoorToMealyConverter.cpp
        src/moorToMealyConverter/MoorToMealyConverter.h)
