#include "Source/API/OpenGL/OpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenGLRenderer {
	void Render() {
		OpenGL::Clear();
		OpenGL::bindTexture(container_texture);
		// Transformations
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = Camera::GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(70.0f), (float)g_windowWidth / g_windowHeight, 0.1f, 100.f);
		// --------------
		OpenGL::useShaderProgram(&container_shaderProgram);
		// Setting Transforms Uniform in shader
		OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
		OpenGL::setMat4(container_shaderProgram, "view", glm::value_ptr(view));
		OpenGL::setMat4(container_shaderProgram, "projection", glm::value_ptr(projection));
		// -----------------------------------
		OpenGL::bindVertexArray(container_vao);

		OpenGL::Draw();		//Renders First cube

		//Renders Second Cube
		model = glm::translate(model, glm::vec3(-3, 0, 2.5));
		OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
		OpenGL::Draw();

		//Renders Third Cube
		model = glm::translate(model, glm::vec3(-3, 0, -3));
		OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
		OpenGL::Draw();
	}
}