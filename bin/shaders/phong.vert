#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec4 tangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragPosition;
out vec4 fragNormal;
out vec2 fragTexCoords;

void main() 
{
    fragPosition = model * position;

    fragNormal = normal;
	fragTexCoords = texCoords;

    gl_Position = projection * view * fragPosition;
}