#include <vk.hpp>

int main() {
    srand(time(0));

    VulkanBase app(
        Model::load("../res/polyplanet.obj"),
        {{"../shader/triangle/vert.spv", "../shader/triangle/frag.spv"},
         {"../shader/ui/vert.spv", "../shader/ui/frag.spv"}},
        "Vulkan Base");
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