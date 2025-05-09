#pragma once

class GLFWwindow;

namespace Arcadia
{
	class CEvent;
	class CRenderContext;

    struct SWindowProps
    {
        std::string m_sTitle;
        unsigned int m_uWidth;
        unsigned int m_uHeight;
		
		SWindowProps(const std::string& _sTitle = "Arcadia Engine", unsigned int _uWidth = 1280, unsigned int _uHeight = 720)
            : m_sTitle(_sTitle), m_uWidth(_uWidth), m_uHeight(_uHeight) {}
    };
    
    class CWindow
	{
	public:
		typedef std::function<void(CEvent&)> EventCallbackFn;

		CWindow();
		CWindow(const SWindowProps& _oWindowProps);

		~CWindow();

		void OnUpdate();

		inline uint32_t GetWidth() const { return m_oWindowData.m_oWindowProps.m_uWidth; };
		inline uint32_t GetHeight() const { return m_oWindowData.m_oWindowProps.m_uWidth; }

		inline static GLFWwindow* GetGLFWwindow() { return m_pGLFWwindow; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& _oCallback) { m_oWindowData.m_oEventCallback = _oCallback; };
		void SetVSync(bool _bEnabled);
		inline bool IsVSync() const { return m_oWindowData.m_bVsync; }

	private:
		void Init(const SWindowProps& _oWindowProps);
		void Shutdown();


		// GLFW Callbacks
		static void OnWindowResizeEvent(GLFWwindow* _pGLFWWindow, int _iWidth, int _iHeight);
		static void OnWindowCloseEvent(GLFWwindow* _pGLFWWindow);
		static void OnDropFilesEvent(GLFWwindow* _pGLFWWindow, int _iPathCount, const char* _sPaths[]);
		static void OnMouseMovedEvent(GLFWwindow* _pGLFWWindow, double _dXPos, double _dYPos);
		static void OnMouseButtonEvent(GLFWwindow* _pGLFWWindow, int _iButton, int _iAction, int _iMods);
		static void OnMouseScrolledEvent(GLFWwindow* _pGLFWWindow, double _dXOffset, double _dYOffset);
		static void OnKeyEvent(GLFWwindow* _pGLFWWindow, int _iKey, int _iScancode, int _iAction, int _iMods);

	private:
		struct SWindowData
		{
			SWindowProps m_oWindowProps;
			EventCallbackFn m_oEventCallback;
			bool m_bVsync = false;
		};
		SWindowData m_oWindowData;

		inline static GLFWwindow* m_pGLFWwindow = nullptr;
	};
}