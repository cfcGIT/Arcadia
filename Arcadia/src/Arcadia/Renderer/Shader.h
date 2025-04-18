#pragma once

namespace Arcadia
{
    class CShader
    {
    public:
        virtual ~CShader() = default;
        static CShader* Create(const char* _sShaderPath);

    private:

    };
}