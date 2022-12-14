// Firework：烟花属性及烟花引擎

#ifndef __FIREWORK_H__
#define __FIREWORK_H__

#include "particle.h"

class Firework
{
public:
    Firework(fireworktype ftype);                               // 根据爆炸类型初始化烟花
    ~Firework();                                                // 销毁烟花

    // 烟花引擎
    void initialise(fireworktype ftype);                        // 随机初始化烟花属性
    void move(float);                                           // 烟花运动的物理模型
    void explode(float);                                        // 粒子爆炸的物理模型

    // 获取烟花各种属性
    GLboolean isExploded();
    GLint getPositionCnt();
    glm::vec3 getPosition();
    glm::vec3* getPositionArr();
    glm::vec3 getVelocity();
    glm::vec4 getColor();
    GLfloat getRadius();
    GLint getParticleNum();
    GLint getParticleAliveNum();
    Particle* getParticles();
    polygon getShape();
    fireworktype getType();
    GLfloat getLightLife();
    GLfloat getLightIntensity();
    glm::vec3 getLightColor();

private:
    // 烟花属性
    GLboolean hasExploded;                                      // 是否已经爆炸
    GLint position_cnt;                                         // 目前记录位置的数量，用于实现拖尾效果
    glm::vec3 position[POSITION_NUMBER];                        // 记录位置的数组，用于实现拖尾效果
    glm::vec3 velocity;                                         // 速度
    glm::vec4 color;                                            // 颜色
    GLfloat radius;                                             // 半径
    polygon shape;                                              // 形状
    fireworktype type;                                          // 爆炸类型

    // 静态变量
    static const GLfloat GRAVITY;                               // 烟花的重力加速度
    static const GLfloat radiusScale;                           // 初始半径的缩放比例，用于适应世界范围
    static const GLfloat velocityScale;                         // 初始速度的缩放比例，用于适应世界范围
    static const GLfloat explodeScale;                          // 爆炸速度的缩放比例，用于适应世界范围

    // 粒子相关属性
    static const GLint minParticleNum = 15;                     // 最小粒子数目的平方根
    static const GLint maxParticleNum = 20;                     // 最大粒子数目的平方根
    GLint particleNum;                                          // 粒子总数
    GLint particleAliveNum;                                     // 存活的粒子数目(不透明度大于0)
    Particle particles[maxParticleNum * maxParticleNum];        // 粒子

    // 光照相关属性
    GLfloat light_life;                                         // 光源寿命
    GLfloat light_intensity;                                    // 光照强度
    glm::vec3 light_color;                                      // 光源颜色

    // 球形烟花与随机球形烟花的粒子初始化
    glm::vec3 getSpherePoint(GLfloat, GLfloat);                 // 根据经纬在球上取点
    glm::vec3 velocitySampleRandom();                           // 在球上随机采样
    void velocitySample(GLuint Longitude, GLuint Latitude,
        std::vector<glm::vec3>& vertexes);                      // 在球上均匀采样

    // 其他类型烟花的粒子初始化
    void initialise_particles();

    // XYZ与RGB空间互换
    glm::vec3 rgb2xyz(glm::vec3);
    glm::vec3 xyz2rgb(glm::vec3);
};

#endif  // !__FIREWORK_H__