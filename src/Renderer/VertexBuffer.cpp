#include "VertexBuffer.h"
#include "GLCall.h"

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));//This generated a buffer of memory
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//Will set the targets current buffer to be this
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//Fills the current bound buffer with data
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::GenBuffer(const void * data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
