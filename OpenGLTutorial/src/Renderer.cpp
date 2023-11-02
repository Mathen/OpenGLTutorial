#include "Renderer.h"

Renderer::Renderer()
{
    //Depth stuff
    GlCall(glEnable(GL_DEPTH_TEST));
    GlCall(glDepthFunc(GL_LESS));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GlCall(glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Draw(const Mesh& mesh) const
{
    mesh.GetVertexArray().Bind();
    mesh.GetIndexBuffer().Bind();
    mesh.GetShader().Bind();

    GlCall(glDrawElements(GL_TRIANGLES, mesh.GetIndexBuffer().GetSize(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GlCall(glClearColor(0.0f, 0.0f, 0.4f, 0.0f));
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}