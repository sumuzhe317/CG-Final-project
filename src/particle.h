// Particle：粒子属性以及一些预定义参数

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "explode_shape.h"
using namespace std;

const uint32_t TYPE_NUM = 4;      // 爆炸类型数目
const uint32_t CHAR_TYPE_NUM = 26; // 字母爆炸烟花数量
const uint32_t MY_TYPE_NUM = 26; // 自定义烟花数量
#define POLYGON_NUM 2             // 形状数目
#define POSITION_NUMBER 4         // 拖尾粒子数量，越多拖尾越明显
#define MAX_FIREWORK_NUMBER 20    // 最多烟花个数

// 粒子或烟花的形状
enum polygon
{
    sphere_t,
    cube_t
};

// 烟花爆炸的类型
enum fireworktype
{
    mudan_t,
    mudan_random_t,
    diamond_t,
    heart_t,
    bird_t,
    my_test,
    my_heart,
    CHAR_A,
    CHAR_B,
    CHAR_C,
    CHAR_D,
    CHAR_E,
    CHAR_F,
    CHAR_G,
    CHAR_H,
    CHAR_I,
    CHAR_J,
    CHAR_K,
    CHAR_L,
    CHAR_M,
    CHAR_N,
    CHAR_O,
    CHAR_P,
    CHAR_Q,
    CHAR_R,
    CHAR_S,
    CHAR_T,
    CHAR_U,
    CHAR_V,
    CHAR_W,
    CHAR_X,
    CHAR_Y,
    CHAR_Z
};

class Particle
{
public:
    Particle();
    ~Particle();

    // get the information
    GLint getPositionCnt();
    glm::vec3 getPosition();
    glm::vec3 *getPositionArr();
    glm::vec3 getVelocity();
    glm::vec4 getColor();
    GLfloat getRadius();
    polygon getShape();

    // 设置粒子的各种属性
    void setPositionCnt(GLint);
    void setPosition(glm::vec3);
    void setVelocity(glm::vec3);
    void setColor(glm::vec4);
    void setRadius(GLfloat);
    void setShape(polygon);

    static const GLfloat GRAVITY; // 粒子的重力加速度

private:
    GLint position_cnt;                  // 目前记录位置的数量，用于实现拖尾效果
    glm::vec3 position[POSITION_NUMBER]; // 记录位置的数组，用于实现拖尾效果
    glm::vec3 velocity;                  // 速度
    glm::vec4 color;                     // 颜色
    GLfloat radius;                      // 半径
    polygon shape;                       // 形状
};

#endif
