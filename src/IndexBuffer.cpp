#include "IndexBuffer.h"
#include "GLCall.h"

IndexBuffer::IndexBuffer()
	:m_Count(0)
{
	GLCall(glGenBuffers(1, &m_RendererID));
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	dataType = GL_UNSIGNED_INT;
	GLCall(glGenBuffers(1, &m_RendererID));//This generated a buffer of memory
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));//Will set the targets current buffer to be this
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));//Fills the current bound buffer with data
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::BufferData(const unsigned int* data, unsigned int count)
{
	m_Count = count;
	dataType = GL_UNSIGNED_INT;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}