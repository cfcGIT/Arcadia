#pragma once

#include "Arcadia/Layer.h"

namespace Arcadia
{
    class CImGuiLayer : public CLayer
    {
    public:
        CImGuiLayer();
        ~CImGuiLayer();

        virtual void OnAttach();
        virtual void OnDetach();
        void OnUpdate();
        void OnEvent(CEvent& _event);
    };
}