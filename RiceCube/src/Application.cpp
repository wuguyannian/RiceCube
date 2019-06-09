#include "ricepch.h"
#include "application.h"
#include "log.h"

namespace RiceCube
{
#define BIND_APP_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_instance = nullptr;

	Application::Application()
	{
        RICE_ASSERTS(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_APP_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
        while (m_running)
        {
            m_window->onUpdate();
        }
	}

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_APP_EVENT_FN(onWindowClose));
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        m_running = false;
        return true;
    }
}