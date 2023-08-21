#include "GroupItem.h"

GroupItem::GroupItem(const std::string_view parent, const MxGeometryTag& geometry)
    : RecipeItem(parent, "", "group", geometry)
{ }
