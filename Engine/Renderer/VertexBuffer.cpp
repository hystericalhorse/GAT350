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

	void VertexBuffer::CreateIndexBuffer(GLenum indexType, GLsizei count, void* data)
	{
		_indexType = indexType;
		_indexCount = count;

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		size_t indexSize = (_indexType == GL_UNSIGNED_SHORT) ? sizeof(GLushort) : sizeof(GLuint);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * indexSize, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::Draw(GLenum primitiveType)
	{
		glBindVertexArray(_vao);

		if (_ibo)
		{
			glDrawElements(primitiveType, _indexCount, _indexType, 0);
		}
		else if (_vbo)
		{
			glDrawArrays(primitiveType, 0, _vertexCount);
		}
	}
}
