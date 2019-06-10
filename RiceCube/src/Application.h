#pragma once

#include "window.h"

#include "layer_stack.h"
#include "layer/layer_imgui.h"

#include "event/event_application.h"

#include "render/shader.h"
#include "render/buffer.h"


namespace RiceCube
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline Window& getWindow() { return *m_window; }

        inline static Application& get() { return *s_instance; }

    private:
        bool onWindowClose(WindowCloseEvent& event);

        bool m_running = true;
        std::unique_ptr<Window> m_window;
        LayerStack m_layerStack;
        LayerImGui* m_layerGui;

        uint32_t m_vertexArray = 0;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;
        std::unique_ptr<IndexBuffer> m_indexBuffer;

	private:
        static Application* s_instance;
	};
}