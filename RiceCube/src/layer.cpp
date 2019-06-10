#include "ricepch.h"
#include "layer.h"

namespace RiceCube
{
    Layer::Layer(const std::string& name)
        : m_debugName(name)
    {
    }

    Layer::~Layer()
    {
    }
}