#pragma once

namespace BhanuEngine
{
	enum class RendererAPI
	{
		NONE = 0,
		OPENGL = 1
	};

	class Renderer
	{
		private:
		    static RendererAPI s_RendererAPI;

		public:
		    inline static RendererAPI GetCurrentAPI() { return s_RendererAPI; }
	};
}

