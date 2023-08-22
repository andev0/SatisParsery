#include "XmlElement.h"

#include <cassert>
#include <fstream>

XmlElement::XmlElement(const std::string_view type)
    : m_type(type)
{ }

const XmlElement::Children& XmlElement::getChildren() const
{
    return m_children;
}

void XmlElement::appendChild(std::unique_ptr<XmlElement> child)
{
    m_children.push_back(std::move(child));
}

const XmlElement::Attributes& XmlElement::getAttributes() const
{
    return m_attributes;
}

void XmlElement::setAttribute(const std::string_view attribute,
                              const std::string_view value)
{
    m_attributes[attribute.data()] = value;
}

void XmlElement::print(std::ostream* outputStream, size_t tabulationLevel) const
{
    for (size_t i = 0; i < tabulationLevel; ++i)
    {
        *outputStream << "    ";
    }

    *outputStream << "<" << m_type;

    if (!m_attributes.empty())
    {
        *outputStream << " ";
    }

    for (const auto& [attributeName, attributeValue] : m_attributes)
    {
        *outputStream << attributeName << "=\"" << attributeValue << "\" ";
    }

    if (m_children.size() > 0)
    {
        *outputStream << ">\n";

        for (const auto& child : m_children)
        {
            child->print(outputStream, tabulationLevel + 1);
        }

        for (size_t i = 0; i < tabulationLevel; ++i)
        {
            *outputStream << "    ";
        }

        *outputStream << "</" << m_type << ">\n";
    }
    else
    {
        *outputStream << "/>\n";
    }
}

void XmlElement::printToFile(std::string_view filePath) const
{
    std::ofstream drawioOutput(filePath.data());
    print(&drawioOutput);
}
