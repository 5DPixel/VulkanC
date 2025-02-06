#version 450

layout(std140, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 projection;
} ubo;

layout(std430, binding = 2) readonly buffer ModelMatrices {
    mat4 model[];
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;

void main() {
    mat4 modelMatrix = model[gl_InstanceIndex];

    gl_Position = ubo.projection * ubo.view * modelMatrix * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;

    fragNormal = normalize(mat3(modelMatrix) * inNormal);
}