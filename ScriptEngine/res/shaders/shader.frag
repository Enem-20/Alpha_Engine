#version 460

layout(binding = 0, set = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 texel = texture(texSampler, fragTexCoord);
	if(texel.a < 0.5)
		discard;
	outColor = texel;
}