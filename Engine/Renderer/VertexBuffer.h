#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H

#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>

namespace en
{
	class VertexBuffer : public Resource
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		bool Create(std::string name, ...) override;

		void CreateVertexBuffer(GLsizei size, GLsizei m_vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

		virtual void Draw(GLenum primitiveType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(_vao); }

	protected:
		GLuint _vao = 0; 

		GLuint _vbo = 0; 
		GLuint _vertexCount = 0; 
	};
}

#endif // _VERTEX_BUFFER_H