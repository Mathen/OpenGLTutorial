#shader vertex
#version 330 core

layout(location = 0) in  vec4 position;
layout(location = 1) in  vec3 normal;
layout(location = 2) in  vec2 texCoord;

                     out vec3 vnormal;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * position;

    vnormal = normal;
};

#shader fragment
#version 330 core

layout(location = 0) out vec3 color;
                     in  vec3 vnormal;

void main()
{
    vec3 lightDir = vec3(0.8f, 0.2f, 0.0f);
    float cosTheta = clamp(dot(vnormal, lightDir), 0, 1);

    vec3 ambientLight = vec3(0.2f ,0.1f ,0.1f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    color = lightColor * cosTheta + ambientLight;
};