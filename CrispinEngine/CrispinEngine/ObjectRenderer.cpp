#include "ObjectRenderer.h"

namespace Crispin {
	void ObjectRenderer::renderObjects(Crispin::SpriteBatch& spriteBatch,
		const glm::mat4& projectionMatrix) {
		spriteBatch.begin();

		if (m_shader == nullptr) {
			m_shader = std::make_unique<Crispin::Shader>();
			m_shader->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
			m_shader->addAttribute("vertexPosition");
			m_shader->addAttribute("vertexColor");
			m_shader->addAttribute("vertexUV");
			m_shader->linkShaders();
		}

		m_shader->use();

		GLint textureUniform = m_shader->getUniformLocation("texSampler");
		glUniform1i(textureUniform, 0);

		GLint projectionMatrixUniform = m_shader->getUniformLocation("projectionMatrix");
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		// Render object here
		for (std::pair<std::string, Crispin::UI*> obj : m_UI) {
		//	printf("Drawing %s\n", obj.first.c_str());
			obj.second->draw();
		//	printf("x[%d], y[%d]\n", obj.second->getPosition().x, obj.second->getPosition().y);
		}

		m_shader->unuse();

		spriteBatch.end();
		spriteBatch.renderBatch();
	}
}