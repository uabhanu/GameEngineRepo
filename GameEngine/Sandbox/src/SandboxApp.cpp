#include "BhanuEngine.h"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

class BhanuTestLayer : public BhanuEngine::Layer
{
	private:
	    BhanuEngine::OrthographicCamera m_OrthographicCamera;
		float m_CameraMoveSpeed = 5.0f , m_CameraRotation , m_CameraRotationSpeed = 180.0f;
		glm::vec3 m_CameraPosition;
		std::shared_ptr<BhanuEngine::Shader> m_Shader;
		std::shared_ptr<BhanuEngine::Shader> m_SquareShader;
		std::shared_ptr<BhanuEngine::IndexBuffer> m_SquareIndexBuffer;
		std::shared_ptr<BhanuEngine::VertexArray> m_SquareVertexArray;
		std::shared_ptr<BhanuEngine::VertexArray> m_VertexArray;

	public:
		BhanuTestLayer()                    //These are Ortho values so if these are higher, images are smaller and vice versa 
			: Layer("Bhanu's Test Layer") , m_OrthographicCamera(-1.6f , 1.6f , -0.9f , 0.9f) , m_CameraPosition(0.0f) , m_CameraRotation(0.0f)
		{
			m_VertexArray.reset(BhanuEngine::VertexArray::Create());

			//No Triangle because of an exception thrown by OpenGL on Desktop but that wasn't thrown on the laptop
			//To reproduce the no triangle/exception, just put the IndexBuffer code before VertexArray
			//Triangle Colour : This is where you change the colour of the triangle
			//Square Colour : Try to do it the same way as above as at this time, it's hardcoded in squareFragmentSrc
			float vertices[3 * 7] =
			{
				-0.5f , -0.5f , 0.0f, 0.0, 0.0, 1.0, 1.0,
				 0.5f , -0.5f , 0.0f, 0.0, 1.0, 0.0, 1.0,
				 0.0f ,  0.5f , 0.0f, 1.0, 0.0, 0.0, 1.0
			};

			std::shared_ptr<BhanuEngine::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(BhanuEngine::VertexBuffer::Create(vertices , sizeof(vertices)));
			BhanuEngine::BufferLayout bufferLayout =
			{
				{BhanuEngine::ShaderDataType::FLOAT3 , "a_Position"},
				{BhanuEngine::ShaderDataType::FLOAT4 , "a_Color"}
			};

			//When I swap these lines like Cherno did, I am not getting any Assert exception but instead, only triangle not rendering
			vertexBuffer->SetLayout(bufferLayout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			//These should come after VertexArray Binding so don't change the order	
			uint32_t indices[3] = {0 , 1 , 2};
			std::shared_ptr<BhanuEngine::IndexBuffer> indexBuffer;
			indexBuffer.reset(BhanuEngine::IndexBuffer::Create(indices , sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_SquareVertexArray.reset(BhanuEngine::VertexArray::Create());

			float squareVertices[3 * 4] =
			{
				-0.5f , -0.5f , 0.0f, 
				 0.5f , -0.5f , 0.0f, 
				 0.5f ,  0.5f , 0.0f,
				-0.5f ,  0.5f , 0.0f
			};

			std::shared_ptr<BhanuEngine::VertexBuffer> squareVertexBuffer;
			squareVertexBuffer.reset(BhanuEngine::VertexBuffer::Create(squareVertices , sizeof(squareVertices)));

			BhanuEngine::BufferLayout squareBufferLayout =
			{
				{BhanuEngine::ShaderDataType::FLOAT3 , "a_Position"}
			};

			//When I swap these lines like Cherno did, I am not getting any Assert exception but instead, only triangle not rendering
			squareVertexBuffer->SetLayout(squareBufferLayout);
			m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

			uint32_t squareIndices[6] = {0 , 1 , 2 , 2 , 3 , 0};
			std::shared_ptr<BhanuEngine::IndexBuffer> squareIndexBuffer;
			squareIndexBuffer.reset(BhanuEngine::IndexBuffer::Create(squareIndices , sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

			//This way you don't have to write "\n" for every line and wonder what 'R' means :)
			//'a' in a_Position represents Attribute
			//'u' in a_Position represents Uniform
			//'v' in v_Position represents Varying
			std::string vertexSrc = 
			R"(
				#version 440 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjectionMatrix;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position , 1.0);	
				}
			)";

			//This way you don't have to write "\n" for every line and wonder what 'R' means :)
			//'a' in a_Position represents Attribute
			std::string fragmentSrc = 
			R"(
				#version 440 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5 , 1.0);
					color = v_Color;
				}
			)";

			m_Shader.reset(new BhanuEngine::Shader(vertexSrc , fragmentSrc));

			std::string squareVertexSrc =
			R"(
				#version 440 core

				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjectionMatrix;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position , 1.0);	
				}
			)";

			//This way you don't have to write "\n" for every line and wonder what 'R' means :)
			//'a' in a_Position represents Attribute
			std::string squareFragmentSrc = 
			R"(
				#version 440 core

				layout(location = 0) out vec4 color;

				in vec3 v_Position;

				void main()
				{
					color = vec4(0.0 , 1.0 , 1.0 , 1.0);
				}
			)";

			m_SquareShader.reset(new BhanuEngine::Shader(squareVertexSrc , squareFragmentSrc));
		}

		void OnEvent(BhanuEngine::Event& event) override
		{
			//BhanuEngine::EventDispatcher eventDispatcher(event);
			//eventDispatcher.Dispatch<BhanuEngine::KeyPressedEvent>(ENGINE_BIND_EVENT(BhanuTestLayer::OnKeyPressedEvent));
		}

		void OnImGUIRender() override
		{
			
		}

		void OnUpdate(BhanuEngine::TimeStep timeStep) override
		{
			if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMoveSpeed  * timeStep.GetSeconds();
			else if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_RIGHT))
				m_CameraPosition.x += m_CameraMoveSpeed * timeStep.GetSeconds();

			if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
				m_CameraPosition.y -= m_CameraMoveSpeed * timeStep.GetSeconds();
			else if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_UP))
				m_CameraPosition.y += m_CameraMoveSpeed * timeStep.GetSeconds();

			if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_A))
				m_CameraRotation += m_CameraRotationSpeed * timeStep.GetSeconds();
			else if(BhanuEngine::Input::IsKeyPressed(ENGINE_KEY_D))
				m_CameraRotation -= m_CameraRotationSpeed * timeStep.GetSeconds();

			BhanuEngine::RenderCommand::SetClearColor({0.0f , 0.2f , 0.2f , 1}); //Curly brackets is to create vec4 and I am seeing this usage for the 1st time
			BhanuEngine::RenderCommand::Clear();

			m_OrthographicCamera.SetPosition(m_CameraPosition);
			m_OrthographicCamera.SetRotation(m_CameraRotation);

			BhanuEngine::Renderer::BeginScene(m_OrthographicCamera);

			glm::mat4 scale = glm::scale(glm::mat4(1.0f) , glm::vec3(0.1f));

			for(int y = 0; y < 20; y++)
			{
				for(int x = 0; x < 20; x++)
				{
					glm::vec3 position(x * 0.11f , y * 0.11f , 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f) , position) * scale;
					BhanuEngine::Renderer::SubmitObject(m_SquareShader , m_SquareVertexArray , transform); //Renders Square First
					BhanuEngine::Renderer::SubmitObject(m_Shader , m_VertexArray); //Traingle will be rendered on top of the square
				}
			}

			BhanuEngine::Renderer::EndScene();
		}
};

class SandboxApp : public BhanuEngine::BhanuEngineApp
{
	public:
		SandboxApp()
		{

			PushLayer(new BhanuTestLayer());
		}

		~SandboxApp()
		{

		}
};

BhanuEngine::BhanuEngineApp* BhanuEngine::CreateApplication()
{
	return new SandboxApp();
}
