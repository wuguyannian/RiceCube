#include "ricepch.h"
#include "shader.h"

#include <glad/glad.h>

namespace RiceCube
{
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_renderID(0)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            RICE_ERROR("{0}", infoLog.data());
            RICE_ASSERTS(false, "Vertex shader compilation failure!");
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);

            glDeleteShader(vertexShader);

            RICE_ERROR("{0}", infoLog.data());
            RICE_ASSERTS(false, "fragment shader compilation failure!");
            return;
        }

        m_renderID = glCreateProgram();
        GLuint program = m_renderID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int32_t*)& isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            RICE_ERROR("{0}", infoLog.data());
            RICE_ASSERTS(false, "Shader link failure!");
            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_renderID);
    }

    void Shader::bind() const
    {
        glUseProgram(m_renderID);
    }

    void Shader::unBind() const
    {
        glUseProgram(0);
    }
}