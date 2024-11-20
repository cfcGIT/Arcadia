#pragma once

#include "Arcadia/Core.h"

#include <string>
#include <functional>

namespace Arcadia
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPreseed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0), //     1 : 0x01 :  1
        EventCategoryInput       = BIT(1), //    10 : 0x02 :  2
        EventCategoryKeyboard    = BIT(2), //   100 : 0x04 :  4
        EventCategoryMouse       = BIT(3), //  1000 : 0x08 :  8
        EventCategoryMouseButton = BIT(4)  // 10000 : 0x10 : 16
    };

    // #_type  -> string
#define EVENT_CLASS_TYPE(_type) static EventType GetStaticType() { return EventType::_type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #_type; }

#define EVENT_CLASS_CATEGORY(_category) virtual int GetCategoryFlags() const override { return _category; }

    class ARCADIA_API Event
    {
    private:
        friend class EventDispatcher; // We can access to private and protected members of class Event from class EventDispatcher
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); } // GetName() by default

        inline bool IsInCategory(EventCategory _category)
        {
            return GetCategoryFlags() & _category;
        }
    protected:
        bool m_bHandled = false;
    };

    class ARCADIA_API EventDispatcher
    {
    public:
        EventDispatcher(Event& _event)
            : m_Event(_event) { }

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& _func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_bHandled |= _func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    inline std::string format_as(const Event& e)
    {
        return e.ToString();
    }

}