#ifndef TAIFA_MILLI_MYR_CONVERTER_MOORTOMEALYCONVERTER_H
#define TAIFA_MILLI_MYR_CONVERTER_MOORTOMEALYCONVERTER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

class MoorToMealyConverter
{
public:
    void Convert(std::ifstream& input) {
        SkipUntillStates(input);
        FillStateAction(input);
        FillMooreResult(input);
        Print();
    }
private:
    std::unordered_map<std::string, std::string> m_stateAction;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_mooreResult;

    void SkipUntillStates(std::ifstream& input) {
        std::string line;
        while (std::getline(input, line)) {
            if (line == "states:") {
                break;
            }
        }
    }

    void FillStateAction(std::ifstream& input) {
        std::string line;
        while (std::getline(input, line)) {
            if (line == "transitions:") {
                break;
            }
            if (line.empty()) {
                continue;
            }

            std::stringstream stream(line);
            std::string stateName, pipe, internalId, slash, output;
            if (!(stream >> stateName >> pipe >> internalId >> slash >> output)) {
                throw std::runtime_error("Could not parse state line: " + line);
            }
            m_stateAction[stateName] = output;
        }
    }

    void FillMooreResult(std::ifstream& input) {
        std::string line;
        while (std::getline(input, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream stream(line);
            std::string from, to, x;

            if (stream >> from >> to >> x) {
                m_mooreResult[from][x] = to;
            } else {
                throw std::runtime_error("Could not parse transition line: " + line);
            }
        }
    }

    void Print() {
        for (const auto& [fromState, inputsMap] : m_mooreResult) {
            for (const auto& [inputX, toState] : inputsMap) {
                std::cout << fromState << " -> " << inputX  + '_' + m_stateAction.at(fromState) << " -> " << toState << std::endl;
            }
        }
    }
};


#endif //TAIFA_MILLI_MYR_CONVERTER_MOORTOMEALYCONVERTER_H