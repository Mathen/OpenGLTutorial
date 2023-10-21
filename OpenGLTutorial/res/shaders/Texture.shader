#shader vertex
#version 330 core

in vec2 UV;
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
    color = texture(myTextureSampler, UV).rgb;
}

#shader fragment
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    UV = vertexUV;
}