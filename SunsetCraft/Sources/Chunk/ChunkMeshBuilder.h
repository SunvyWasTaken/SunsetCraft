//
// Created by sunvy on 21/01/2026.
//

#ifndef SUNSETCRAFT_CHUNKMESHBUILDER_H
#define SUNSETCRAFT_CHUNKMESHBUILDER_H

struct CraftScene;
class Chunk;

struct ChunkMeshBuilder
{
    static void Build(Chunk& chunk, std::vector<std::uint32_t>& vertices);
};

#endif //SUNSETCRAFT_CHUNKMESHBUILDER_H