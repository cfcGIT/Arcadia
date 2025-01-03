#pragma once

namespace Arcadia
{
    class CRendererAPI
    {
    public:
        enum class EAPI
        {
            None = -1,
            Vulkan,
            OpenGL,
            DX12
        };

    public:
        virtual ~CRendererAPI() = default;

        virtual void Init() = 0;
        virtual void InitRenderContext() = 0;
        virtual void Shutdown() = 0;

        static EAPI GetAPI() { return m_oAPI; }
        static std::unique_ptr<CRendererAPI> Create();

    private:
        inline static EAPI m_oAPI = EAPI::Vulkan; // TODO: CVar
    };
}