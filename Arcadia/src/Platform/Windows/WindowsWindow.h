#pragma once

#include "Arcadia/Window.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    class ARCADIA_API WindowsWindow : public Window
    {
	public:
		WindowsWindow(const WindowProps& _windowProps);
		~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_WindowData.m_WindowProps.m_uWidth; };
		inline unsigned GetHeight() const override { return m_WindowData.m_WindowProps.m_uWidth; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& _callback) override { m_WindowData.m_EventCallback = _callback; };
		void SetVSync(bool _bEnabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& _windowProps);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			WindowProps m_WindowProps;
			EventCallbackFn m_EventCallback;
			bool m_bVsync;
		};
		WindowData m_WindowData;
    };
}