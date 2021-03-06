#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace BhanuEngine
{
	class Shader
	{
		private:
		    uint32_t m_RendererID;

		public:
		    Shader(const std::string& vertexSrc , const std::string& fragmentSrc);
			~Shader();

			void Bind() const;
			void Unbind() const;

			void UploadUniformMat4(const std::string& name , const glm::mat4& matrix);
	};
}
