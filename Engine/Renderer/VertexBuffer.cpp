#include "VertexBuffer.h"

namespace en
{
	VertexBuffer::VertexBuffer()
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
	}

	VertexBuffer::~VertexBuffer()
	{
		
	}

	bool VertexBuffer::Create(std::string name, ...)
	{
		return true;
	}

	void VertexBuffer::CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data)
	{
		_vertexCount = vertexCount;

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetAttribute(int index, GLint size, GLsizei stride, size_t offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
	}

	void VertexBuffer::Draw(GLenum primitiveType)
	{
		glBindVertexArray(_vao);
		glDrawArrays(primitiveType, 0, _vertexCount);
	}
}
