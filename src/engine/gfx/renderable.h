//
// Created by Ember Lee on 3/23/24.
//

#ifndef JOSHENGINE_RENDERABLE_H
#define JOSHENGINE_RENDERABLE_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

#ifdef GFX_API_VK
#include <vulkan/vulkan.h>
#include <array>

struct JEInterleavedVertex_VK {
    glm::vec3 position;
    glm::vec2 uvCoords;
    glm::vec3 normal;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(JEInterleavedVertex_VK);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; // vec3
        attributeDescriptions[0].offset = offsetof(JEInterleavedVertex_VK, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT; // vec2
        attributeDescriptions[1].offset = offsetof(JEInterleavedVertex_VK, uvCoords);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT; // vec3
        attributeDescriptions[2].offset = offsetof(JEInterleavedVertex_VK, normal);

        return attributeDescriptions;
    }
};
#endif

#ifdef GFX_API_MTL
struct JEInterleavedVertex_MTL {
    alignas(16) glm::vec3 position;
    alignas(8 ) glm::vec2 textureCoordinate;
    alignas(16) glm::vec3 normal;
};
#endif

class Renderable {
public:
    unsigned int shaderProgram;
    std::vector<unsigned int> descriptorIDs;

    glm::mat4 transform{};
    glm::mat4 rotate{};
    glm::mat4 scale{};
    glm::mat4 objectMatrix{};

    bool enabled;

    bool manualDepthSort{};

#ifdef GFX_API_VK
    unsigned int vboID{};
#endif

#ifdef GFX_API_MTL
    unsigned int vboID{};
#endif

    // Although on OpenGL this was negligible, for some reason on Vulkan this resulted in around +10FPS.
    unsigned int indicesSize{};

    Renderable() {
        enabled = false;
    }

    Renderable(std::vector<float> verts, std::vector<float> _uvs, std::vector<float> norms, std::vector<unsigned int> ind, unsigned int shid, std::vector<unsigned int> descs, bool manualDepthSort);

    void setMatrices(glm::mat4 t, glm::mat4 r, glm::mat4 s) {
        this->transform = t;
        this->rotate = r;
        this->scale = s;
        this->objectMatrix = (this->transform * this->rotate * this->scale);
    }

};

#endif //JOSHENGINE_RENDERABLE_H