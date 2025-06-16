//
//  Camera.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/14.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // 相机的位置和方向
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // 欧拉角
    float yaw;
    float pitch;
    // 其余选项
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // 向量构造器
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    
    // 标量构造器
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // 返回视图变换矩阵
    glm::mat4 getViewMatrix() const;
    
    // 处理键盘输入对应移动
    void processKeyboard(CameraMovement direction, float deltaTime);

    // 处理鼠标输入改变视角
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // 处理鼠标滚动进行缩放
    void processMouseScroll(float yoffset);

private:
    // 通过欧拉角计算前、上、右方向
    void updateCameraVectors();
};

#endif /* Camera_hpp */
