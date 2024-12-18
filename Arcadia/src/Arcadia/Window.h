#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    struct SWindowProps
    {
        std::string m_sTitle;
        unsigned int m_uWidth;
        unsigned int m_uHeight;
		
		SWindowProps(const std::string& _sTitle = "Arcadia Engine", unsigned int _uWidth = 1280, unsigned int _uHeight = 720)
            : m_sTitle(_sTitle), m_uWidth(_uWidth), m_uHeight(_uHeight) {}
    };
    
	// Interface (pure virtual)
    class CWindow
	{
	public:
		typedef std::function<void(CEvent&)> EventCallbackFn;

		virtual ~CWindow() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& _callback) = 0;
		virtual void SetVSync(bool _bEnabled) = 0;
		virtual bool IsVSync() const = 0;

		static CWindow* Create(const SWindowProps& props = SWindowProps());
	};
}