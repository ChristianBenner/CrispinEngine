#include "ParticleBatch2D.h"

namespace Crispin {
	ParticleBatch2D::ParticleBatch2D()
	{
	}


	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_particles;
	}

	void ParticleBatch2D::init(const int& maximumParticleAmount,
		const float& decayRate, 
		GLTexture texture,
		std::function<void(Particle2D&, float)> func) {
		m_updateFunc = func;
		m_maxParticles = maximumParticleAmount;
		m_decayRate = decayRate;
		m_texture = texture;
		m_particles = new Particle2D[maximumParticleAmount];
	}

	void ParticleBatch2D::update(const float& deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_particles[i].lifePeriod > 0.0f) {
				m_updateFunc(m_particles[i], deltaTime);
				m_particles[i].lifePeriod -= m_decayRate * deltaTime;
			}
		}
	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		for (int i = 0; i < m_maxParticles; i++) {
			auto& p = m_particles[i];
			if (p.lifePeriod > 0.0f) {
				glm::vec4 dest(p.position.x, p.position.y, p.size, p.size);
				spriteBatch->draw(dest, uv, m_texture.ID, 0.0f, p.color, p.angle);
			}
		}
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		const ColorRGBA8& color,
		const float& size,
		const float& angle) {

		int particleIndex = findFreeParticle();
		auto& p = m_particles[particleIndex];
		p.lifePeriod = 1.0f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.size = size;
		p.angle = angle;
	}

	int ParticleBatch2D::findFreeParticle() {
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_particles[i].lifePeriod <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++) {
			if (m_particles[i].lifePeriod <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		Warning("Particle writeover (too many existing)");
		return 0;
	}
}