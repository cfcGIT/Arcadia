
#include "Arcadia/LayerStack.h"

namespace Arcadia
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            delete layer; // TODO: The erased layers wont be deleted?
        }
    }

    void LayerStack::PushLayer(Layer* _layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_uLayerInsertIndex, _layer);
        m_uLayerInsertIndex++;
    }

    void LayerStack::PopLayer(Layer* _layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_uLayerInsertIndex, _layer);
        if (it != m_Layers.begin() + m_uLayerInsertIndex)
        {
            m_Layers.erase(it); // Erase from m_Layers but not deleted. It will be live until LayerStack dtor... TODO: but dtor doesnt delete erased layers?
            m_uLayerInsertIndex--;
        }
    }

    void LayerStack::PushOverlay(Layer* _overlay)
    {
        m_Layers.emplace_back(_overlay);
    }

    void LayerStack::PopOverlay(Layer* _overlay)
    {
        auto it = std::find(m_Layers.begin() + m_uLayerInsertIndex, m_Layers.end(), _overlay);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
    }


}