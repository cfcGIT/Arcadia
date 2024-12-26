#pragma once

namespace Arcadia
{
    class CLayer;

    /**
    * LayerStack will have layers first and overlays after: Layer1,Layer2,...,LayerN,Overlay1,Overlay2,...,OverlayN
    * 
    * E.g.: ImGui will be Overlay, app and editor will be Layers. We want to capture ImGui events over other layer events.
    */
    class CLayerStack
    {
    public:
        CLayerStack() = default;
        ~CLayerStack();

        void PushLayer(CLayer* _layer);
        void PopLayer(CLayer* _layer);
        void PushOverlay(CLayer* _overlay);
        void PopOverlay(CLayer* _overlay);

        std::vector<CLayer*>::iterator begin() { return m_tLayers.begin(); }
        std::vector<CLayer*>::iterator end() { return m_tLayers.end(); }
        std::vector<CLayer*>::reverse_iterator rbegin() { return m_tLayers.rbegin(); }
        std::vector<CLayer*>::reverse_iterator rend() { return m_tLayers.rend(); }

        std::vector<CLayer*>::const_iterator begin() const { return m_tLayers.begin(); }
        std::vector<CLayer*>::const_iterator end() const { return m_tLayers.end(); }
        std::vector<CLayer*>::const_reverse_iterator rbegin() const { return m_tLayers.rbegin(); }
        std::vector<CLayer*>::const_reverse_iterator rend() const { return m_tLayers.rend(); }

    private:
        std::vector<CLayer*> m_tLayers;
        unsigned int m_uLayerInsertIndex = 0;
    };
}