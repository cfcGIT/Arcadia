#pragma once

#include "Event.h"

namespace Arcadia
{
    class ARCADIA_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(float _fWidth, float _fHeight)
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

    class ARCADIA_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ARCADIA_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ARCADIA_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ARCADIA_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ARCADIA_API DropFilesEvent : public Event
    {
    public:
        DropFilesEvent(int _iPathCount, const char* _sPaths[])
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