#pragma once

#include "XmlElement.h"

class MxCellTag : public XmlElement
{
public:
    explicit MxCellTag(std::string_view parent = "");

    const std::string& getId() const;

    static std::string generateId();

private:
    std::string m_id {generateId()};
};
