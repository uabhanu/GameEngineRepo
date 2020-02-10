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
		bool Normalised;
		ShaderDataType Type;
		std::string Name;
		uint32_t Offset , Size;

		BufferElements() {}

		BufferElements(ShaderDataType type , const std::string& name , bool normalised = false)
			: Name(name) , Type(type) , Size(ShaderDataTypeSize(type)) , Offset(0) , Normalised(normalised)  
		{

		}

		uint32_t GetComponentsCount() const
		{
			switch(Type)
			{
				case ShaderDataType::BOOL:      return 1;
				case ShaderDataType::FLOAT:     return 1;
				case ShaderDataType::FLOAT2:    return 2;
				case ShaderDataType::FLOAT3:    return 3;
				case ShaderDataType::FLOAT4:    return 4;
				case ShaderDataType::INT:       return 1;
				case ShaderDataType::INT2:      return 2;
				case ShaderDataType::INT3:      return 3;
				case ShaderDataType::INT4:      return 4;
				case ShaderDataType::MAT3:      return 3 * 3;
				case ShaderDataType::MAT4:      return 4 * 4;
			}

			ENGINE_CORE_ASSERT(false , "Sir Bhanu, Unknown Shader Data Type :(");
			return 0;
		}
	};

	class BufferLayout
	{
		private:
		    std::vector<BufferElements> m_Elements;
			uint32_t m_Stride = 0;

		private:
		    //Not sure why sometimes functions are implemented in .h files rather than .cpp file
			void CalculateOffsetsAndStride()
			{
				uint32_t offset = 0;
				m_Stride = 0;

				for(auto& elements : m_Elements)
				{
					elements.Offset = offset;
					offset += elements.Size;
					m_Stride += elements.Size;
				}
			}

		public:

		    BufferLayout() {}

		    BufferLayout(const std::initializer_list<BufferElements>& elements)
				: m_Elements(elements) 
			{
				CalculateOffsetsAndStride();
			}

			inline uint32_t GetStride() const { return m_Stride; }
		    inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }

			std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); } //Phew
			std::vector<BufferElements>::iterator end() { return m_Elements.end(); } //Phew
	};

	class VertexBuffer
	{
		public:
		    virtual ~VertexBuffer() {}
		    
			virtual void Bind() const = 0;
		    virtual void Unbind() const = 0;

			virtual const BufferLayout& GetLayout() const = 0;
			virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

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

