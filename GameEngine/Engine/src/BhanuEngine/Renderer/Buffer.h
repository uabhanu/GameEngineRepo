#pragma once

//This is a pure virtual interface meaning that the storage this takes is virtually zero, 1 byte to be precise as no data members

namespace BhanuEngine
{
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

