#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_sdl3.h>

#include "IMFAssert.h"


int main()
{
    // init sdl //
    IMF_ASSERT(!(SDL_Init(SDL_INIT_VIDEO)),
        "Failed To Init SDL: " + std::string(SDL_GetError()));
    IMF_ASSERT(!(SDL_Vulkan_LoadLibrary(nullptr)),
        "Failed To Load SDL Vulkan Library: " + std::string(SDL_GetError()));


    // create the window //
    SDL_Window* mainWindow = SDL_CreateWindow(
        "imFucked", 720, 600,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
    );
    IMF_ASSERT(!mainWindow,
        "Failed To Init SDL Window: " + std::string(SDL_GetError()));


    // setting up the extensions //
    uint32_t instanceExtensionCount = 0;
    const char* const* instanceExtensions =
        SDL_Vulkan_GetInstanceExtensions(&instanceExtensionCount);
    IMF_ASSERT(!(instanceExtensions),
        "Failed To Load SDL_Vulkan Extensions" + std::string(SDL_GetError()));

    std::vector<const char*> extensions(
        instanceExtensions,
        instanceExtensions + instanceExtensionCount
    );
    extensions.insert(extensions.begin(), VK_EXT_DEBUG_REPORT_EXTENSION_NAME);


    // init vulkan //
    // creating app
    VkApplicationInfo vkAppInfo = {};
    vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkAppInfo.pApplicationName = "imFucked";
    vkAppInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    vkAppInfo.pEngineName = "No Engine";
    vkAppInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
    vkAppInfo.apiVersion = VK_API_VERSION_1_3;

    // creating instance
    VkInstanceCreateInfo vkInstanceInfo = {};
    vkInstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceInfo.pApplicationInfo = &vkAppInfo;
    vkInstanceInfo.enabledExtensionCount = extensions.size();
    vkInstanceInfo.ppEnabledExtensionNames = extensions.data();

    VkInstance vkInstance;
    VkResult instanceCreateResult =
        vkCreateInstance(&vkInstanceInfo, nullptr, &vkInstance);
    IMF_ASSERT(
        (instanceCreateResult != 0),
        "Failed To Init Vulkan" + static_cast<int>(instanceCreateResult)
    );

    // creating phy device
    uint32_t phyDeviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &phyDeviceCount, nullptr);
    IMF_ASSERT((phyDeviceCount == 0),
        "Vulkan Didn't Find Any Physical Devices");
    std::vector<VkPhysicalDevice> vkPhyDevicesFound(phyDeviceCount);
    vkEnumeratePhysicalDevices(
        vkInstance, &phyDeviceCount, vkPhyDevicesFound.data()
    );
    VkPhysicalDevice vkPhysicalDevice = vkPhyDevicesFound[0];

    // creating queue family
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
        vkPhysicalDevice, &queueFamilyCount, nullptr
    );
    std::vector<VkQueueFamilyProperties> vkQueueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(
        vkPhysicalDevice, &queueFamilyCount, vkQueueFamilies.data()
    );
    
    // querying the graphics queue family
    uint32_t graphicsQueueFamilyIndex = -1;
    int i = 0;
    for(auto& queueFamily : vkQueueFamilies)
    {
        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            graphicsQueueFamilyIndex = i;
            break;
        }
        i++;
    }
    IMF_ASSERT((graphicsQueueFamilyIndex == -1),
        "No Graphics Queue Family Found");

    // creating the logical device (VkDevice)
	extensions.clear();
    extensions.insert(extensions.begin(), VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	VkDeviceQueueCreateInfo vkDeviceQueueInfo = {};
	vkDeviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	vkDeviceQueueInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
	vkDeviceQueueInfo.queueCount = 1;
	float queuePriority = 1.0f;
	vkDeviceQueueInfo.pQueuePriorities = &queuePriority;

	VkDeviceCreateInfo vkDeviceInfo = {};
	vkDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	vkDeviceInfo.queueCreateInfoCount = 1;
	vkDeviceInfo.pQueueCreateInfos = &vkDeviceQueueInfo;
	vkDeviceInfo.enabledExtensionCount = extensions.size();
	vkDeviceInfo.ppEnabledExtensionNames = extensions.data();
    vkDeviceInfo.enabledLayerCount = 0;
	vkDeviceInfo.ppEnabledLayerNames = nullptr;

	VkDevice vkDevice;
    VkResult deviceCreateResult =
        vkCreateDevice(vkPhysicalDevice, &vkDeviceInfo, nullptr, &vkDevice);
    IMF_ASSERT(
        (deviceCreateResult != 0),
        "Failed To Create A VkDevice" + static_cast<int>(deviceCreateResult)
    );

    // getting the graphics queue
    VkQueue graphicsQueue;
    vkGetDeviceQueue(vkDevice, graphicsQueueFamilyIndex, 0, &graphicsQueue);

    // setting up the descriptor pool
    std::vector<VkDescriptorPoolSize> vkDescriptorPoolSizes = {
        {VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
        {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
        {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}
    };

    VkDescriptorPoolCreateInfo vkDescriptorPoolInfo = {};
    vkDescriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    vkDescriptorPoolInfo.flags =
        VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    vkDescriptorPoolInfo.poolSizeCount =
        static_cast<uint32_t>(vkDescriptorPoolSizes.size());
    vkDescriptorPoolInfo.pPoolSizes = vkDescriptorPoolSizes.data();
    vkDescriptorPoolInfo.maxSets = 1000;

    VkDescriptorPool imguiDescriptorPool;
    VkResult imguiDesPoolCreateResult = vkCreateDescriptorPool(
        vkDevice, &vkDescriptorPoolInfo, nullptr, &imguiDescriptorPool
    );
    IMF_ASSERT((imguiDesPoolCreateResult != 0),
        "Failed To Create A Descriptor Pool For Imgui");

    // setting up imaging
    uint32_t minImageCount = 2;

    // setting up render pass
    VkAttachmentDescription vkColorAttachInfo = {};
    // @TODO: create a swapchain and get format from there
    vkColorAttachInfo.format = VK_FORMAT_B8G8R8_SRGB;
    vkColorAttachInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    vkColorAttachInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    vkColorAttachInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    vkColorAttachInfo.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    vkColorAttachInfo.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    vkColorAttachInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    vkColorAttachInfo.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorRefInfo = {};
    colorRefInfo.attachment = 0;
    colorRefInfo.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription vkSubpassInfo = {};
    vkSubpassInfo.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkSubpassInfo.colorAttachmentCount = 1;
    vkSubpassInfo.pColorAttachments = &colorRefInfo;

    VkRenderPassCreateInfo vkRenderPassInfo = {};
    vkRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    vkRenderPassInfo.attachmentCount = 1;
    vkRenderPassInfo.pAttachments = &vkColorAttachInfo;
    vkRenderPassInfo.subpassCount = 1;
    vkRenderPassInfo.pSubpasses = &vkSubpassInfo;
    VkRenderPass vkRenderPass;
    
    VkResult renderPassCreateResult = vkCreateRenderPass(
        vkDevice, &vkRenderPassInfo, nullptr, &vkRenderPass
    );
    IMF_ASSERT(
        (renderPassCreateResult != 0),
        "Failed To Create A Render Pass" +
        static_cast<int>(renderPassCreateResult)
    );


    // setting up imgui //
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplSDL3_InitForVulkan(mainWindow);
    ImGui_ImplVulkan_InitInfo imguiVulkanInfo = {};
    imguiVulkanInfo.Instance = vkInstance;
    imguiVulkanInfo.PhysicalDevice = vkPhysicalDevice;
    imguiVulkanInfo.Device = vkDevice;
    imguiVulkanInfo.QueueFamily = 1;
	imguiVulkanInfo.Queue = graphicsQueue;
    imguiVulkanInfo.PipelineCache = nullptr;
    imguiVulkanInfo.DescriptorPool = imguiDescriptorPool;
    imguiVulkanInfo.MinImageCount = minImageCount;
    imguiVulkanInfo.ImageCount = minImageCount;
    imguiVulkanInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    imguiVulkanInfo.Allocator = nullptr;
    imguiVulkanInfo.CheckVkResultFn = nullptr;
    imguiVulkanInfo.RenderPass = vkRenderPass;

    ImGui_ImplVulkan_Init(&imguiVulkanInfo);

	// creating a command pool and buffer
    VkCommandPool vkCmdPool;
    VkCommandPoolCreateInfo vkCmdPoolInfo = {};
    vkCmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    vkCmdPoolInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
    vkCmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VkResult createCmdPoolResult = vkCreateCommandPool(
        vkDevice, &vkCmdPoolInfo, nullptr, &vkCmdPool
    );
    IMF_ASSERT(
        (createCmdPoolResult != 0),
        "Failed To Create Command Pool" +
        static_cast<int>(createCmdPoolResult)
    );

    VkCommandBuffer vkCmdBuffer;
    VkCommandBufferAllocateInfo vkCmdBufferAllocInfo = {};
    vkCmdBufferAllocInfo.sType =
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    vkCmdBufferAllocInfo.commandPool = vkCmdPool;
    vkCmdBufferAllocInfo.commandBufferCount = 1;
    vkCmdBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    VkResult allocCmdBufResult =
        vkAllocateCommandBuffers(
            vkDevice, &vkCmdBufferAllocInfo, &vkCmdBuffer
        );
    IMF_ASSERT(
        (allocCmdBufResult != 0),
        "Failed To Allocate Command Buffer" +
        static_cast<int>(allocCmdBufResult)
    );


    // gameloop //
    bool isRunning = true;
    SDL_Event event;

    while(isRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            { isRunning = false; }
        }

		// imgui stuff //
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // ImGui::Begin("Hello");
		// ImGui::Text("Hello, World!");
		// ImGui::End();

		ImGui::ShowDemoWindow();

        ImGui::Render();
    }


    // close //
    ImGui_ImplVulkan_Shutdown();
	ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    vkDestroyInstance(vkInstance, nullptr);
    vkDestroyDevice(vkDevice, nullptr);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}