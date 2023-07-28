#include <objio.hpp>
#include <vk.hpp>

int main() {
    srand(time(0));

    mesh_t m;
    mesh_load(&m, "../res/polyplanet.obj");
    VulkanBase app(Model::load(m), "Vulkan Base");
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