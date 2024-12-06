#include "Arcadia/LayerStack.h"

namespace Arcadia
{
    CLayerStack::~CLayerStack()
    {
        for (CLayer* pLayer : m_tLayers)
        {
            delete pLayer; // TODO: The erased layers wont be deleted?
        }
    }

    /**
    * Layer1,Layer2,Layer3,*_layer*,Overlay1,Overlay2
    */
    void CLayerStack::PushLayer(CLayer* _pLayer)
    {
        m_tLayers.emplace(m_tLayers.begin() + m_uLayerInsertIndex, _pLayer);
        m_uLayerInsertIndex++;
    }

    void CLayerStack::PopLayer(CLayer* _pLayer)
    {
        auto it = std::find(m_tLayers.begin(), m_tLayers.begin() + m_uLayerInsertIndex, _pLayer);
        if (it != m_tLayers.begin() + m_uLayerInsertIndex)
        {
            m_tLayers.erase(it); // Erase from m_Layers but not deleted. It will be live until LayerStack dtor... TODO: but dtor doesnt delete erased layers?
            m_uLayerInsertIndex--;
        }
    }

    /**
    * Layer1,Layer2,Layer3,Overlay1,Overlay2,*_overlay*
    */
    void CLayerStack::PushOverlay(CLayer* _pOverlay)
    {
        m_tLayers.emplace_back(_pOverlay);
    }

    void CLayerStack::PopOverlay(CLayer* _pOverlay)
    {
        auto it = std::find(m_tLayers.begin() + m_uLayerInsertIndex, m_tLayers.end(), _pOverlay);
        if (it != m_tLayers.end())
        {
            m_tLayers.erase(it);
        }
    }


}