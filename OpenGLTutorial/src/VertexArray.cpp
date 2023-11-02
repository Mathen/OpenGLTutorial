#include "VertexArray.h"

VertexArray::VertexArray() : myRendererId(0), myVb(nullptr), myLayout(nullptr)
{
	GlCall(glGenVertexArrays(1, &myRendererId));
}
VertexArray::~VertexArray()
{
	delete myVb;
	delete myLayout;

	GlCall(glDeleteVertexArrays(1, &myRendererId));
}

void VertexArray::AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout)
{
	myVb = vb;
	myLayout = layout;

	Bind();
	vb->Bind();
	const auto& elements = layout->GetElements();
	unsigned char* offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(
			i,
			e.dimention,
			e.type,
			e.normalized,
			layout->GetStride(),
			offset));
		offset += e.dimention * VertexBufferElement::GetBytesOfType(e.type);
	}
}
void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{
	AddBuffer(&vb, &layout);
}

void VertexArray::Bind() const
{
	GlCall(glBindVertexArray(myRendererId));
}
void VertexArray::Unbind() const
{
	GlCall(glBindVertexArray(0));
}