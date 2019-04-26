// a simple flat colour shader
#version 410

uniform sampler2D textureMaps[16];

in vec2 texCoords;

out vec4 FragColour;

void main()
{
	FragColour = texture(textureMaps[0], texCoords);
}