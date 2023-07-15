#pragma once

#include <types.hpp>

#include <GLFW/glfw3.h>

// Status:
// https://vulkan-tutorial.com/en/Texture_mapping/Images
// Part: ?

// Additional: https://developer.nvidia.com/vulkan-memory-management

float time();

class VulkanBase {
  public:
    VulkanBase(Model model, const char *title, int width = 720,
               int height = 480);

    ~VulkanBase();

    bool update();

  public:
    const char *title;
    int width, height;

  private:
    GLFWwindow *window;

    // Main Instance
    VkInstance instance;

    // Validation Layers
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};

    // Debug Messenger
    VkDebugUtilsMessengerEXT debugMessenger;

    // Physical Device
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    // Logical Device
    VkDevice device;

    // Graphics Queue
    VkQueue graphicsQueue;

    // Window Surface
    VkSurfaceKHR surface;

    // Present Queue
    VkQueue presentQueue;

    // Required Device Extensions
    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    // Swap Chain
    VkSwapchainKHR swapChain;

    // Swap Chain Images
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    // Swap Chain Image Views
    std::vector<VkImageView> swapChainImageViews;

    // Pipeline Layout
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;

    // Render Pass
    VkRenderPass renderPass;

    // Graphics Pipeline
    VkPipeline graphicsPipeline;

    // Framebuffers
    std::vector<VkFramebuffer> swapChainFramebuffers;

    // Command Pool
    VkCommandPool commandPool;

    // Command Buffer
    std::vector<VkCommandBuffer> commandBuffers;

    // Semaphores
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    bool framebufferResized = false;

    // Current Frame
    uint32_t currentFrame = 0;

    // Vertex Indices
    Model model;

    // Vertex Buffer
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    // Index Buffer
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void *> uniformBuffersMapped;

    // Descriptor Pool
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

  private:
    void initWindow(const char *title, int width, int height);

    static void framebufferResizeCallback(GLFWwindow *window, int width,
                                          int height);

    void createInstance();
    bool checkValidationLayerSupport();

    std::vector<const char *> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                  void *pUserData);

    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void setupDebugMessenger();

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void createLogicalDevice();

    void createSurface();

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void createSwapChain();

    void createImageViews();

    static std::vector<char> readFile(const char *path);

    void createGraphicsPipeline();

    VkShaderModule createShaderModule(const std::vector<char> &code);

    void createRenderPass();

    void createFramebuffers();

    void createCommandPool();

    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer commandBuffer,
                             uint32_t imageIndex);

    void createSyncObjects();

    void drawFrame();

    void cleanupSwapChain();

    void recreateSwapChain();

    void createVertexBuffer();

    uint32_t findMemoryType(uint32_t typeFilter,
                            VkMemoryPropertyFlags properties);

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                      VkMemoryPropertyFlags properties, VkBuffer &buffer,
                      VkDeviceMemory &bufferMemory);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void createIndexBuffer();

    void createDescriptorSetLayout();

    void createUniformBuffers();

    void updateUniformBuffer(uint32_t currentImage);

    void createDescriptorPool();

    void createDescriptorSets();
};