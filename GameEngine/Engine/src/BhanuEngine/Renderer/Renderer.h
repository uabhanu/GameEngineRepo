#pragma once

namespace BhanuEngine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		Direct3D = 2
	};

	class Renderer
	{
		private:
		    static RendererAPI s_RendererAPI;

		public:
		    inline static RendererAPI GetAPI() { return s_RendererAPI; }
	};
}