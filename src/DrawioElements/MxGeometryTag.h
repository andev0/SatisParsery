#pragma once

#include "MxCellTag.h"

class MxGeometryTag : public XmlElement
{
public:
    MxGeometryTag();
    MxGeometryTag(double x, double y, double width, double height);

    MxGeometryTag(const MxGeometryTag& other);
    MxGeometryTag& operator=(const MxGeometryTag& other) = default;

    ~MxGeometryTag() = default;

    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

private:
    double m_x;
    double m_y;
    double m_width;
    double m_height;
};
