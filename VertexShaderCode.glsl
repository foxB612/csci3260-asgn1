#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int colorPerVertex;
uniform vec3 color;
out vec4 vColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	if (colorPerVertex == 1)
		vColor = vec4(vertexColor, 1.0f);
	else
		vColor = vec4(color, 1.0f);
}