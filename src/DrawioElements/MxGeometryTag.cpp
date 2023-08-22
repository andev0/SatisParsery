#include "MxGeometryTag.h"

#include "Algorithms.h"

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
    setAttribute("x", doubleToString(x));
    setAttribute("y", doubleToString(y));
    setAttribute("width", doubleToString(width));
    setAttribute("height", doubleToString(height));

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

void MxGeometryTag::setX(const double x)
{
    m_x = x;
}

void MxGeometryTag::setY(const double y)
{
    m_y = y;
}

void MxGeometryTag::setWidth(const double width)
{
    m_width = width;
}

void MxGeometryTag::setHeight(const double height)
{
    m_height = height;
}
