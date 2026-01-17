//
// Created by sunvy on 17/01/2026.
//

#ifndef SUNSETCRAFT_BLOCKREGISTRY_H
#define SUNSETCRAFT_BLOCKREGISTRY_H

using BlockId = uint8_t;
class BlockType;

class BlockRegistry
{
public:
    static void Init(const std::string_view& Path);

    // It can throw a unknow block if it doesn't exist in the registry
    static const BlockType Get(const BlockId id);

    static const BlockType Get(const std::string_view& name);

    static BlockId AIR;
    static BlockId GRASS;
    static BlockId DIRT;
    static BlockId STONE;
};

#endif //SUNSETCRAFT_BLOCKREGISTRY_H