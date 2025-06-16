//
//  PaticleRenderer.cpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/18.
//

#include "ParticleRenderer.hpp"
#include "Constants.h"

#include <math.h>

ParticleRenderer::ParticleRenderer(Shader & shader)
: shader(shader)
{
    initRendererData();
}

ParticleRenderer::~ParticleRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void ParticleRenderer::renderParticle(glm::vec3 position, float size, glm::vec3 color)
{
    this->shader.use();
    // 设置model矩阵
    glm::mat4 model(1.0f);
    model = glm::scale(model, glm::vec3(size, size, size));
    model = glm::translate(model, position);
    this->shader.setMatrix4f("model", model);
    
    // 设置颜色
    this->shader.setVector3f("color", color);
    
    // 绘制粒子
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void ParticleRenderer::initRendererData()
{
    unsigned int VBO, EBO;
    
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    createSphere(LAT_SEGMENTS, LON_SEGMENTS, vertices, indices);
    this->indexCount = static_cast<unsigned int>(indices.size());
    
    // 创建VAO, VBO, EBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // 绑定VAO
    glBindVertexArray(this->VAO);
    
    // 绑定VBO并传递数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    // 绑定EBO并传递数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
    
    // 配置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VAO
    glBindVertexArray(0);
}

void ParticleRenderer::createSphere(unsigned int latSegments, unsigned int lonSegments, std::vector<GLfloat> & vertices, std::vector<GLuint> & indices)
{
    // 顶点数据
    for (unsigned int i = 0; i <= latSegments; i++)
    {
        float theta = i * PI / latSegments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        
        for (unsigned int j = 0; j <= lonSegments; j++)
        {
            float phi = j * 2 * PI / lonSegments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);
            
            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    // 索引数据
    for (unsigned int i = 0; i < latSegments; i++)
    {
        for (unsigned int j = 0; j < lonSegments; j++)
        {
            GLuint first = (i * (lonSegments + 1)) + j;
            GLuint second = first + lonSegments + 1;
            
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

