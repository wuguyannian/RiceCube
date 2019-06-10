#pragma once

namespace RiceCube
{
    enum RenderAPI
    {
        None = 0,
        OpenGL
    };

    class Renderer
    {
    public:
        inline static RenderAPI getAPI() { return s_renderAPI; }

    private:
        static RenderAPI s_renderAPI;
    };
}