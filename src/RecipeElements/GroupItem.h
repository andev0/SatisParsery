#pragma once

#include "RecipeItem.h"

class GroupItem : public RecipeItem
{
public:
    explicit GroupItem(std::string_view parent, const MxGeometryTag& geometry);
};
