#include <fstream>
#include <stdexcept>

#include "src/mealyToMoor/MealyToMoorConverter.h"
#include "src/moorToMealyConverter/MoorToMealyConverter.h"

int main()
{
    std::ifstream file("../Input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    getline(file, line);
    if (line == "type: mealy") {
        auto converter = MealyToMoorConverter();
        converter.Convert(file);
    } else if (line == "type: moor") {
        auto converter = MoorToMealyConverter();
        converter.Convert(file);
    } else {
        file.close();
        throw std::runtime_error("can not recogize input type");
    }
    file.close();
}
