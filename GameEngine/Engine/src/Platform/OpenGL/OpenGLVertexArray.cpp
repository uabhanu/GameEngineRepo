#include "EnginePCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace BhanuEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch(type)
		{
			case BhanuEngine::ShaderDataType::BOOL:       return GL_BOOL;
			case BhanuEngine::ShaderDataType::FLOAT:      return GL_FLOAT;
			case BhanuEngine::ShaderDataType::FLOAT2:	  return GL_FLOAT;
			case BhanuEngine::ShaderDataType::FLOAT3:	  return GL_FLOAT;
			case BhanuEngine::ShaderDataType::FLOAT4:	  return GL_FLOAT;
			case BhanuEngine::ShaderDataType::INT:        return GL_INT;
			case BhanuEngine::ShaderDataType::INT2:       return GL_INT;
			case BhanuEngine::ShaderDataType::INT3:		  return GL_INT;
			case BhanuEngine::ShaderDataType::INT4:		  return GL_INT;
			case BhanuEngine::ShaderDataType::MAT3:       return GL_FLOAT;
			case BhanuEngine::ShaderDataType::MAT4:		  return GL_FLOAT;
		}

		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown Shader Data Type :(");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		//glCreateVertexArrays(1 , &m_RendererID); //Just like Vertex/Index Buffers, Cherno used Create but for me Gen is working and not Create
		glGenVertexArrays(1 , &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ENGINE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() , "Sir Bhanu, Vertex Buffer has no layout :(");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		//For fun, when you are free, try using regular for loop instead
		uint32_t index = 0;
		const auto& bufferLayout = vertexBuffer->GetLayout();

		for(const auto& element : bufferLayout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index , element.GetComponentsCount() , ShaderDataTypeToOpenGLBaseType(element.Type) , element.Normalised ? GL_TRUE : GL_FALSE , bufferLayout.GetStride() , (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
