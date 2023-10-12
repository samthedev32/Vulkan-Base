#include <stdexcept>
#include <vk/window.hpp>
#include <vulkan/vulkan_core.h>

Window::Window(VkInstance *instance, const char *title, vec<2, int> size)
    : size(size), isResized(false), instance(instance) {
  // Init & Check Compatibility
  glfwInit();

  if (!glfwVulkanSupported())
    throw std::runtime_error("vulkan is not supported");

  // Create Window
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(size->x, size->y, title, nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

  if (!window)
    throw std::runtime_error("failed to create window");

  // Create Surface
  if (glfwCreateWindowSurface(*instance, window, nullptr, &surface) !=
      VK_SUCCESS)
    throw std::runtime_error("failed to create window surface");
}

Window::~Window() {
  // Destroy Surface
  vkDestroySurfaceKHR(*instance, surface, nullptr);

  // Destroy Window
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::update() {
  glfwPollEvents();
  return !glfwWindowShouldClose(window);
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
  auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  self->isResized = true;
  self->size = {width, height};
}