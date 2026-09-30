#include "MealyToMoorConverter.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

void MealyToMoorConverter::Convert(std::ifstream &input) {
    SkipUntillTransitions(input);
    const auto mialyLines = ParseMialyLines(input);
    InitMoorAndFillStateNames(mialyLines);
    FillMoorMap(mialyLines);
    PrintMoor();
}

void MealyToMoorConverter::SkipUntillTransitions(std::ifstream &input) {
    std::string line;
    while (std::getline(input, line)) {
        if (line == "transitions:") {
            return;;
        }
    }
}

std::vector<MealyToMoorConverter::MialyLine> MealyToMoorConverter::ParseMialyLines(std::ifstream &input) {
    std::vector<MialyLine> mialyLines;
    std::string line;

    while (std::getline(input, line)) {
        std::stringstream stream(line);
        std::string from, to, x, devider, y;
        if (!(stream >> from >> to >> x >> devider >> y)) {
            throw std::runtime_error("Could not read line" + line);
        }
        mialyLines.push_back({from, to, x, y});
    }
    return mialyLines;
}

void MealyToMoorConverter::InitMoorAndFillStateNames(const std::vector<MialyLine> &mialyLines) {
    for (const auto& mialyLine : mialyLines) {
        auto key = mialyLine.From + '_' + mialyLine.Y;
        if (m_stateNameMap.find(key) == m_stateNameMap.end()) {
            auto value = 'Z' + std::to_string(id++);
            m_stateNameMap[key] = value;
            m_moorMap[value] = {};
        }
    }
}

void MealyToMoorConverter::FillMoorMap(const std::vector<MialyLine> &mialyLines) {
    for (const auto& mialyLine : mialyLines) {
        auto fromKey = mialyLine.From + '_' + mialyLine.Y;
        auto toKey = mialyLine.To + '_' + mialyLine.Y;

        if (m_stateNameMap.find(toKey) == m_stateNameMap.end()) {
            auto value = 'Z' + std::to_string(id++);
            m_stateNameMap[toKey] = value;
            m_moorMap[value] = {};
        }

        m_moorMap[m_stateNameMap[fromKey]][mialyLine.X] = m_stateNameMap[toKey];
    }
}

void MealyToMoorConverter::PrintMoor() {
    for (const auto& [key, stateName] : m_stateNameMap) {
        std::cout << key << " - " << stateName << std::endl;
    }
    std::cout << std::endl;

    for (const auto& [state, transitions] : m_moorMap) {
        for (const auto& [input, nextState] : transitions) {
            std::cout << state << " -> " << input << " -> " << nextState << std::endl;
        }
    }
}




