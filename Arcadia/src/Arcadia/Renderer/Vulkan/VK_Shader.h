#pragma once

#include "Arcadia/Renderer/Shader.h"

namespace Arcadia
{
    namespace VK
    {

        class CVK_Shader: public CShader
        {
        public:
            CVK_Shader() = default;
            CVK_Shader(const char* _sShaderPath);
            virtual ~CVK_Shader();
        };
    }
}