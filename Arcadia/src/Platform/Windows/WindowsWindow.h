#pragma once

#include "Arcadia/Window.h"
#include "Arcadia/Renderer/RenderContext.h"

#include "GLFW/glfw3.h"

//class RenderContext; // TODO: Check

namespace Arcadia
{
    class CWindowsWindow : public CWindow
    {
	public:
		CWindowsWindow(const SWindowProps& _oWindowProps);
		~CWindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_oWindowData.m_oWindowProps.m_uWidth; };
		inline unsigned GetHeight() const override { return m_oWindowData.m_oWindowProps.m_uWidth; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& _oCallback) override { m_oWindowData.m_oEventCallback = _oCallback; };
		void SetVSync(bool _bEnabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const SWindowProps& _oWindowProps);
		virtual void Shutdown();

		// GLFW Callbacks
		static void OnWindowResizeEvent(GLFWwindow* _pWindow, int _iWidth, int _iHeight);
		static void OnWindowCloseEvent(GLFWwindow* _pWindow);
		static void OnDropFilesEvent(GLFWwindow* _pWindow, int _iPathCount, const char* _sPaths[]);
		static void OnMouseMovedEvent(GLFWwindow* _pWindow, double _dXPos, double _dYPos);
		static void OnMouseButtonEvent(GLFWwindow* _pWindow, int _iButton, int _iAction, int _iMods);
		static void OnMouseScrolledEvent(GLFWwindow* _pWindow, double _dXOffset, double _dYOffset);
		static void OnKeyEvent(GLFWwindow* _pWindow, int _iKey, int _iScancode, int _iAction, int _iMods);

	private:
		GLFWwindow* m_pGLFWWindow;
		std::unique_ptr<CRenderContext> m_pRenderContext;

		struct SWindowData
		{
			SWindowProps m_oWindowProps;
			EventCallbackFn m_oEventCallback;
			bool m_bVsync = false;
		};
		SWindowData m_oWindowData;
    };
}