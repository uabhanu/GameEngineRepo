#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OrthographicCamera.h"

namespace BhanuEngine
{
	class OrthographicCamera
	{
		private:
		    float m_Rotation = 0.0f;

		    glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix;
			glm::vec3 m_Position;

		private:
		    void RecalculateViewMatrix();

		public:
		    OrthographicCamera(float left , float right , float bottom , float top);

			//Cherno just mentioned that we can do these implementations in cpp file that answers your question about when you need to do as below or in cpp and you can do anyway you want
			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

			float GetRotation() const { return m_Rotation; }
			void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); } //Wonder why this is not float& like above as Cherno didn't mention probably because this is obvious

			const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	};
}

