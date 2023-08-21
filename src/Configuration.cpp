#include "Configuration.h"

Configuration::Configuration(const std::string_view configPath)
{
    nlohmann::ordered_json config;

    std::ifstream configFile(configPath.data());
    configFile >> config;
    configFile.close();

    *this = config.template get<Configuration>();
}

void Configuration::printToFile(const std::string_view filePath) const
{
    std::ofstream outputItemsList(filePath.data());

    const nlohmann::ordered_json config = *this;

    outputItemsList << config.dump(4);
}

std::string_view Configuration::getStyle(const std::string_view type)
{
    const auto it = m_stylesConfig.find(type.data());

    if (it != m_stylesConfig.end())
    {
        return it->second;
    }

    const auto defaultStyle = "rounded=0;whiteSpace=wrap;html=1;";

    m_stylesConfig.try_emplace(type.data(), defaultStyle);

    return defaultStyle;
}

Configuration::Building Configuration::getBuilding(const std::string_view buildingName)
{
    const auto buildingsIt = m_buildingsConfig.find(buildingName.data());

    if (buildingsIt != m_buildingsConfig.end())
    {
        return buildingsIt->second;
    }

    Building newBuildingRecord;

    newBuildingRecord.readableName = buildingName;

    m_buildingsConfig.try_emplace(buildingName.data(), newBuildingRecord);

    return newBuildingRecord;
}

Configuration::Ingredient
Configuration::getIngredient(const std::string_view ingredientName)
{
    const auto ingredientsIt = m_ingredientsConfig.find(ingredientName.data());

    if (ingredientsIt != m_ingredientsConfig.end())
    {
        return ingredientsIt->second;
    }

    const auto productsIt = m_productsConfig.find(ingredientName.data());

    if (productsIt != m_productsConfig.end())
    {
        return {{productsIt->second.readableName}, productsIt->second.type};
    }

    Ingredient newIngredientRecord;

    newIngredientRecord.readableName = ingredientName;
    newIngredientRecord.type = "undefined";

    m_ingredientsConfig.try_emplace(ingredientName.data(), newIngredientRecord);

    return newIngredientRecord;
}

Configuration::Product Configuration::getProduct(const std::string_view productName)
{
    const auto productsIt = m_productsConfig.find(productName.data());

    if (productsIt != m_productsConfig.end())
    {
        return productsIt->second;
    }

    const auto ingredientsIt = m_ingredientsConfig.find(productName.data());

    if (ingredientsIt != m_ingredientsConfig.end())
    {
        Product newProductRecord;

        newProductRecord.readableName = ingredientsIt->second.readableName;
        newProductRecord.type = ingredientsIt->second.type;
        newProductRecord.ignoreRecipes = false;

        m_productsConfig.try_emplace(productName.data(), newProductRecord);

        m_ingredientsConfig.erase(ingredientsIt);

        return newProductRecord;
    }

    Product newProductRecord;

    newProductRecord.readableName = productName;
    newProductRecord.type = "undefined";
    newProductRecord.ignoreRecipes = false;

    m_productsConfig.try_emplace(productName.data(), newProductRecord);

    return newProductRecord;
}

void from_json(const nlohmann::ordered_json& configJson, Configuration& config)
{
    for (auto& element : configJson["styles"])
    {
        config.m_stylesConfig.try_emplace(std::string(element["type"]),
                                          std::string(element["style"]));
    }

    for (auto& element : configJson["products"])
    {
        Configuration::Product product;

        product.readableName = element["readable_name"];
        product.type = element["type"];
        product.ignoreRecipes = element["ignore_recipes"];

        config.m_productsConfig.try_emplace(std::string(element["name"]), product);
    }

    for (auto& element : configJson["ingredients"])
    {
        Configuration::Ingredient ingredient;

        ingredient.readableName = element["readable_name"];
        ingredient.type = element["type"];

        config.m_ingredientsConfig.try_emplace(element["name"], ingredient);
    }

    for (auto& element : configJson["buildings"])
    {
        Configuration::Building building;

        building.readableName = element["readable_name"];

        config.m_buildingsConfig.try_emplace(element["name"], building);
    }
}

void to_json(nlohmann::ordered_json& configJson, const Configuration& config)
{
    for (const auto& [type, style] : config.m_stylesConfig)
    {
        configJson["styles"].push_back({
            {"type",  type },
            {"style", style}
        });
    }

    for (const auto& [productName, product] : config.m_productsConfig)
    {
        configJson["products"].push_back({
            {"name",           productName          },
            {"readable_name",  product.readableName },
            {"type",           product.type         },
            {"ignore_recipes", product.ignoreRecipes}
        });
    }

    for (const auto& [ingredientName, ingredient] : config.m_ingredientsConfig)
    {
        configJson["ingredients"].push_back({
            {"name",          ingredientName         },
            {"readable_name", ingredient.readableName},
            {"type",          ingredient.type        }
        });
    }

    for (const auto& [buildingName, building] : config.m_buildingsConfig)
    {
        configJson["buildings"].push_back({
            {"name",          buildingName         },
            {"readable_name", building.readableName}
        });
    }
}
