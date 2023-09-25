#pragma once

#include <vulkan/vulkan.h>

class VulkanBase;

// Vulkan Graphics Pipeline
class Pipeline {
  public:
    Pipeline();
    ~Pipeline();

  private:
    bool init(VkInstance instance);

    friend class VulkanBase;
};