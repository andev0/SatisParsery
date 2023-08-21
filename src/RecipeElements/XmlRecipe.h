#pragma once

#include "DrawioElements/MxCellTag.h"

#include "Configuration.h"

class XmlRecipe
{
public:
    struct Item
    {
        std::string name;
        double count;
    };

    using Items = std::vector<Item>;

    XmlRecipe(std::string_view parentId,
              size_t recipeIndex,
              const Items& ingredients,
              std::string_view buildingName,
              const Items& products,
              Configuration& config);

    static std::vector<XmlRecipe::Item> acquireItems(const nlohmann::json& recipe,
                                                     std::string_view listName,
                                                     const double outputsCountInMinute);

    // Leaves XmlRecipe empty
    void appendTo(XmlElement& element);

private:
    using XmlElements = std::vector<std::unique_ptr<MxCellTag>>;

    enum class ItemType
    {
        Ingredient,
        Product
    };

    void
    generateGroupElement(std::string_view parentId, size_t recipeIndex, size_t width);
    void generateBuildingElement(std::string text, size_t width);
    void generateItemElements(const Items& source,
                              XmlElements& target,
                              size_t groupWidth,
                              double y,
                              ItemType itemType) const;

    Configuration& r_config;

    std::unique_ptr<MxCellTag> m_groupElement;
    XmlElements m_ingredientsElements;
    std::unique_ptr<MxCellTag> m_buildingElement;
    XmlElements m_productsElements;

    bool isMovedOut {false};

    static constexpr uint8_t s_basicElementWidth = 140;
    static constexpr uint8_t s_basicElementHeight = 40;
    static constexpr uint8_t s_basicElementsSpacing = 20;
    static inline const std::string_view s_basicElementStyle
        = "rounded=0;whiteSpace=wrap;html=1;";
};
