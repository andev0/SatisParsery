#include "RecipeItem.h"

RecipeItem::RecipeItem(const std::string_view parent,
                       const std::string_view text,
                       const std::string_view style,
                       const MxGeometryTag& geometry)
    : MxCellTag(parent)
{
    setAttribute("parent", parent);
    setAttribute("value", text);
    setAttribute("style", style);
    setAttribute("vertex", "1");

    appendChild(std::make_unique<MxGeometryTag>(geometry));
}
