#shader vertex
#version 330 core

layout(location = 0) in  vec4 position;
                     out vec4 fragmentColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * position;
    
    fragmentColor = (position + 1) / 2.0f;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
                     in  vec4 fragmentColor;

void main()
{
    color = fragmentColor;
};