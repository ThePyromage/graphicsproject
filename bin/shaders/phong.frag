#version 410

struct Light 
{
    vec4 position;
	vec3 color;
	float radius;
};

uniform int lightCount;
uniform Light lights[8];

in vec4 fragPosition;
in vec4 fragNormal;
in vec2 fragTexCoords;

out vec4 fragColor;

void main() 
{
    vec3 lighting = vec3(0.1f);
	
	for(int i = 0; i < lightCount; ++i) 
	{
	    vec3 lightDir = normalize(lights[i].position.xyz - fragPosition.xyz);
		vec3 normal = fragNormal.xyz;
		
		float lambert = max(0.0f, dot(normal, -lightDir));
		
		lighting += lambert * lights[i].color;
	}
	
	fragColor = vec4(lighting, 1.0f);
}