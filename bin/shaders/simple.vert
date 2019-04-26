//a simple shader
#version 410

layout( location = 0) in vec4 Position;
layout( location = 1) in vec4 Normal;
layout( location = 2) in vec2 TexCoordinates;

uniform mat4 ProjectionViewModel;

out vec2 texCoords;

void main() 
{
    texCoords = Position.xy;

	gl_Position = ProjectionViewModel * Position;
}