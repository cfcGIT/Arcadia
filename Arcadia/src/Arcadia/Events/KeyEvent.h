#pragma once

#include "Event.h"

#include <sstream>

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
        KeyPressedEvent(int _iKeyCode, int _iRepeatCount)
            : KeyEvent(_iKeyCode), m_iRepeatCount(_iRepeatCount) {}

        inline int GetRepeatCount() const { return m_iRepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_iKeyCode << " (" << m_iRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_iRepeatCount;
    };

    class ARCADIA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int _iKeyCode)
            : KeyEvent(_iKeyCode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_iKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}