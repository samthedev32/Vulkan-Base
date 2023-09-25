#include <vk/window.hpp>

Window::Window(const char *title, vec<2, int> size)
    : size(size), isResized(false) {
    glfwInit();

    if (!glfwVulkanSupported())
        throw std::runtime_error("vulkan is not supported");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(size->x, size->y, title, nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window() {
    // Destroy Window
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::update() {
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

void Window::createSurface(VkInstance instance, VkSurfaceKHR &surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) !=
        VK_SUCCESS)
        throw std::runtime_error("failed to create window surface");
}

void Window::framebufferResizeCallback(GLFWwindow *window, int width,
                                       int height) {
    auto self = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    self->isResized = true;
    self->size = {width, height};
}