//
//  Firework.cpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#include "Firework.hpp"
#include "Constants.h"
#include "ResourceManager.hpp"

#include <map>
#include <random>
#include <algorithm>
#include <iostream>

Firework::Firework(glm::vec3 position, float vy, glm::vec3 color, float explodeTime, std::map<std::string, float> properties)
: position(position), vy(vy), color(color), exploded(false), restTime(explodeTime), vanished(false)
{
    initFirework(properties);
}

void Firework::update(float dt)
{
    if (!this->exploded)
    {
        // 计算空气阻力
        float dragForceY = FIREWORK_DRAG_COEF * vy * vy;
        if (vy > 0)
            dragForceY *= -1;
        
        // 发射状态
        float ay = dragForceY / mass - GRAVITY;
        this->vy += ay * dt;
        this->position.y += vy * dt;
        this->restTime -= dt;
        if (vy <= 0.0)
        {
            // 爆炸生成粒子
            this->exploded = true;
            for (unsigned int i = 0; i < particlesNum; i++)
            {
                particles.push_back(generateParticle());
            }
            // 分配质量
            float totalVol = 0.0f;
            for (auto & particle : particles)
            {
                totalVol += particle.size * particle.size * particle.size;
            }
            for (auto & particle : particles)
            {
                particle.mass = particle.size * particle.size * particle.size / totalVol * mass;
            }
        }
    }
    else
    {
        // 更新粒子
        for (unsigned int i = 0; i < particles.size(); i++)
        {
            particles[i].update(dt);
            particles.erase(
                std::remove_if(particles.begin(), particles.end(), [](const Particle& p){
                    return !p.valid;
                }),
                particles.end()
            );
        }
        if (particles.empty())
            vanished = true;
    }
}

void Firework::render(ParticleRenderer & renderer)
{
    if (!this->exploded)
    {
        renderer.renderParticle(this->position, this->size, this->color);
    }
    else
    {
        for (Particle & particle : particles)
            particle.render(renderer);
    }
}

Particle Firework::generateParticle()
{
    // 粒子位置
    glm::vec3 position = this->position;
    
    // 粒子初速度
    std::normal_distribution<float> vDistribution(0, strength);
    glm::vec3 velocity(vDistribution(ResourceManager::generator), vDistribution(ResourceManager::generator) + vy, vDistribution(ResourceManager::generator));
    
    // 粒子颜色
    std::uniform_real_distribution<float> colorChoice(0.0, 1.0);
    float choice = colorChoice(ResourceManager::generator);
    unsigned int colorIndex;
    std::string colorName;
    for (colorIndex = 0; colorIndex < colorDistributions.size(); colorIndex++)
    {
        if (colorDistributions[colorIndex].second > choice) {
            colorName = colorDistributions[colorIndex].first;
            break;
        }
    }
    glm::vec3 color = ResourceManager::colorsMap[colorName];
    
    // 粒子生命周期
    std::uniform_real_distribution<float> lifeDistribution(particleLifeMean, particleLifeSD);
    float life = lifeDistribution(ResourceManager::generator);
    life = life > MIN_PARTICLE_LIFE ? life : MIN_PARTICLE_LIFE;
    
    // 粒子尺寸
    std::uniform_real_distribution<float> sizeDistribution(particleSizeMean, particleSizeSD);
    float size = sizeDistribution(ResourceManager::generator);
    size = size > MIN_PARTICLE_SIZE ? size : MIN_PARTICLE_SIZE;
    return Particle(position, velocity, color, life, size);
}

void Firework::initFirework(std::map<std::string, float> properties)
{
    // 读取尺寸大小
    std::map<std::string, float>::iterator it = properties.find("sizeMean");
    if (it != properties.end())
    {
        this->particleSizeMean = it->second;
        properties.erase(it);
    }
    it = properties.find("sizeSD");
    if (it != properties.end())
    {
        this->particleSizeSD = it->second;
        properties.erase(it);
    }
    size = particleSizeMean - particleSizeSD;
    
    // 读取质量
    float massMean = 0.0f, massSD = 0.0f;
    it = properties.find("massMean");
    if (it != properties.end())
    {
        massMean = it->second;
        properties.erase(it);
    }
    it = properties.find("massSD");
    if (it != properties.end())
    {
        massSD = it->second;
        properties.erase(it);
    }
    std::normal_distribution<float> massDistribution(massMean, massSD);
    float mass = massDistribution(ResourceManager::generator);
    this->mass = mass > 0.1 ? strength : 0.1;
    
    // 读取爆炸强度
    float strengthMean = 0.0f, strengthSD = 0.0f;
    it = properties.find("strengthMean");
    if (it != properties.end())
    {
        strengthMean = it->second;
        properties.erase(it);
    }
    it = properties.find("strengthSD");
    if (it != properties.end())
    {
        strengthSD = it->second;
        properties.erase(it);
    }
    std::normal_distribution<float> strengthDistribution(strengthMean, strengthSD);
    float strength = strengthDistribution(ResourceManager::generator);
    this->strength = strength > 0 ? strength : 0;
    
    // 读取粒子寿命分布
    it = properties.find("lifeMean");
    if (it != properties.end())
    {
        this->particleLifeMean = it->second;
        properties.erase(it);
    }
    it = properties.find("lifeSD");
    if (it != properties.end())
    {
        this->particleLifeSD = it->second;
        properties.erase(it);
    }
    
    // 生成粒子数量
    float numMean = 0.0f, numSD = 0.0f;
    it = properties.find("numMean");
    if (it != properties.end())
    {
        numMean = it->second;
        properties.erase(it);
    }
    it = properties.find("numSD");
    if (it != properties.end())
    {
        numSD = it->second;
        properties.erase(it);
    }
    std::normal_distribution<float> numDistribution(numMean, numSD);
    this->particlesNum = static_cast<unsigned int>(numDistribution(ResourceManager::generator));
    
    // 颜色分布
    for (auto & pair : properties)
    {
        colorDistributions.push_back(pair);
    }
    // 根据分布进行排序
    std::sort(colorDistributions.begin(), colorDistributions.end(), [](const std::pair<std::string, float> & lhs, const std::pair<std::string, float> & rhs){
        return lhs.second < rhs.second;
    });
}


