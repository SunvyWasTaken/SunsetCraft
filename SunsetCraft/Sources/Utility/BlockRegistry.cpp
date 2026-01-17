//
// Created by sunvy on 17/01/2026.
//

#include "BlockRegistry.h"

#include "World/Block.h"

#include <nlohmann/json.hpp>

#include <fstream>

namespace
{
    std::unordered_map<BlockId, BlockType> _BlockRegistry;

    bool bIsInitialized = false;

    nlohmann::json LoadJsonFile(const std::string_view& Path)
    {
        std::ifstream file;
        file.open(Path.data());

        nlohmann::json json;

        if (!file.is_open())
        {
            LOG("Json file couldn't be open")
            return json;
        }

        file >> json;
        return json;
    }
}

void BlockRegistry::Init(const std::string_view &Path)
{
    nlohmann::json blockJson = LoadJsonFile(Path);

    if (blockJson.empty())
        return;

    for (auto& block_json : blockJson)
    {
        BlockType block;
        block.id = block_json["id"];
        block.name = block_json["name"];

        auto& tex = block_json["texture"];
        if (tex.contains("all"))
        {
            std::string all = tex.value("all", "");
            for (auto& t : block.textures)
                t = all;
        }
        if (tex.contains("top"))
            block.textures[static_cast<int>(BlockFace::Top)] = tex["top"];

        if (tex.contains("bottom"))
            block.textures[static_cast<int>(BlockFace::Bottom)] = tex["bottom"];

        if (tex.contains("north"))
            block.textures[static_cast<int>(BlockFace::North)] = tex["north"];

        if (tex.contains("south"))
            block.textures[static_cast<int>(BlockFace::South)] = tex["south"];

        if (tex.contains("west"))
            block.textures[static_cast<int>(BlockFace::West)] = tex["west"];

        if (tex.contains("east"))
            block.textures[static_cast<int>(BlockFace::East)] = tex["east"];

        _BlockRegistry[block.id] = block;
    }

    bIsInitialized = true;
}

const BlockType BlockRegistry::Get(BlockId id)
{
    if (!bIsInitialized)
    {
        HUD("Block Registry isn't initialized")
        return BlockType{};
    }

    if (!_BlockRegistry.contains(id))
        return BlockType{};

    return _BlockRegistry[id];
}
