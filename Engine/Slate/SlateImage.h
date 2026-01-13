//
// Created by sunvy on 13/01/2026.
//

#ifndef SUNSETCRAFT_SLATEIMAGE_H
#define SUNSETCRAFT_SLATEIMAGE_H

#include "Slate.h"

namespace SunsetEngine
{
    class SlateImage : public Slate
    {
        SlateImage();
        virtual ~SlateImage();
        void LoadImage(const std::string_view& path);
        void Draw() const override;
    private:
        uint32_t VAO;
        uint32_t VBO;
        uint32_t m_Id;
    };
}

#endif //SUNSETCRAFT_SLATEIMAGE_H