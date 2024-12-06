#pragma once

#include "Arcadia/Layer.h"

namespace Arcadia
{
    class CImGuiLayer : public CLayer
    {
    public:
        CImGuiLayer();
        ~CImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(CEvent& _event);
    };
}