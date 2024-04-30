#pragma once

#include <cstdio>
#include <stdexcept>
#include <vulkan/vulkan.h>

// Vulkan Debug Messenger
class DebugMessenger {
public:
  // Set Up Debug Messenger
  DebugMessenger(VkInstance *instance);

  // Destroy Debug Messenger
  ~DebugMessenger();

  // Get Create Info
  VkDebugUtilsMessengerCreateInfoEXT getCreateInfo();

  // Debug Messenger
  VkDebugUtilsMessengerEXT debugMessenger;

private:
  VkInstance *instance;

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);
};