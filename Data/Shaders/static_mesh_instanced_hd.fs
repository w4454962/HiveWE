#version 450 core

layout (binding = 0) uniform sampler2D diffuse;
layout (binding = 1) uniform sampler2D normal;
layout (binding = 2) uniform sampler2D orm;
layout (binding = 3) uniform sampler2D environemt;
layout (binding = 4) uniform sampler2D emissive;

layout (location = 1) uniform float alpha_test;
layout (location = 2) uniform bool show_lighting;

in vec2 UV;
in vec3 TangentLightDirection;
in vec3 vertexColor;

out vec4 color;

void main() {
	color = texture(diffuse, UV) * vec4(vertexColor, 1.f);
	
	// normal is a 2 channel normal map so we have to deduce the 3rd value
	vec2 texel = texture(normal, UV).rg;

	if (show_lighting) {
		vec3 normal = vec3(texel, 1.f - sqrt(texel.x * texel.x + texel.y * texel.y));
		normal = normalize(normal * 2.f - 1.f);

		float contribution = (dot(normal, TangentLightDirection) + 1.f) * 0.5f;
		color.rgb *= clamp(contribution, 0.f, 1.f);
	}

	if (color.a < alpha_test) {
		discard;
	}
}