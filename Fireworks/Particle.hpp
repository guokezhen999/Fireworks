//
//  Particle.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <glm/glm.hpp>

#include "ParticleRenderer.hpp"

class Particle
{
public:
    // 位置
    glm::vec3 position;
    // 速度
    glm::vec3 velocity;
    // 颜色
    glm::vec3 initColor;
    glm::vec3 color;
    // 最大生命
    float maxLife;
    // 剩余生命
    float life;
    // 尺寸
    float size;
    // 质量
    float mass;
    // 是否有效
    float valid;
    
    Particle();
    Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float life, float size);
    
    void update(float dt);
    void render(ParticleRenderer & renderer);
    
    void fadeColor(float ratio);
};

#endif /* Particle_hpp */
