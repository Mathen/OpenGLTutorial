#include "Renderer.h"

void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("OpenGL Error: 0x%04X", error);
        return false;
    }
    return true;
}