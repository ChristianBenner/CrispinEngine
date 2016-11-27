#include "ParticleEngine2D.h"

namespace Crispin {
	ParticleEngine2D::ParticleEngine2D()
	{
	}


	ParticleEngine2D::~ParticleEngine2D()
	{
		for (auto& b : m_batches) {
			delete b;
		}
	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* batch) {
		m_batches.push_back(batch);
	}

	void ParticleEngine2D::update(const float& deltaTime) {
		for (auto& b : m_batches) {
			b->update(deltaTime);
		}
	}

	void ParticleEngine2D::draw(SpriteBatch *spriteBatch) {
		for (auto& b : m_batches) {
			spriteBatch->begin();
			b->draw(spriteBatch);
			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}
}
