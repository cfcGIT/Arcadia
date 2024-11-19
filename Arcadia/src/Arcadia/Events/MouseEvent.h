#pragma once

#include "Event.h"

#include <sstream>

namespace Arcadia
{
    class ARCADIA_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float _fX, float _fY)
            : m_fMouseX(_fX), m_fMouseY(_fY) {}

        inline float GetX() const { return m_fMouseX; }
        inline float GetY() const { return m_fMouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_fMouseX << ", " << m_fMouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_fMouseX;
        float m_fMouseY;
    };

    class ARCADIA_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float _fOffsetX, float _fOffsetY)
            : m_fOffsetX(_fOffsetX), m_fOffsetY(_fOffsetY) {}

        inline float GetOffsetX() const { return m_fOffsetX; }
        inline float GetOffsetY() const { return m_fOffsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_fOffsetX << ", " << m_fOffsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_fOffsetX;
        float m_fOffsetY;
    };

    class ARCADIA_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() { return m_iButton; }
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int _iButton)
            : m_iButton(_iButton) {}

        int m_iButton;
    };

    class ARCADIA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int _iButton)
            : MouseButtonEvent(_iButton) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_iButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class ARCADIA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int _iButton)
            : MouseButtonEvent(_iButton) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_iButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}