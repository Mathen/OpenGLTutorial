#include "Debug.h"

void GlClearError()
{
    int loop = 10;
    while (glGetError() != GL_NO_ERROR && loop--);
}

bool GlLogCall()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("OpenGL Error: 0x%04X\n", error);
        return false;
    }
    return true;
}