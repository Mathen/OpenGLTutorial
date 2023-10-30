#pragma once

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) GlClearError();\
    x;\
    ASSERT(GlLogCall())

void GlClearError();
bool GlLogCall();