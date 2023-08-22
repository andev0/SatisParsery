#include <iostream>
#include <set>

#include <nlohmann/json.hpp>

#include "File.h"
#include "DrawioElements/DiagramTag.h"
#include "DrawioElements/MxCellTag.h"

#include "RecipeElements/XmlRecipe.h"

#include "Configuration.h"

int main(int argc, const char* argv[])
{
    if (argc != 4)
    {
        LOG_ERROR("Usage: SatisParsery path/to/data.json path/to/configuration.json "
                  "path/to/output.drawio");
    }

    using Seconds = double;

    Configuration config(argv[2]);

    nlohmann::json recipes = nlohmann::json::parse(readFile(argv[1]))["recipes"];

    auto mxfileTag = std::make_unique<XmlElement>("mxfile");
    auto diagramTag = std::make_unique<DiagramTag>("Recipes");
    auto mxGraphModelTag = std::make_unique<XmlElement>("mxGraphModel");
    auto xmlRoot = std::make_unique<XmlElement>("root");

    mxGraphModelTag->setAttribute("page", "0");

    std::string commonParentId;

    {
        auto first = std::make_unique<MxCellTag>();
        auto second = std::make_unique<MxCellTag>(first->getId());
        commonParentId = second->getId();
        xmlRoot->appendChild(std::move(first));
        xmlRoot->appendChild(std::move(second));
    }

    size_t recipeIndex = 0;

    for (const auto& recipe : recipes)
    {
        // Filtering-out unnecessary recipes.
        if (recipe["alternate"] == false && recipe["inMachine"] == true)
        {
            Seconds constructingTime = recipe["time"];
            double outputsCountInMinute = 60 / constructingTime;

            std::vector<XmlRecipe::Item> ingredients
                = XmlRecipe::acquireItems(recipe, "ingredients", outputsCountInMinute);

            std::vector<XmlRecipe::Item> products
                = XmlRecipe::acquireItems(recipe, "products", outputsCountInMinute);

            bool ignoreRecipe = false;

            for (const auto& product : products)
            {
                if (config.getProduct(product.name).ignoreRecipes)
                {
                    ignoreRecipe = true;
                }
            }

            if (!ignoreRecipe)
            {
                XmlRecipe xmlRecipe(commonParentId, recipeIndex, ingredients,
                                    std::string(recipe["producedIn"][0]), products,
                                    config);

                xmlRecipe.appendTo(*xmlRoot);

                ++recipeIndex;
            }
        }
    }

    mxGraphModelTag->appendChild(std::move(xmlRoot));
    diagramTag->appendChild(std::move(mxGraphModelTag));
    mxfileTag->appendChild(std::move(diagramTag));

    config.printToFile(argv[2]);
    mxfileTag->printToFile(argv[3]);

    return 0;
}
