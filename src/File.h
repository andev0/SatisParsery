#pragma once

#include <fstream>

#include "Logging.h"

bool readLine(std::string_view filePath, std::string& line);

std::string readFile(std::string_view filePath);

template<class Collection>
void writeToFile(std::string_view filePath, Collection collection)
{
    std::ofstream outputFile(filePath.data());

    if (!outputFile.is_open())
    {
        LOG_ERROR("Couldn't open the output file \"" << filePath << "\"");
    }

    for (const auto& item : collection)
    {
        outputFile << item << "\n";
    }
}
