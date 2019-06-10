﻿#pragma once

namespace RiceCube
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() {}
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
}