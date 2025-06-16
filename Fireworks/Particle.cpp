//
//  Particle.cpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#include "Particle.hpp"

#include "Constants.h"
#include <iostream>

Particle::Particle()
: Particle(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f)
{}

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float life, float size)
: position(position), initColor(color), color(color), velocity(velocity), maxLife(life), life(life), size(size), valid(true)
{
}

void Particle::update(float dt)
{
    glm::vec3 dragForce = -PARTICLE_DRAG_COEF * glm::length(velocity) * velocity;
    glm::vec3 acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f) + dragForce / mass;
    velocity += acceleration * dt;
    position += velocity * dt;
    life -= dt;
    if (life < 0.5 * maxLife)
        fadeColor(1 - life / maxLife * 2);
    if (life < 0.0f || position.y < 0.0f)
        valid = false;
}

void Particle::render(ParticleRenderer & renderer)
{
    renderer.renderParticle(this->position, this->size, this->color);
}

void Particle::fadeColor(float ratio)
{
    this->color = initColor * (1 - ratio) + BLACK * ratio;

}
