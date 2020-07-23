#pragma once
#include "core.h"
#include "Particle.h"

namespace ew {
	class ParticleSystem {
	public:
		void startup();
		void shutdown();

		void update(float dt);
		void draw(Core::Graphics& graphics);

		void create(const Vector2& position, 
					float angle, 
					float angleRange, 
					size_t count, 
					float lifetime, 
					const Color& color, 
					float minSpeed, 
					float maxSpeed);

	protected:
		Particle* getFreeParticle();

	protected:
		Particle* particles;
		size_t size;
	};
}

extern ew::ParticleSystem particleSystem;
