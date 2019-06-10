﻿#pragma once

#include "event/event.h"

namespace RiceCube
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event& event) {}

        inline const std::string& getName() const { return m_debugName; }

    protected:
        std::string m_debugName;
    };
}