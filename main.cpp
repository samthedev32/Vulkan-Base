#include <vk/vk.hpp>

int main() {
  srand(time(0));

  VulkanBase app(Model::load("../res/polysphere.obj"), "Vulkan Base");
  try {
    float now = time(), then = now;

    while (app.update()) {
      then = now;
      now = time();
      float deltaTime = now - then;
    }

  } catch (const std::exception &e) {
    printf("%s\n", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}