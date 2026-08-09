#include "pch.h"
#include "Particle.h"
#include "Renderer.h"
#include "Engine.h"
#include "Texture.h"

namespace nu {
	bool ParticleSystem::Initialize(size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particles
		// TODO: clear() particles
		m_particles.clear();
	}
	void ParticleSystem::Update(float dt)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			// reduce particle.lifespan by subtracting delta time
			particle.lifespan -= dt;
			particle.active = particle.lifespan > 0;
			particle.position += (particle.velocity * dt);
		}
	}
	void ParticleSystem::Draw(const Renderer& renderer)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// set particle color and draw point at current position
				// TODO: set color with particle color
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				// TODO: draw point with particle position
				//renderer.DrawPoint(particle.position.x, particle.position.y);
				res_t<Texture> particles = Resources().Get<Texture>("textures/flames.png", Engine::Get().GetRenderer());
				renderer.DrawTexture(*particles, particle.position.x, particle.position.y, 0.0f, 0.0125f);
			}
		}
	}
	void ParticleSystem::AddParticle(const Particle& particle) {
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle) {
			// set free particle object with particle
			*freeParticle = particle;
			// set particle active
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		// find and return inactive particle 
		for (auto& particle : m_particles) {
			// return pointer to inactive particle
			if (!particle.active)
				return &particle;
		}

		// no free particles, return nullptr
		return nullptr;
	}

}