#pragma once

#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_iKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int _iKeyCode)
            : m_iKeyCode(_iKeyCode) {}

        int m_iKeyCode;
    };

    class KeyPressedEvent : public KeyEvent
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

    class KeyReleasedEvent : public KeyEvent
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

    class KeyTypedEvent : public KeyEvent
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