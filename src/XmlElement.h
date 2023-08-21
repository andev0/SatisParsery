#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>

class XmlElement
{
public:
    using Children = std::vector<std::unique_ptr<XmlElement>>;
    using Attributes = std::unordered_map<std::string, std::string>;

    explicit XmlElement(std::string_view type);

    const Children& getChildren() const;
    void appendChild(std::unique_ptr<XmlElement> child);

    const Attributes& getAttributes() const;
    void setAttribute(std::string_view attribute, std::string_view value);

    void print(std::ostream* outputStream, size_t tabulationLevel = 0) const;
    void printToFile(std::string_view filePath) const;

private:
    std::string m_type;
    Attributes m_attributes;
    Children m_children;
};
