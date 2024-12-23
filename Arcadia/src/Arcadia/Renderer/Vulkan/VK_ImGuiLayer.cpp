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
        //io.IniFilename = nullptr;  // Avoiding the INI file
        //io.LogFilename = nullptr;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

        //float fontSize = 18.0f;// *2.0f;
        //io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
        //io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);

        // Setup ImGui style
        ////ImGui::StyleColorsDark();
        //VkDescriptorPool oDescriptorPool;
        //std::vector<VkDescriptorPoolSize> poolSize{ {VK_DESCRIPTOR_TYPE_SAMPLER, 1}, {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1} };
        //VkDescriptorPoolCreateInfo poolInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
        //poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        //poolInfo.maxSets = 1000;
        //poolInfo.poolSizeCount = 2;
        //poolInfo.pPoolSizes = poolSize.data();
        //vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &oDescriptorPool);

        //// Setup Platform/Renderer back ends
        //ImGui_ImplVulkan_InitInfo init_info = {};
        //init_info.Instance = m_instance;
        //init_info.PhysicalDevice = m_physicalDevice;
        //init_info.Device = m_device;
        //init_info.QueueFamily = m_graphicsQueueIndex;
        //init_info.Queue = m_queue;
        //init_info.PipelineCache = VK_NULL_HANDLE;
        //init_info.DescriptorPool = oDescriptorPool;
        //init_info.MinImageCount = 2;
        //init_info.ImageCount = static_cast<int>(m_swapChain.getImageCount());
        //init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;  // <--- need argument?
        //init_info.CheckVkResultFn = nullptr;
        //init_info.Allocator = nullptr;

        //init_info.UseDynamicRendering = m_useDynamicRendering;
        //init_info.PipelineRenderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
        //init_info.PipelineRenderingCreateInfo.colorAttachmentCount = 1;
        //init_info.PipelineRenderingCreateInfo.pColorAttachmentFormats = &m_colorFormat;
        //init_info.PipelineRenderingCreateInfo.depthAttachmentFormat = m_depthFormat;
        //ImGui_ImplVulkan_Init(&init_info);

        //// Upload Fonts
        //ImGui_ImplVulkan_CreateFontsTexture();
    }

    void CVK_ImGuiLayer::OnDetach()
    {
        ImGui_ImplVulkan_Shutdown();
    }
}