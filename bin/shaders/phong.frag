#version 410

uniform sampler2D textureMaps[16];

uniform int lightCount;
uniform vec4 lightPositions[8];
uniform vec3 lightColours[8];
uniform float lightRadiuses[8];

in vec4 fragPosition;
in vec4 fragNormal;
in vec2 fragTexCoords;

out vec4 fragColor;

void main()
{
    vec3 diffuse = texture(textureMaps[0], fragTexCoords).rgb;
	vec3 lighting = diffuse * 0.1f;
	
	for(int i = 0; i < lightCount; ++i)
	{
		vec3 lightDir = normalize(lightPositions[i].xyz - fragPosition.xyz);
		vec3 normal = fragNormal.xyz;
		
		float lambert = max(0.0f, dot(normal, -lightDir));
		
		lighting += lambert * diffuse * lightColours[i];
	}
	
	fragColor = vec4(lighting, 1.0f);
}