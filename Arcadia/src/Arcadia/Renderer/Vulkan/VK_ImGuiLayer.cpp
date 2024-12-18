#include "Arcadia/Renderer/Vulkan/VK_ImGuiLayer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_vulkan.h"

#include "arcpch.h"

namespace Arcadia
{
    void CVK_ImGuiLayer::OnAttach()
    {
        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        
        // TODO:
        // ...
        //ImGui_ImplVulkan_Init(&init_info);

        // Upload Fonts
        //ImGui_ImplVulkan_CreateFontsTexture();
    }

    void CVK_ImGuiLayer::OnDetach()
    {
        ImGui_ImplVulkan_Shutdown();
    }
}