#pragma once

#include "Event.h"

namespace Arcadia
{
    class ARCADIA_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_iKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int _iKeyCode)
            : m_iKeyCode(_iKeyCode) {}

        int m_iKeyCode;
    };

    class ARCADIA_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int _iKeyCode, bool _bIsRepeat)
            : KeyEvent(_iKeyCode), m_bIsRepeat(_bIsRepeat) {}

        inline bool IsRepeat() const { return m_bIsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_iKeyCode << " (repeat = " << m_bIsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_bIsRepeat;
    };

    class ARCADIA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int _iKeyCode)
            : KeyEvent(_iKeyCode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_iKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class ARCADIA_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int _iKeyCode)
            : KeyEvent(_iKeyCode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_iKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}