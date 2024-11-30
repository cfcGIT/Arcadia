#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/Layer.h"

namespace Arcadia
{
    /**
    * LayerStack will have layers first and overlays after: Layer1,Layer2,...,LayerN,Overlay1,Overlay2,...,OverlayN
    * 
    * E.g.: ImGui will be Overlay, app and editor will be Layers. We want to capture ImGui events over other layer events.
    */
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* _layer);
        void PopLayer(Layer* _layer);
        void PushOverlay(Layer* _overlay);
        void PopOverlay(Layer* _overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_uLayerInsertIndex = 0;
    };
}