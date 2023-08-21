#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

class Configuration
{
public:
    struct Building
    {
        std::string readableName;
    };

    struct Ingredient : public Building
    {
        std::string type;
    };

    struct Product : public Ingredient
    {
        bool ignoreRecipes;
    };

    Configuration() = default;
    explicit Configuration(std::string_view configPath);

    void printToFile(std::string_view filePath) const;

    std::string_view getStyle(std::string_view type);

    Building getBuilding(std::string_view buildingName);
    Ingredient getIngredient(std::string_view ingredientName);
    Product getProduct(std::string_view productName);

private:
    std::unordered_map<std::string, Building> m_buildingsConfig;
    std::unordered_map<std::string, Ingredient> m_ingredientsConfig;
    std::unordered_map<std::string, Product> m_productsConfig;
    std::unordered_map<std::string, std::string> m_stylesConfig;

    friend void from_json(const nlohmann::ordered_json& configJson,
                          Configuration& config);
    friend void to_json(nlohmann::ordered_json& configJson, const Configuration& config);
};

void from_json(const nlohmann::ordered_json& configJson, Configuration& config);
void to_json(nlohmann::ordered_json& configJson, const Configuration& config);
