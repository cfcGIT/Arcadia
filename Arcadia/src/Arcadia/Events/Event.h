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
        KeyPreseed, KeyReleased,
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

    /*
    * If you're following along in linux or using a different compiler than the one in Visual Studio, remove the concatenation of the first line of the EVENT_CLASS_TYPE. 
      Instead of  return EventType::##type;   it's return  EventType::type;
    */

    // #_type  -> string
    // ##_type -> token-pasting
#define EVENT_CLASS_TYPE(_type) static EventType GetStaticType() { return EventType::##_type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #_type; }

#define EVENT_CLASS_CATEGORY(_category) virtual int GetCategoryFlags() const override { return _category; }

    class ARCADIA_API Event
    {
    private:
        friend class EventDispatcher; // We can access to private and protected members of class Event from class EventDispatcher
    public:
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

    // TODOCFC: Entender esto
    /*
    * For anyone struggling like me, *(T*)&m_Event casts the m_Event reference from an Event to T. 
    The order of operations is & then (T*) then *. 
    First, &m_Event gets the memory address of of m_Event (now it's type Event*).
    Second, this Event* gets casted to a T* using (T*)  (now it's type T*).
    Last, this T* gets dereferenced into a T with *(object from second step).

    */
    class ARCADIA_API EventDispatcher
    {
    private:
        template<typename T> using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& _event)
            : m_Event(_event) { }
        template<typename T> bool Dispatch(EventFn<T> _func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_bHandled = func(*(T*)&m_Event);
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