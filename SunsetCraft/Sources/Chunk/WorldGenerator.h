//
// Created by sunvy on 22/01/2026.
//

#ifndef SUNSETCRAFT_WORLDGENERATOR_H
#define SUNSETCRAFT_WORLDGENERATOR_H

class Chunk;

struct WorldGenerator
{
  static void Init();
  static void Shutdown();

  static void Request(Chunk& chunk);
};

#endif //SUNSETCRAFT_WORLDGENERATOR_H