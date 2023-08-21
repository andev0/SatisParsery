#include "MxGeometryTag.h"

MxGeometryTag::MxGeometryTag()
    : MxGeometryTag(0, 0, 0, 0)
{ }

MxGeometryTag::MxGeometryTag(const double x,
                             const double y,
                             const double width,
                             const double height)
    : XmlElement("mxGeometry")
    , m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
{
    setAttribute("x", std::to_string(x));
    setAttribute("y", std::to_string(y));
    setAttribute("width", std::to_string(width));
    setAttribute("height", std::to_string(height));

    setAttribute("as", "geometry");
}

MxGeometryTag::MxGeometryTag(const MxGeometryTag& other)
    : MxGeometryTag(other.m_x, other.m_y, other.m_width, other.m_height)
{ }

double MxGeometryTag::getX() const
{
    return m_x;
}

double MxGeometryTag::getY() const
{
    return m_y;
}

double MxGeometryTag::getWidth() const
{
    return m_width;
}

double MxGeometryTag::getHeight() const
{
    return m_height;
}

void MxGeometryTag::setX(double x)
{
    m_x = x;
}

void MxGeometryTag::setY(double y)
{
    m_y = y;
}

void MxGeometryTag::setWidth(double width)
{
    m_width = width;
}

void MxGeometryTag::setHeight(double height)
{
    m_height = height;
}
