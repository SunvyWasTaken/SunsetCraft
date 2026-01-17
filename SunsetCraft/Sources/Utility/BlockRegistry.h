//
// Created by sunvy on 17/01/2026.
//

#ifndef SUNSETCRAFT_BLOCKREGISTRY_H
#define SUNSETCRAFT_BLOCKREGISTRY_H

enum class BlockId : uint8_t;
class BlockType;

class BlockRegistry
{
public:
    static void Init(const std::string_view& Path);

    // It can throw a unknow block if it doesn't exist in the registry
    static const BlockType Get(BlockId id);
};

#endif //SUNSETCRAFT_BLOCKREGISTRY_H