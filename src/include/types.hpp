#pragma once

#include <stdexcept>
#include <vulkan/vulkan.h>

#include <mathutil/matrix.hpp>

#include <array>
#include <cstring>
#include <exception>
#include <fstream>
#include <optional>

#include <string>
#include <vector>

struct Vertex {
    vec3 position;
    vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2>
    getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2>
            attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject {
    mat4 model, view, projection;
};

struct Model {
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;

    static Model load(std::string path) {
        std::ifstream file(path);

        if (!file.is_open())
            throw std::runtime_error("Failed to open Model File");

        Model model;

        std::vector<vec3> vertices;
        std::vector<vec3> colors;

        // Load Model
        std::string line;
        while (getline(file, line)) {
            char index[8];
            char data[129];
            int c = sscanf(line.c_str(), "%7s %[^\n]s", index, data);

            if (c == 2) {
                if (!strcmp(index, "v")) {
                    vec3 vertex;
                    sscanf(data, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                    vertices.push_back(vertex);
                } else if (!strcmp(index, "f")) {
                    int v[4];
                    char part[4][128];
                    int parts = sscanf(data, "%s %s %s %s", part[0], part[1],
                                       part[2], part[3]);

                    for (int i = 0; i < parts; i++) {
                        if (sscanf(part[i], "%i/%*i/%*i", &v[i]) != 3)
                            if (sscanf(part[i], "%i//%*i", &v[i]) != 2)
                                if (sscanf(part[i], "%i/%*i", &v[i]) != 2)
                                    if (sscanf(part[i], "%i", &v[i]) != 1) {
                                        printf("Failed to read Face Line\n");
                                        parts = 0;
                                    }
                    }

                    if (parts != 3)
                        printf("Face is not a Tri (%i)\n", parts);
                    else {
                        // TODO: duplicate face optimization
                        for (int i = 0; i < 3; i++) {
                            Vertex vertex;
                            vertex.position = vertices[v[i]];
                            vertex.color = {(float)(rand() % 1000) / 1000,
                                            (float)(rand() % 1000) / 1000,
                                            (float)(rand() % 1000) / 1000};

                            model.vertices.push_back(vertex);
                            model.indices.push_back(model.vertices.size() - 1);
                        }
                    }
                }
            }
        }

        if (model.indices.size() < 3)
            throw std::runtime_error("No Triangles were loaded");

        // model.vertices = {{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        //                   {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        //                   {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        //                   {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}};

        // model.indices = {0, 1, 2, 2, 3, 0};

        return model;
    }
};