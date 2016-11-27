/*
This is a particle batch class *depends on the Crispin
ParticleEngine2D class* developed for the Crispin Engine

Use it for any of your projects, commercial or otherwise,
free of charge, but do not remove this disclaimer.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
OF THIS SOFTWARE.

April 13 2016
Author: Christian Benner
Email: christianbenner35@gmail.com
*/

#pragma once
#include <glm\glm.hpp>
#include <functional>
#include "../Objects/Data/Vertex.h"
#include "../Rendering/SpriteBatch.h"
#include "../Loading/Resource.h"
#include "../Statements.h"

namespace Crispin {
	class Particle2D {
	public:
		glm::vec2 position = glm::vec2(0.0);
		glm::vec2 velocity = glm::vec2(0.0);
		ColorRGBA8 color;
		float lifePeriod = 0.0f;
		float size = 0.0f;
	};

	inline void defaultParticleUpdate(Particle2D& particle, float deltaTime) {
		particle.position += particle.velocity * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(const int& maximumParticleAmount,
			const float& decayRate, 
			GLTexture texture,
			std::function<void(Particle2D&, float)> func = defaultParticleUpdate);

		void update(const float& deltaTime);

		void draw(SpriteBatch* spriteBatch);

		void addParticle(const glm::vec2& position, 
			const glm::vec2& velocity,
			const ColorRGBA8& color,
			const float& size); //find particle in array and set to active
	private:
		int findFreeParticle();

		float m_decayRate = 0.01f;
		Particle2D* m_particles = nullptr; //particle array
		int m_maxParticles = 0;
		GLTexture m_texture;
		int m_lastFreeParticle = 0;
		std::function<void(Particle2D&, float)> m_updateFunc;
	};
}
