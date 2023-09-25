#include <vk/debug.hpp>

// Create Vulkan Debug Messenger
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
// Destroy Vulkan Debug Messenger
void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

DebugMessenger::DebugMessenger(VkInstance *instance) : instance(instance) {

    VkDebugUtilsMessengerCreateInfoEXT createInfo = getCreateInfo();

    if (CreateDebugUtilsMessengerEXT(*instance, &createInfo, nullptr,
                                     &debugMessenger) != VK_SUCCESS) {
        fprintf(stderr, "failed to set up debug messenger\n");
        return;
    }
}

DebugMessenger::~DebugMessenger() {
    DestroyDebugUtilsMessengerEXT(*instance, debugMessenger, nullptr);
}

VkDebugUtilsMessengerCreateInfoEXT DebugMessenger::getCreateInfo() {
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = this;
    return createInfo;
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData) {
    DebugMessenger *it = (DebugMessenger *)pUserData;

    fprintf(stderr, "%svalidation layer: %s\n",
            messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                ? "!!! "
                : "",
            pCallbackData->pMessage);

    return VK_FALSE;
}