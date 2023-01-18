#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	unsigned int dataType;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void BufferData(const unsigned int* data, unsigned int count);

	inline unsigned int GetCount() const { return m_Count; }
	inline unsigned int GetDataType() const { return dataType; }
};