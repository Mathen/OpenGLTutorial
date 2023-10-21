#shader vertex
#version 330 core

layout(location = 0) in  vec4 position;
layout(location = 1) in  vec3 vertexColor;
                     out vec3 fragmentColor;

uniform mat4 MVP1;
uniform mat4 MVP2;

void main()
{
    if (gl_VertexID < 8)
        gl_Position = MVP1 * position;
    else
        gl_Position = MVP2 * position;
    
    fragmentColor = vertexColor;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
                     in  vec4 fragmentColor;

void main()
{
    color = fragmentColor;
};