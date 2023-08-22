#include "XmlRecipe.h"

#include "GroupItem.h"
#include "Logging.h"

#include "Algorithms.h"

XmlRecipe::XmlRecipe(const std::string_view parentId,
                     const size_t recipeIndex,
                     const Items& ingredients,
                     const std::string_view buildingName,
                     const Items& products,
                     Configuration& config)
    : r_config(config)
{
    const auto maxItemsCount = std::max(ingredients.size(), products.size());

    const auto groupWidth = s_basicElementWidth * maxItemsCount
                            + s_basicElementsSpacing * (maxItemsCount - 1);

    generateGroupElement(parentId, recipeIndex, groupWidth);

    generateItemElements(ingredients, m_ingredientsElements, groupWidth, 0,
                         ItemType::Ingredient);

    generateBuildingElement(buildingName.data(), groupWidth);

    generateItemElements(products, m_productsElements, groupWidth,
                         s_basicElementHeight * 2, ItemType::Product);
}

std::vector<XmlRecipe::Item> XmlRecipe::acquireItems(const nlohmann::json& recipe,
                                                     std::string_view listName,
                                                     const double outputsCountInMinute)
{
    std::vector<XmlRecipe::Item> result;

    for (const auto& element : recipe[listName])
    {
        const double itemsCount = element["amount"];

        const std::string itemName = element["item"];

        result.push_back({itemName, itemsCount * outputsCountInMinute});
    }

    return result;
}

void XmlRecipe::appendTo(XmlElement& element)
{
    if (isMovedOut)
    {
        LOG_ERROR("XmlRecipe::appendTo can't be called twice");
    }

    element.appendChild(std::move(m_groupElement));

    for (auto& ingredient : m_ingredientsElements)
    {
        element.appendChild(std::move(ingredient));
    }

    element.appendChild(std::move(m_buildingElement));

    for (auto& product : m_productsElements)
    {
        element.appendChild(std::move(product));
    }

    isMovedOut = true;
}

void XmlRecipe::generateGroupElement(std::string_view parentId,
                                     const size_t recipeIndex,
                                     const size_t groupWidth)
{
    const auto groupHeight = s_basicElementHeight * 3;

    const auto groupY = groupHeight * recipeIndex + s_basicElementsSpacing * recipeIndex;

    MxGeometryTag geometry;

    geometry.setX(0);
    geometry.setY(static_cast<double>(groupY));
    geometry.setWidth(static_cast<double>(groupWidth));
    geometry.setHeight(groupHeight);

    auto groupElement = std::make_unique<GroupItem>(parentId, geometry);

    m_groupElement = std::move(groupElement);
}

void XmlRecipe::generateBuildingElement(std::string text, const size_t width)
{
    MxGeometryTag geometry;

    geometry.setX(0);
    geometry.setY(s_basicElementHeight);
    geometry.setWidth(static_cast<double>(width));
    geometry.setHeight(s_basicElementHeight);

    text = r_config.getBuilding(text).readableName;

    auto buildingElement = std::make_unique<RecipeItem>(m_groupElement->getId(), text,
                                                        s_basicElementStyle, geometry);

    m_buildingElement = std::move(buildingElement);
}

void XmlRecipe::generateItemElements(const Items& source,
                                     XmlElements& target,
                                     const size_t groupWidth,
                                     const double y,
                                     const ItemType itemType) const
{
    for (size_t i = 0; i < source.size(); ++i)
    {
        const auto itemWidth = groupWidth / source.size();
        const auto itemX = itemWidth * i;

        MxGeometryTag geometry;

        geometry.setX(static_cast<double>(itemX));
        geometry.setY(y);
        geometry.setWidth(static_cast<double>(itemWidth));
        geometry.setHeight(s_basicElementHeight);

        std::string name;
        std::string style;

        switch (itemType)
        {
            case ItemType::Ingredient: {
                const auto ingredient = r_config.getIngredient(source[i].name);
                name = ingredient.readableName;
                style = r_config.getStyle(ingredient.type);
                break;
            }
            case ItemType::Product: {
                const auto product = r_config.getProduct(source[i].name);
                name = product.readableName;
                style = r_config.getStyle(product.type);
                break;
            }
        }

        name = doubleToString(source[i].count) + " " + name;

        const auto itemElementPtr
            = new RecipeItem(m_groupElement->getId(), name, style, geometry);

        auto itemElement = std::unique_ptr<MxCellTag>((MxCellTag*)itemElementPtr);

        target.push_back(std::move(itemElement));
    }
}
