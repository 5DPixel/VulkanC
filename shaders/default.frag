#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

layout(std140, binding = 2) readonly buffer ModelMatrices {
    float ambient;
    mat4 modelMatrices[];
};

void main() {
    vec3 lightDir = normalize(vec3(0.0, 0.5, 1.0));
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));
    vec3 ambient = vec3(ambient);

    vec3 normal = normalize(fragNormal);

    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float shininess = 32.0;
    float specularStrength = 0.5;
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess) * specularStrength;

    vec3 texColor = texture(texSampler, fragTexCoord).rgb;

    vec3 litColor = texColor * (ambient + diffuse) + vec3(specular);
    
    outColor = vec4(litColor, 1.0);
}