#pragma once

#include "Arcadia/Layer.h"

namespace Arcadia
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& _event);
    };
}