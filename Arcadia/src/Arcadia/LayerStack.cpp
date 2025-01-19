#include "Arcadia/LayerStack.h"

#include "Arcadia/Layer.h"

namespace Arcadia
{
    CLayerStack::~CLayerStack()
    {
        // TODO: I don't like to delete the layers here because we're not creating them.
        for (CLayer* pLayer : m_tAllLayers)
        {
            delete pLayer;
            pLayer = nullptr;
        }
    }

    /**
    * Layer1,Layer2,Layer3,*_layer*,Overlay1,Overlay2
    */
    void CLayerStack::PushLayer(CLayer* _pLayer)
    {
        m_tLayers.emplace(m_tLayers.begin() + m_uLayerInsertIndex, _pLayer);
        m_tAllLayers.emplace_back(_pLayer);
        m_uLayerInsertIndex++;
    }

    void CLayerStack::PopLayer(CLayer* _pLayer)
    {
        auto it = std::find(m_tLayers.begin(), m_tLayers.begin() + m_uLayerInsertIndex, _pLayer);
        if (it != m_tLayers.begin() + m_uLayerInsertIndex)
        {
            m_tLayers.erase(it);
            m_uLayerInsertIndex--;
        }
    }

    /**
    * Layer1,Layer2,Layer3,Overlay1,Overlay2,*_overlay*
    */
    void CLayerStack::PushOverlay(CLayer* _pOverlay)
    {
        m_tLayers.emplace_back(_pOverlay);
        m_tAllLayers.emplace_back(_pOverlay);
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