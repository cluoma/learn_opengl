#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor; // specify a color output to the fragment shader
uniform float xOffset;
void main()
{
   gl_Position = vec4(aPos.x + xOffset, (-1)*aPos.y, aPos.z, 1.0);
   //vertexColor = aColor;
   vertexColor = aPos;
}