#version 460

layout(binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

void main()
{
    outColor = vec4(fragColor * texture(texSampler, fragTexCoord).xyz, 1.0);
}

