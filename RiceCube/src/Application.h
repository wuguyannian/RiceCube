#pragma once

#include "window.h"
#include "event/event_application.h"


namespace RiceCube
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

        void onEvent(Event& event);

        inline Window& getWinow() { return *m_window; }

        inline static Application& get() { return *s_instance; }

    private:
        bool onWindowClose(WindowCloseEvent& event);

        bool m_running = true;
        std::unique_ptr<Window> m_window;

	private:
        static Application* s_instance;
	};
}