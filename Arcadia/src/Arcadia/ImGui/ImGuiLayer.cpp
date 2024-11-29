#include "Arcadia/ImGui/ImGuiLayer.h"
#include "imgui/imgui.h"

namespace Arcadia
{
    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
    }

    void ImGuiLayer::OnEvent(Event& _event)
    {
    }
}