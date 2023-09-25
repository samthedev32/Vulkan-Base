#pragma once

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vec.hpp"

#include <stdexcept>

class Window {
  public:
    vec<2, int> size;
    bool isResized;

  public:
    Window(const char *title, vec<2, int> size);
    ~Window();

    bool update();

    void createSurface(VkInstance instance, VkSurfaceKHR &surface);

  private:
    GLFWwindow *window;

  private:
    static void framebufferResizeCallback(GLFWwindow *window, int width,
                                          int height);
};