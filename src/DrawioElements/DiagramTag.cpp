#include "DiagramTag.h"

#include "MxCellTag.h"

DiagramTag::DiagramTag(const std::string_view pageName)
    : XmlElement("diagram")
{
    setAttribute("id", MxCellTag::generateId());
    setAttribute("name", pageName);
}

std::string_view DiagramTag::getPageName() const
{
    return m_pageName;
}
