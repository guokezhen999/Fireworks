//
//  SkyboxRenderer.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/6/2.
//

#ifndef SkyboxRenderer_hpp
#define SkyboxRenderer_hpp

#include "Shader.hpp"

unsigned int loadCubemap(std::vector<std::string> faces);

class SkyboxRenderer
{
public:
    Shader shader;
    
    SkyboxRenderer(Shader & shader);
    ~SkyboxRenderer();
    
    void renderSkybox();
    
private:
    unsigned int VAO;
    unsigned int texture;
    
    void initRendererData();
};

#endif /* SkyboxRenderer_hpp */
