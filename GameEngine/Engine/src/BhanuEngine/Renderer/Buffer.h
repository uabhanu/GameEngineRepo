#pragma once

//This is a pure virtual interface meaning that the storage this takes is virtually zero, 1 byte to be precise as no data members

namespace BhanuEngine
{
	enum class ShaderDataType
	{
		BOOL , NONE = 0, FLOAT , FLOAT2 , FLOAT3 , FLOAT4 , INT , INT2 , INT3 , INT4 , MAT3 , MAT4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch(type)
		{
			case ShaderDataType::BOOL:      return 1;
			case ShaderDataType::FLOAT:     return 4;
			case ShaderDataType::FLOAT2:    return 4 * 2;
			case ShaderDataType::FLOAT3:    return 4 * 3;
			case ShaderDataType::FLOAT4:    return 4 * 4;
			case ShaderDataType::INT:       return 4;
			case ShaderDataType::INT2:      return 4 * 2;
			case ShaderDataType::INT3:      return 4 * 3;
			case ShaderDataType::INT4:      return 4 * 4;
			case ShaderDataType::MAT3:      return 4 * 3 * 3;
			case ShaderDataType::MAT4:      return 4 * 4 * 4;
		}

		ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown Shader Data Type :(");
		return 0;
	}

	struct BufferElements
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Offset , Size;

		BufferElements(ShaderDataType type , const std::string& name)
			: Name(name) , Offset(0) , Size(ShaderDataTypeSize(type)) , Type(type)
		{

		}
	};

	class BufferLayout
	{
		private:
		    std::vector<BufferElements> m_Elements;

		public:
		    BufferLayout(const std::initializer_list<BufferElements>& elements) {}
		    inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }
	};

	class VertexBuffer
	{
		public:
		    virtual ~VertexBuffer() {}
		    
			virtual void Bind() const = 0;
		    virtual void Unbind() const = 0;

			static VertexBuffer* Create(float* vertices , uint32_t size); //Visualise the general declaration of a function here and see if you understood
	};

	class IndexBuffer
	{
		public:
		    virtual ~IndexBuffer() {}

		    virtual void Bind() const = 0;
		    virtual void Unbind() const = 0;

			virtual uint32_t GetCount() const = 0;

		    static IndexBuffer* Create(uint32_t* indices , uint32_t count); //Visualise the general declaration of a function here and see if you understood
	};
}

