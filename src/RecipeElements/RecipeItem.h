#include "DrawioElements/MxGeometryTag.h"

class RecipeItem : public MxCellTag
{
public:
    RecipeItem(std::string_view parent,
               std::string_view text,
               std::string_view style,
               const MxGeometryTag& geometry);
};
