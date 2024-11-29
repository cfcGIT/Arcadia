#pragma once

#include "Arcadia/Window.h"
#include "Arcadia/Renderer/RenderContext.h"

#include "GLFW/glfw3.h"

//class RenderContext; // TODO: Check

namespace Arcadia
{
    class WindowsWindow : public Window
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

		// GLFW Callbacks
		static void OnWindowResizeEvent(GLFWwindow* _window, int _iWidth, int _iHeight);
		static void OnWindowCloseEvent(GLFWwindow* _window);
		static void OnDropFilesEvent(GLFWwindow* _window, int _iPathCount, const char* _sPaths[]);
		static void OnMouseMovedEvent(GLFWwindow* _window, double _dXPos, double _dYPos);
		static void OnMouseButtonEvent(GLFWwindow* _window, int _iButton, int _iAction, int _iMods);
		static void OnMouseScrolledEvent(GLFWwindow* _window, double _dXOffset, double _dYOffset);
		static void OnKeyEvent(GLFWwindow* _window, int _iKey, int _iScancode, int _iAction, int _iMods);

	private:
		GLFWwindow* m_GLFWWindow;
		std::unique_ptr<RenderContext> m_puRenderContext;

		struct WindowData
		{
			WindowProps m_WindowProps;
			EventCallbackFn m_EventCallback;
			bool m_bVsync;
		};
		WindowData m_WindowData;
    };
}