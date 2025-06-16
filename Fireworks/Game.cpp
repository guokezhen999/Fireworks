//
//  Game.cpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/15.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Constants.h"
#include "Shader.hpp"

#include <iostream>
#include <random>

#include <GLFW/glfw3.h>

Game::Game(GLuint width, GLuint height)
: keys(), width(width), height(height), fireworks()
{
    camera = new Camera();
}

Game::~Game()
{
    delete camera;
    delete particleRenderer;
}

void Game::init()
{
    // 设置shader
    Shader particleShader("res/shaders/basic.vsh", "res/shaders/basic.fsh");
    Shader skyboxShader("res/shaders/skybox.vsh", "res/shaders/skybox.fsh");
    
    // 初始化renderer
    particleRenderer = new ParticleRenderer(particleShader);
    skyboxRenderer = new SkyboxRenderer(skyboxShader);

    // 读取烟花数据
    ResourceManager::loadAllProperties();
    for (auto & properties : ResourceManager::allFireworkProperties)
    {
        for (auto & pair : properties)
        {
            std::cout << pair.first << ": " << pair.second << '\n';
        }
    }
}


void Game::processInput(GLFWwindow * window, GLfloat dt)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        camera->processKeyboard(UP, dt);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        camera->processKeyboard(DOWN, dt);
}

void Game::update(GLfloat dt)
{
    std::uniform_real_distribution<float> generateFirework(0.0f, 1.0f);
    std::uniform_int_distribution<int> chooseFirework(0, (int)ResourceManager::allFireworkProperties.size() - 1);
    std::uniform_real_distribution<float> vyRandom(VY_MIN, VY_MAX);
    std::uniform_real_distribution<float> xRandom(X_RANGE_0, X_RANGE_1);
    std::uniform_real_distribution<float> zRandom(Z_RANGE_0, Z_RANGE_1);

    // 根据生成率产生烟花
    if (generateFirework(ResourceManager::generator) < GEN_RATE)
    {
        // 选择产生烟花种类
        const std::map<std::string, float> & properties = ResourceManager::allFireworkProperties[chooseFirework(ResourceManager::generator)];
        // 选择烟花速度
        float vy = vyRandom(ResourceManager::generator);
        // 选择烟花产生位置
        float x = xRandom(ResourceManager::generator);
        float z = zRandom(ResourceManager::generator);
        glm::vec3 position(x, 0.0f, z);
        // 烟花爆炸时间
        float initTime = vy / GRAVITY * 0.7f;
        fireworks.push_back(Firework(position, vy, FIREWORK_COLOR, initTime, properties));
    }
    
    // 烟花进行更新
    for (unsigned int i = 0; i < fireworks.size(); i++)
    {
        fireworks[i].update(dt);
        fireworks.erase(
            std::remove_if(fireworks.begin(), fireworks.end(), [](const Firework& f){
                return f.vanished;
            }),
            fireworks.end()
        );
    }
}

void Game::render()
{
    glm::mat4 view = this->camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)width / (float)height, Z_NEAR, Z_FAR);
    
    this->particleRenderer->shader.use();
    this->particleRenderer->shader.setMatrix4f("view", view);
    this->particleRenderer->shader.setMatrix4f("projection", projection);
    
    for (Firework & firework : fireworks)
    {
        firework.render(*particleRenderer);
    }
    
    // 渲染天空盒子
//    glDepthFunc(GL_LEQUAL);
//    this->skyboxRenderer->shader.use();
//    glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
//    this->skyboxRenderer->shader.setMatrix4f("view", skyboxView);
//    this->skyboxRenderer->shader.setMatrix4f("projection", projection);
//    this->skyboxRenderer->renderSkybox();

}
