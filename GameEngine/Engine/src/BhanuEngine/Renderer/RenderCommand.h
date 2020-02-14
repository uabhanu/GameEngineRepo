#pragma once

#include "RendererAPI.h"

namespace BhanuEngine
{
	class RenderCommand
	{
		private:
		    static RendererAPI* s_RendererAPI; //Not sure why this shouldn't be m_RendererAPI

		public:
			inline static void Clear()
			{
				s_RendererAPI->Clear();
			}

			inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) //Even if you don't put inline here, the compiler would anyway
			{
				s_RendererAPI->DrawIndexed(vertexArray);
			}

			inline static void SetClearColor(const glm::vec4& color)
			{
				s_RendererAPI->SetClearColor(color);
			}
	};
}