#pragma once

#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class CWindowResizeEvent : public CEvent
    {
    public:
        CWindowResizeEvent(float _fWidth, float _fHeight)
            : m_fWidth(_fWidth), m_fHeight(_fHeight) {}

        inline float GetWidth() const { return m_fWidth; }
        inline float GetHeight() const { return m_fHeight; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_fWidth << ", " << m_fHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        float m_fWidth;
        float m_fHeight;
    };

    class CWindowCloseEvent : public CEvent
    {
    public:
        CWindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CAppTickEvent : public CEvent
    {
    public:
        CAppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CAppUpdateEvent : public CEvent
    {
    public:
        CAppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CAppRenderEvent : public CEvent
    {
    public:
        CAppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CDropFilesEvent : public CEvent
    {
    public:
        CDropFilesEvent(int _iPathCount, const char* _sPaths[])
            : m_iPathCount(_iPathCount), m_sPaths(_sPaths) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            std::stringstream ss2;
            for (int i = 0; i < m_iPathCount; ++i)
            {
                ss2 << m_sPaths[i] << ",";
            }
            ss << "DropFilesEvent: " << m_iPathCount << ": " << ss2.str();
            return ss.str();
        }

        EVENT_CLASS_TYPE(DropFiles)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        int m_iPathCount;
        const char** m_sPaths;
    };
}