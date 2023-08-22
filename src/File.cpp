#include "File.h"

bool readLine(const std::string_view filePath, std::string& line)
{
    static std::string lastFile = "";
    static std::ifstream inputFile;

    if (lastFile != filePath)
    {
        inputFile.close();

        inputFile.open(filePath.data());

        if (!inputFile.is_open())
        {
            LOG_ERROR("Couldn't open the input file \"" << filePath << "\".");
        }

        lastFile = filePath;
    }

    if (std::getline(inputFile, line))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string readFile(const std::string_view filePath)
{
    std::string fileContent;
    std::string line;

    while (readLine(filePath, line))
    {
        fileContent += line + "\n";
    }

    return fileContent;
}
