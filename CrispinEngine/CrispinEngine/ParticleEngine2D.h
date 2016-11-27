/*
This is a particle engine class developed for the Crispin
Engine

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

#include "ParticleBatch2D.h"

namespace Crispin {
	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		//when adding a particle batch, the engine is responsible
		//for its deallocation
		void addParticleBatch(ParticleBatch2D* batch);

		void update(const float& deltaTime);

		void draw(SpriteBatch *spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};
}
