#pragma once

#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class CKeyEvent : public CEvent
    {
    public:
        inline int GetKeyCode() const { return m_iKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        CKeyEvent(int _iKeyCode)
            : m_iKeyCode(_iKeyCode) {}

        int m_iKeyCode;
    };

    class CKeyPressedEvent : public CKeyEvent
    {
    public:
        CKeyPressedEvent(int _iKeyCode, bool _bIsRepeat)
            : CKeyEvent(_iKeyCode), m_bIsRepeat(_bIsRepeat) {}

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

    class CKeyReleasedEvent : public CKeyEvent
    {
    public:
        CKeyReleasedEvent(int _iKeyCode)
            : CKeyEvent(_iKeyCode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_iKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class CKeyTypedEvent : public CKeyEvent
    {
    public:
        CKeyTypedEvent(int _iKeyCode)
            : CKeyEvent(_iKeyCode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_iKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}