#include "Mesh.h"

Mesh::Mesh(GeometryData& geoData, Shader& shader)
{
    VertexBuffer vb(geoData.GetVerticies().data(), sizeof(meshVertice) * geoData.GetVerticies().size());

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    myVertexArray.SetBuffer(vb, layout);

    myIndexBuffer = geoData.GetFaces();

    myShader = shader;
}

Mesh::~Mesh()
{

}