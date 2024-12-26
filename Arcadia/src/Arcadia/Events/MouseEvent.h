#pragma once

#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class CMouseMovedEvent : public CEvent
    {
    public:
        CMouseMovedEvent(float _fX, float _fY)
            : m_fMouseX(_fX), m_fMouseY(_fY) {}

        inline float GetX() const { return m_fMouseX; }
        inline float GetY() const { return m_fMouseY; }

        std::string ToString() const override
        {
            // TODO: Don't use stringstream, it does 3 allocs in two lines -.-
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_fMouseX << ", " << m_fMouseY; // 1 alloc
            return ss.str(); // 2 allocs
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    private:
        float m_fMouseX;
        float m_fMouseY;
    };

    class CMouseScrolledEvent : public CEvent
    {
    public:
        CMouseScrolledEvent(float _fOffsetX, float _fOffsetY)
            : m_fOffsetX(_fOffsetX), m_fOffsetY(_fOffsetY) {}

        inline float GetOffsetX() const { return m_fOffsetX; }
        inline float GetOffsetY() const { return m_fOffsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_fOffsetX << ", " << m_fOffsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    private:
        float m_fOffsetX;
        float m_fOffsetY;
    };

    class CMouseButtonEvent : public CEvent
    {
    public:
        inline int GetMouseButton() { return m_iButton; }
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    protected:
        CMouseButtonEvent(int _iButton)
            : m_iButton(_iButton) {}

        int m_iButton;
    };

    class CMouseButtonPressedEvent : public CMouseButtonEvent
    {
    public:
        CMouseButtonPressedEvent(int _iButton)
            : CMouseButtonEvent(_iButton) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_iButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class CMouseButtonReleasedEvent : public CMouseButtonEvent
    {
    public:
        CMouseButtonReleasedEvent(int _iButton)
            : CMouseButtonEvent(_iButton) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_iButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };
}