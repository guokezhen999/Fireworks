//
//  Game.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#ifndef Game_hpp
#define Game_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image/stb_image.h"

#include <vector>

#include "Firework.hpp"
#include "Camera.hpp"
#include "SkyboxRenderer.hpp"

class Game
{
public:
    GLboolean keys[1024];
    GLuint width, height;
    
    Camera * camera;
    ParticleRenderer * particleRenderer;
    SkyboxRenderer * skyboxRenderer;
    
    std::vector<Firework> fireworks;
    
    Game(GLuint width, GLuint height);
    ~Game();
    
    // 初始化
    void init();
    
    // 循环
    void processInput(GLFWwindow * window, float dt);
    void update(GLfloat dt);
    void render();
    
};

#endif /* Game_hpp */
