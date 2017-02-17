#pragma once

#include "Rendering\SpriteBatch.h"
#include "Rendering\Shader.h"

#include "UI.h"

#include <map>
#include <memory>
namespace Crispin {
	class ObjectRenderer
	{
	public:
		virtual void renderObjects(Crispin::SpriteBatch& spriteBatch, 
			const glm::mat4& projectionMatrix);
	
		void addObject(Crispin::UI *uiObject, 
			const std::string& name) {
			m_UI.emplace(name, uiObject);
		}

		void removeUIObject(const std::string& name) {
			m_UI.at(name) = nullptr;
		}
	protected:
		std::unique_ptr<Crispin::Shader> m_shader = nullptr;

		std::map<std::string, Crispin::UI*> m_UI;
	};
}
