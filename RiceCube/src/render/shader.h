#pragma once

#include <string.h>

namespace RiceCube
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unBind() const;

    private:
        uint32_t m_renderID = 0;
    };
}