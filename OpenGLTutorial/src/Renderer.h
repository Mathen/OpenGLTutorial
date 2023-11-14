#pragma once

#include <GL/glew.h>

#include "Debug.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"

class Renderer
{
public:
    Renderer();

    void DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawTriangles(const Mesh& mesh) const;

    void DrawTrianglesOutline(const Mesh& mesh, const Shader& shader) const;

    void Clear() const;
};