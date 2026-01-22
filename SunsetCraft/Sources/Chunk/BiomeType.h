//
// Created by sunvy on 22/01/2026.
//

#ifndef SUNSETCRAFT_BIOMETYPE_H
#define SUNSETCRAFT_BIOMETYPE_H

#include <variant>

#define VSTRUCT(name, Amplitude) struct name { name(){}; float amp = Amplitude; };

struct BiomeData
{
    float humidity;
    float heat;
};

struct BiomeType
{
    VSTRUCT(Plain, 3)
    VSTRUCT(Desert, 4)
    VSTRUCT(Forest, 5)
    VSTRUCT(Mountain, 20)
    VSTRUCT(Ocean, 6)

    using Type = std::variant<std::monostate, Plain, Desert, Forest, Mountain, Ocean>;
};

#endif //SUNSETCRAFT_BIOMETYPE_H