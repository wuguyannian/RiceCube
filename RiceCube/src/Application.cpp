#include "ricepch.h"
#include "application.h"
#include "log.h"

#include <glad/glad.h>

namespace RiceCube
{
#define BIND_APP_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    static GLenum getDataTypeGL(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:     return GL_FLOAT;
        case ShaderDataType::Float2:    return GL_FLOAT;
        case ShaderDataType::Float3:    return GL_FLOAT;
        case ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderDataType::Mat3:      return GL_FLOAT;
        case ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderDataType::Int:       return GL_INT;
        case ShaderDataType::Int2:      return GL_INT;
        case ShaderDataType::Int3:      return GL_INT;
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL;
        default: break;
        }
        RICE_ASSERTS(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application* Application::s_instance = nullptr;

	Application::Application()
	{
        RICE_ASSERTS(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_APP_EVENT_FN(onEvent));

        m_layerGui = new LayerImGui();
        pushOverlay(m_layerGui);

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);
        
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position"},
                { ShaderDataType::Float4, "a_Color"}
            };
            m_vertexBuffer->setLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_vertexBuffer->getLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.getComponentCount(),
                getDataTypeGL(element._type),
                element._normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)element._offset);
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

        m_shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
        while (m_running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_layerStack)
                layer->onUpdate();

            m_layerGui->begin();
            for (Layer* layer : m_layerStack)
                layer->onImGuiRender();
            m_layerGui->end();

            m_window->onUpdate();
        }
	}

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_APP_EVENT_FN(onWindowClose));

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->onEvent(event);
            if (event._handled)
                break;
        }
    }

    void Application::pushLayer(Layer* layer)
    {
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* layer)
    {
        m_layerStack.pushOverlay(layer);
        layer->onAttach();
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        m_running = false;
        return true;
    }
}