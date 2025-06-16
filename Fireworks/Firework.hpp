//
//  Firework.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#ifndef Firework_hpp
#define Firework_hpp

#include <glm/glm.hpp>

#include <vector>
#include <map>
#include <string>

#include "Particle.hpp"
#include "ParticleRenderer.hpp"

class Firework
{
public:
    // 位置
    glm::vec3 position;
    // 速度
    float vy;
    // 颜色
    glm::vec3 color;
    // 尺寸
    float size;
    // 质量
    float mass;
    // 爆炸时间
    float restTime;
    // 是否爆炸
    bool exploded;
    // 是否消失
    bool vanished;
    // 粒子数量
    unsigned int particlesNum;
    // 粒子
    std::vector<Particle> particles;
    // 产生粒子生命均值、方差
    float particleLifeMean, particleLifeSD;
    // 产生粒子尺寸大小、方差
    float particleSizeMean, particleSizeSD;
    // 爆炸强度
    float strength;
    // 生成粒子颜色分布
    std::vector<std::pair<std::string, float>> colorDistributions;
    
    Firework(glm::vec3 position, float vy, glm::vec3 color, float explodeTime, std::map<std::string, float> properties);
        
    void update(float dt);
    void render(ParticleRenderer & renderer);
    
private:
    Particle generateParticle();
    void initFirework(std::map<std::string, float> properties);
};

#endif /* Firework_hpp */
