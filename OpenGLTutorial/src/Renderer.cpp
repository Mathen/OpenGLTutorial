#include "Renderer.h"

Renderer::Renderer()
{
    //Depth stuff
    GlCall(glEnable(GL_DEPTH_TEST));
    GlCall(glDepthFunc(GL_LESS));
}

void Renderer::DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GlCall(glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::DrawTriangles(const Mesh& mesh) const
{
    mesh.GetVertexArray().Bind();
    mesh.GetIndexBuffer().Bind();
    mesh.GetShader().Bind();

    GlCall(glDrawElements(GL_TRIANGLES, mesh.GetIndexBuffer().GetSize(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawTrianglesOutline(const Mesh& mesh, const Shader& shader) const
{
    mesh.GetVertexArray().Bind();
    mesh.GetIndexBuffer().Bind();

    shader.Bind();
    GlCall(glLineWidth(3.0f));

    for (unsigned int tri = 0; tri < mesh.GetIndexBuffer().GetSize(); tri++)
    {
        GlCall(glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (void*)(tri * 12)));
    }
}

void Renderer::Clear() const
{
    GlCall(glClearColor(0.3f, 0.3f, 0.3f, 0.0f));
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}