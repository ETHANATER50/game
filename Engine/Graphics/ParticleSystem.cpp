#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

ew::ParticleSystem particleSystem;

namespace ew {
	void ParticleSystem::startup() {
		size = 3000;
		particles = new Particle[size];
	}

	void ParticleSystem::shutdown() {
		delete[] particles;
	}

	void ParticleSystem::update(float dt) {
		for (size_t i = 0; i < size; i++) {
			Particle* p = &particles[i];
			if (p->active) {
				p->lifetime -= dt;
				p->active = (p->lifetime > 0);

				p->prevPosition = p->position;
				p->position += p->velocity * dt;
			}
		}
	}

	void ParticleSystem::draw(Core::Graphics& graphics) {
		for (size_t i = 0; i < size; i++) {
			Particle* p = &particles[i];
			if (p->active) {
				graphics.SetColor(p->color);
				graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
			}
		}

	}

	void ParticleSystem::create(const Vector2& position, float angle, float angleRange, size_t count, float lifetime, const Color& color, float minSpeed, float maxSpeed) {

		for (size_t i = 0; i < count; i++) {
			Particle* p = getFreeParticle();
			if (p) {
				p->active = true;
				p->lifetime = lifetime;
				p->position = position;
				p->prevPosition = position;
				p->color = color;

				float angleRandom = degreesToRadians(random(-angleRange, angleRange));
				Vector2 direction = Vector2::rotate(Vector2::forward, angle + angleRandom);
				p->velocity = direction * random(minSpeed, maxSpeed);

			}
		}
	}

	Particle* ParticleSystem::getFreeParticle() {

		for (size_t i = 0; i < size; i++) {
			Particle* p = &particles[i];
			if (!p->active) {
				return p;
			}
		}

		return nullptr;
	}


}

