#pragma once

#include "layer.h"

namespace RiceCube
{
    class LayerImGui : public Layer
    {
    public:
        LayerImGui();
        ~LayerImGui();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onImGuiRender() override;

        void begin();
        void end();

    private:
        float m_time = 0.f;
    };
}

