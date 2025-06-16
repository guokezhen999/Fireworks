//
//  PaticleRenderer.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/18.
//

#ifndef PaticleRenderer_hpp
#define PaticleRenderer_hpp

#include <vector>

#include "Shader.hpp"

class ParticleRenderer
{
public:
    Shader shader;
    
    ParticleRenderer(Shader & shader);
    ~ParticleRenderer();
    
    void renderParticle(glm::vec3 position, float size, glm::vec3 color);
    
private:
    unsigned int VAO;
    unsigned int indexCount;
    
    void initRendererData();
    void createSphere(unsigned int latSegment, unsigned int lonSegment, std::vector<GLfloat> & vertices, std::vector<GLuint> & indices);
};

#endif /* PaticleRenderer_hpp */
