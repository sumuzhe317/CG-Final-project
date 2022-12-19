// Firework：烟花属性及烟花引擎

#ifndef __FIREWORK_H__
#define __FIREWORK_H__

#include "particle.h"

class Firework
{
public:
    Firework(fireworktype ftype,glm::vec3 start=glm::vec3(0.0f, 60.0f, -200.0f));                               // 根据爆炸类型初始化烟花
    ~Firework();                                                // 销毁烟花

    // 烟花引擎
    void initialise(fireworktype ftype);                        // 随机初始化烟花属性
    void my_initialise(fireworktype ftype,glm::vec3 start);                        // 随机初始化烟花属性
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
    GLboolean hasExploded;                                      // whether explode
    GLint position_cnt;                                         // position records
    glm::vec3 position[POSITION_NUMBER];                        // position arrays
    glm::vec3 velocity;                                         // speed
    glm::vec4 color;                                            // color
    GLfloat radius;                                             // radius
    polygon shape;                                              // shape of particle
    fireworktype type;                                          // shape of boom

    // 静态变量
    static const GLfloat GRAVITY;                               // g for firework
    static const GLfloat radiusScale;                           // scale for radius
    static const GLfloat velocityScale;                         // scale for speed
    static const GLfloat explodeScale;                          // scale for explode speed

    // 粒子相关属性
    static const GLint minParticleNum = 15;                     // sqrt of minimum
    static const GLint maxParticleNum = 20;                     // sqrt of maxnum
    GLint particleNum;                                          // the sum of particle
    GLint particleAliveNum;                                     // alive sum of particle
    Particle particles[maxParticleNum * maxParticleNum];        // particle's records

    // 光照相关属性
    GLfloat light_life;                                         // light point's life
    GLfloat light_intensity;                                    // light point's intensity
    glm::vec3 light_color;                                      // light point's color

    // 球形烟花与随机球形烟花的粒子初始化
    glm::vec3 getSpherePoint(GLfloat, GLfloat);                 // 根据经纬在球上取点
    glm::vec3 velocitySampleRandom();                           // sample in the sphere
    void velocitySample(GLuint Longitude, GLuint Latitude,
        std::vector<glm::vec3>& vertexes);                      // sample in the sphere

    // 其他类型烟花的粒子初始化
    void initialise_particles();


    // 通用更新
    void posUpdate(float timeScale);

    // 通用初始化
    glm::vec3 velocityInitRandom();
    GLfloat radiusInitRandom(GLfloat start, GLfloat gap);
    glm::vec3 xyzColorInitRandom();
    GLuint particleNumInitRandom();
    GLfloat explodeSpeedInitRandom();

    glm::vec3 posInit();

    // XYZ与RGB空间互换
    glm::vec3 rgb2xyz(glm::vec3);
    glm::vec3 xyz2rgb(glm::vec3);
};

#endif  // !__FIREWORK_H__