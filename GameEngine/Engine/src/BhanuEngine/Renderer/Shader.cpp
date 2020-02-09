#include "EnginePCH.h"
#include "Shader.h"

#include <glad/glad.h>

namespace BhanuEngine
{
	Shader::Shader(const std::string& vertexSrc , const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		//const GLchar *source = (const GLchar *)vertexSrc.c_str(); //Cherno said no need to cast this so now this line becomes as below
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			ENGINE_CORE_ERROR("{0}" , infoLog.data());
			ENGINE_CORE_ASSERT(false , "Sir Bhanu, Vertex Shader Compilation Failed!!! :(");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		//source = (const GLchar *)fragmentSrc.c_str(); //As Cherno showed, no need for casting so the code below also works just fine
		source = fragmentSrc.c_str(); //As Cherno showed, no need for casting so the code below also works just fine
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the shader anymore.
			// Either of them. Don't leak shaders.
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			ENGINE_CORE_ERROR("{0}" , infoLog.data());
			ENGINE_CORE_ASSERT(false , "Sir Bhanu, Fragment Shader Compilation Failed!!! :(");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		//Cherno said it's not needed to replace program with m_RendererID so did m_Renderer = glCreateProgram but this is
		//the only way, Cherno said this is to avoid replacing program with m_RendererID in every line in a lazy sense 
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	
			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ENGINE_CORE_ERROR("{0}" , infoLog.data());
			ENGINE_CORE_ASSERT(false , "Sir Bhanu, Shader Link Failed!!! :(");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}