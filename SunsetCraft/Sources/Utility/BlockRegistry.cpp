//
// Created by sunvy on 17/01/2026.
//

#include "BlockRegistry.h"

#include "World/Block.h"

#include <nlohmann/json.hpp>

namespace
{
    std::unordered_map<BlockId, BlockType> m_BlockRegistry;
    std::unordered_map<std::string, BlockId> m_BlockRegistryName;

    bool bIsInitialized = false;

    void FillRegistry(const nlohmann::json& blockJson)
    {
        if (blockJson.empty())
            return;

        BlockId currentBlockId = 0;

        for (auto& block_json : blockJson)
        {
            BlockType block;
            block.id = currentBlockId++;
            block.name = block_json["name"];

            if (block_json.contains("textures"))
            {
                auto& tex = block_json["textures"];
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
            }

            m_BlockRegistry[block.id] = block;
            m_BlockRegistryName[block.name] = block.id;
        }

        bIsInitialized = true;
    }
}

BlockId BlockRegistry::AIR = 0;
BlockId BlockRegistry::GRASS = 0;
BlockId BlockRegistry::DIRT = 0;
BlockId BlockRegistry::STONE = 0;

void BlockRegistry::Init(const std::string_view &Path)
{
    const nlohmann::json blockJson = SunsetEngine::UtilityFunction::LoadJson(Path);

    FillRegistry(blockJson);

    AIR = Get("air").id;
    GRASS = Get("grass").id;
    DIRT = Get("dirt").id;
    STONE = Get("stone").id;
}

const BlockType BlockRegistry::Get(const BlockId id)
{
    if (!bIsInitialized || !m_BlockRegistry.contains(id))
        return BlockType{};

    return m_BlockRegistry[id];
}

const BlockType BlockRegistry::Get(const std::string_view &name)
{
    if (!bIsInitialized || !m_BlockRegistryName.contains(name.data()))
        return BlockType{};

    return m_BlockRegistry[m_BlockRegistryName[name.data()]];
}
