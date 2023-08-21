#pragma once

#include "XmlElement.h"

class DiagramTag : public XmlElement
{
public:
    explicit DiagramTag(std::string_view pageName);

    std::string_view getPageName() const;

private:
    std::string m_pageName;
};
