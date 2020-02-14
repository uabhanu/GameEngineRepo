#include "EnginePCH.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "RenderCommand.h"

namespace BhanuEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}