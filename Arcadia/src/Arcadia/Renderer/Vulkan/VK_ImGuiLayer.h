#pragma once

#include "Arcadia/ImGui/ImGuiLayer.h"

namespace Arcadia
{
    class CVK_ImGuiLayer : public CImGuiLayer
    {
    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
    };
}