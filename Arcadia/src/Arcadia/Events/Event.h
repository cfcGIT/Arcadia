#pragma once

namespace Arcadia
{
    enum class EEventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        DropFiles,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EEventCategory:uint32_t
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    // #_type  -> string
#define EVENT_CLASS_TYPE(_type) static EEventType GetStaticType() { return EEventType::_type; }\
                                virtual EEventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #_type; }

#define EVENT_CLASS_CATEGORY(_category) virtual uint32_t GetCategoryFlags() const override { return _category; }

    class CEvent
    {
    private:
        friend class CEventDispatcher; // We can access to private and protected members of class Event (e.g. m_bHandled) from class EventDispatcher
    public:
        virtual ~CEvent() = default;

        virtual EEventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual uint32_t GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); } // GetName() by default

        inline bool IsInCategory(EEventCategory _eCategory)
        {
            return GetCategoryFlags() & _eCategory;
        }

        inline bool IsHandled() { return m_bHandled; }

    protected:
        bool m_bHandled = false;
    };

    class CEventDispatcher
    {
    public:
        CEventDispatcher(CEvent& _oEvent)
            : m_oEvent(_oEvent) { }

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& _oFunc)
        {
            if (m_oEvent.GetEventType() == T::GetStaticType())
            {
                m_oEvent.m_bHandled |= _oFunc(static_cast<T&>(m_oEvent));
                return true;
            }
            return false;
        }

    private:
        CEvent& m_oEvent;
    };

    inline std::string format_as(const CEvent& _oEvent)
    {
        return _oEvent.ToString();
    }

}