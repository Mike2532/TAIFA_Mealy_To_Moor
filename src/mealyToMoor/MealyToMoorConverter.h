#ifndef TAIFA_MILLI_MYR_CONVERTER_MEALYTOMOORCONVERTER_H
#define TAIFA_MILLI_MYR_CONVERTER_MEALYTOMOORCONVERTER_H

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

class MealyToMoorConverter
{
public:
    void Convert(std::ifstream& input);
private:
    struct MialyLine
    {
        std::string From;
        std::string To;
        std::string X;
        std::string Y;
    };

    int id = 0;
    std::unordered_map<std::string, std::string> m_stateNameMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_moorMap;

    void SkipUntillTransitions(std::ifstream& input);

    std::vector<MialyLine> ParseMialyLines(std::ifstream& input);

    void InitMoorAndFillStateNames(const std::vector<MialyLine>& mialyLines);

    void FillMoorMap(const std::vector<MialyLine>& mialyLines);

    void PrintMoor();
};


#endif //TAIFA_MILLI_MYR_CONVERTER_MEALYTOMOORCONVERTER_H