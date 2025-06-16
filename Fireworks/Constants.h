//
//  Constants.h
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/14.
//

#ifndef Constants_h
#define Constants_h

#include <glm/glm.hpp>

using namespace std;


// 窗口属性
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// 相机属性
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  10.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

const float Z_NEAR = 0.1f;
const float Z_FAR = 500.0f;

// 重力
const float GRAVITY = 9.81;

// 阻力
const float FIREWORK_DRAG_COEF = 0.015f;
const float PARTICLE_DRAG_COEF = 0.008f;

// 烟花生成速率0.0-1.0
const float GEN_RATE = 0.3f;

// 烟花初速度
const float VY_MIN = 50.0f;
const float VY_MAX = 100.0f;

// 烟花生成位置
const float X_RANGE_0 = -400.0;
const float X_RANGE_1 = 400.0f;
const float Z_RANGE_0 = -100.0f;
const float Z_RANGE_1 = -800.0f;

// 烟花未爆炸的颜色
const glm::vec3 FIREWORK_COLOR(0.1f, 0.1f, 0.1f);

// 最小粒子数量
const unsigned int MIN_PARTICLE_NUM = 30;

// 最小粒子寿命
const float MIN_PARTICLE_LIFE = 1.0f;

// 最小粒子尺寸
const float MIN_PARTICLE_SIZE = 0.01f;

// 颜色表
const glm::vec3 RED(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE(0.0f, 0.0f, 1.0f);

const glm::vec3 WHITE(1.0f, 1.0f, 1.0f);
const glm::vec3 LIGHT_GRAY(0.75f, 0.75f, 0.75f);
const glm::vec3 GRAY(0.5f, 0.5f, 0.5f);
const glm::vec3 DARK_GRAY(0.25f, 0.25f, 0.25f);
const glm::vec3 BLACK(0.0f, 0.0f, 0.0f);

const glm::vec3 YELLOW(1.0f, 1.0f, 0.0f);
const glm::vec3 MAGANTA(1.0f, 0.0f, 1.0f);
const glm::vec3 PURPLE(0.63f, 0.125f, 0.94f);
const glm::vec3 PINK(1.0f, 0.75f, 0.75f);
const glm::vec3 ORANGE(1.0f, 0.64f, 0.0f);
const glm::vec3 CYAN(0.0f, 1.0f, 1.0f);
const glm::vec3 LIGHT_BLUE(0.69f, 0.88f, 1.0f);

// 渲染设置
const float PI = 3.1415926;
const unsigned int LAT_SEGMENTS = 15;
const unsigned int LON_SEGMENTS = 15;

// 地面范围
const float GROUND_X_0 = -1000.0f;
const float GROUND_X_1 = 1000.0f;
const float GROUND_Z_0 = -1000.0f;
const float GROUND_Z_1 = 1000.0f;

#endif /* Constants_h */



