#include "firework.h"
#include "explode_shape.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "sound.h"
#include <irrklang/irrKlang.h>
// const GLfloat Firework::GRAVITY = -0.25f;
const GLfloat Firework::GRAVITY = -9.8f;
const GLfloat Firework::radiusScale = 250.0f;
const GLfloat Firework::velocityScale = 80.0f;
const GLfloat Firework::explodeScale = 80.0f;


Firework::Firework(fireworktype ftype)
{
    initialise(ftype);
}

Firework::~Firework()
{
}

void Firework::initialise(fireworktype ftype)
{
    type = ftype;
    shape = sphere_t;
    hasExploded = false;

    // 初始位置 0.0f, 45.0f, -110.0f
    position_cnt = 1;
    position[POSITION_NUMBER - 1] = glm::vec3(0.0f, 45.0f, -110.0f);

    // 随机初始速度
    velocity = glm::vec3(
        // x轴方向限制在 [-0.3,0.3] * velocityScale
        -0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.6))),
        // y轴方向限制在 [0.78,0.98] * velocityScale
        0.78 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2))),
        // z轴方向限制在 [-0.1,0.1] * velocityScale
        -0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2)))
    );
    velocity *= Firework::velocityScale;

    // 半径限制在 [0.003,0.004] * radiusScale
    radius = 0.003f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.001f)));
    radius *= Firework::radiusScale;
    particleNum = 0;
    particleAliveNum = 0;

    // 生成一定范围内的随机颜色
    glm::vec3 xyz(
        0.4273033440113067627f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.639719843864440918f - 0.4273033440113067627f))),
        0.218611598014831543f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.7708090543746948242f - 0.218611598014831543f))),
        0.0975274890661239624f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8590958118438720703f - 0.0975274890661239624f)))
    );
    color = glm::vec4(
        xyz2rgb(xyz),
        1.0f
    );

    std::cout << "Initialised a firework." << std::endl;
}


void Firework::move(float dt)
{
    // 已爆炸：对粒子应用物理定律
    if (this->isExploded())
    {
        this->explode(dt);
    }
    // 未爆炸：对烟花应用物理定律
    else
    {
        // 更新位置及历史位置
        position_cnt = position_cnt + 1 < POSITION_NUMBER ? position_cnt + 1 : POSITION_NUMBER;
        for (int i = 0; i < POSITION_NUMBER - 1; i++)
        {
            this->position[i] = this->position[i + 1];
        }
        position[POSITION_NUMBER - 1] += (velocity * dt);

        // 更新速度
        velocity.y += (Firework::GRAVITY * dt);

        // 更新后若y方向速度为小于0，爆炸产生粒子
        if (velocity.y <= 0.0f)
        {
            sound::boom();
            velocity.y = 0;
            velocity *= 0.3;
            hasExploded = true;
            color.a = 0.0f;

            // 赋予光照属性
            light_life = 2.0f;
            light_color = glm::vec3(color.r, color.g, color.b);
            light_intensity = 15000;

            // 若为球形烟花或随机球形烟花爆炸，调用函数在球上取样生成粒子
            if (type == mudan_t || type == mudan_random_t)
            {
                // 粒子数量随机
                particleNum = minParticleNum + (rand() % static_cast<int>(maxParticleNum - minParticleNum + 1));
                particleAliveNum = particleNum * particleNum;

                // 球形烟花：单位球均匀采样得到速度
                std::vector<glm::vec3> velSample;
                if (type == mudan_t)
                    velocitySample(particleNum, particleNum, velSample);

                // 爆炸速度限制在 [0.1,0.12] * explodeScale
                GLfloat explosion_speed = Firework::explodeScale * (0.10f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.02))));

                for (int i = 0; i < particleNum * particleNum; i++)
                {
                    // 粒子初始位置为烟花爆炸位置
                    particles[i].setPositionCnt(1);
                    particles[i].setPosition(this->getPosition());

                    // 粒子速度为 单位球采样+烟花速度
                    if (type == mudan_t)
                        particles[i].setVelocity(velSample[i] * explosion_speed + velocity);
                    else
                        particles[i].setVelocity(velocitySampleRandom() * explosion_speed + velocity);

                    // 粒子颜色为随机取样后再乘以原烟花颜色
                    glm::vec3 xyz(
                        0.4273033440113067627f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.639719843864440918f - 0.4273033440113067627f))),
                        0.218611598014831543f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.7708090543746948242f - 0.218611598014831543f))),
                        0.0975274890661239624f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8590958118438720703f - 0.0975274890661239624f)))
                    );
                    glm::vec4 particleColor = glm::vec4(xyz2rgb(xyz), 1.0f) * color;
                    particleColor.a = 1.0f;
                    particles[i].setColor(particleColor);

                    // 粒子半径限制在 [0.002,0.003] * radiusScale
                    particles[i].setRadius(
                        Firework::radiusScale * (0.002f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.001))))
                    );
                    particles[i].setShape(shape);
                }
            }
            // 其他类型烟花爆炸
            else
            {
                initialise_particles();
            }
            std::cout << "Boom!" << std::endl;
        }
    }
}

void Firework::explode(float dt)
{
    // 爆炸之后：光源寿命逐渐减少，光照强度逐渐减弱
    light_life -= dt;
    light_intensity -= 1500 * dt;
    int pNum = getParticleNum();

    // 对每一个粒子应用物理定律，并且不透明度逐渐降低
    for (int i = 0; i < pNum; i++)
    {
        if (particles[i].getColor().a > 0.0f)
        {
            // 更新位置
            particles[i].setPosition(particles[i].getPosition() + (particles[i].getVelocity() * dt));
            // 更新速度
            particles[i].setVelocity(particles[i].getVelocity() + glm::vec3(0.0f, Particle::GRAVITY * dt, 0.0f));

            // 不透明度降低
            float alphaFactor = 0.000005f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.4)));
            particles[i].setColor(particles[i].getColor() - glm::vec4(0.0f, 0.0f, 0.0f, alphaFactor * dt));
            // 不透明度降为0时粒子寿命结束
            if (particles[i].getColor().a <= 0.0f)
            {
                particleAliveNum--;
            }
        }
    }
}

void Firework::initialise_particles()
{
    // 粒子数量为模型顶点数量
    particleNum = vertices_num[type];
    particleAliveNum = vertices_num[type];

    // 爆炸速度限制在 [0.1,0.12] * explodeScale
    GLfloat explosion_speed = Firework::explodeScale * (0.10f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.02))));

    for (int i = 0; i < particleNum; i++)
    {
        // 粒子初始位置为烟花爆炸位置
        particles[i].setPositionCnt(1);
        particles[i].setPosition(this->getPosition());

        // 粒子速度 = 模型顶点位置
        particles[i].setVelocity(explosion_speed * glm::vec3(vertices_arr[type][i * 3], vertices_arr[type][i * 3 + 1], vertices_arr[type][i * 3 + 2]) + velocity);

        // 粒子颜色为随机取样后再乘以原烟花颜色
        glm::vec3 xyz(
            0.4273033440113067627f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.639719843864440918f - 0.4273033440113067627f))),
            0.218611598014831543f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.7708090543746948242f - 0.218611598014831543f))),
            0.0975274890661239624f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8590958118438720703f - 0.0975274890661239624f)))
        );
        glm::vec4 particleColor = glm::vec4(xyz2rgb(xyz), 1.0f) * color;
        particleColor.a = 1.0f;
        particles[i].setColor(particleColor);

        // 粒子半径限制在 [0.002,0.003] * radiusScale
        particles[i].setRadius(
            Firework::radiusScale * (0.002f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.001))))
        );
        particles[i].setShape(shape);
    }
}

glm::vec3 Firework::getSpherePoint(GLfloat u, GLfloat v)
{
    GLfloat pi = glm::pi<GLfloat>();
    GLfloat z = std::cos(pi * u);
    GLfloat x = std::sin(pi * u) * std::cos(2 * pi * v);
    GLfloat y = std::sin(pi * u) * std::sin(2 * pi * v);
    return glm::vec3(x, y, z);
}


void Firework::velocitySample(GLuint Longitude, GLuint Latitude, std::vector<glm::vec3>& vertexes)
{
    GLfloat lon_step = 1.0f / Longitude;
    GLfloat lat_step = 1.0f / Latitude;
    for (size_t lat = 0; lat < Latitude; lat++) {
        for (size_t lon = 0; lon < Longitude; lon++) {
            glm::vec3 point = getSpherePoint(lat * lat_step, lon * lon_step);
            vertexes.push_back(point);
        }
    }
}

glm::vec3 Firework::velocitySampleRandom()
{
    return glm::normalize(glm::vec3(
        -0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2))),
        -0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2))),
        -0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2)))
    ));
}

glm::vec3 Firework::rgb2xyz(glm::vec3 rgb)
{
    rgb.r > 0.04045f ? rgb.r = pow(((rgb.r + 0.055f) / 1.055f), 2.4f) : rgb.r /= 12.92f;
    rgb.g > 0.04045f ? rgb.g = pow(((rgb.g + 0.055f) / 1.055f), 2.4f) : rgb.g /= 12.92f;
    rgb.b > 0.04045f ? rgb.b = pow(((rgb.b + 0.055f) / 1.055f), 2.4f) : rgb.b /= 12.92f;

    glm::mat3 A(glm::vec3(0.412456439089692, 0.212672851405623, 0.019333895582329),
        glm::vec3(0.357576077643909, 0.715152155287818, 0.119192025881303),
        glm::vec3(0.180437483266399, 0.072174993306560, 0.950304078536368));

    return A * rgb;
}

glm::vec3 Firework::xyz2rgb(glm::vec3 xyz)
{
    glm::mat3 A(glm::vec3(3.240454162114104, -0.969266030505187, 0.055643430959115),
        glm::vec3(-1.537138512797716, 1.876010845446694, -0.204025913516754),
        glm::vec3(-0.498531409556016, 0.041556017530350, 1.057225188223179));

    glm::vec3 rgb = A * xyz;

    rgb.r > 0.0031308f ? rgb.r = 1.055f * pow(rgb.r, (1.0f / 2.4f)) - 0.055f : rgb.r *= 12.92f;
    rgb.g > 0.0031308f ? rgb.g = 1.055f * pow(rgb.g, (1.0f / 2.4f)) - 0.055f : rgb.g *= 12.92f;
    rgb.b > 0.0031308f ? rgb.b = 1.055f * pow(rgb.b, (1.0f / 2.4f)) - 0.055f : rgb.b *= 12.92f;

    return rgb;
}


GLboolean Firework::isExploded()
{
    return hasExploded;
}

GLint Firework::getPositionCnt()
{
    return position_cnt;
}

glm::vec3 Firework::getPosition()
{
    return position[POSITION_NUMBER - 1];
}

glm::vec3* Firework::getPositionArr()
{
    return position;
}

glm::vec3 Firework::getVelocity()
{
    return velocity;
}

glm::vec4 Firework::getColor()
{
    return color;
}

GLfloat Firework::getRadius()
{
    return radius;
}


GLint Firework::getParticleNum()
{
    if (type == mudan_t || type == mudan_random_t)
        return particleNum * particleNum;
    return particleNum;
}

GLint Firework::getParticleAliveNum()
{
    return particleAliveNum;
}

Particle* Firework::getParticles()
{
    return particles;
}

polygon Firework::getShape()
{
    return shape;
}

fireworktype Firework::getType()
{
    return type;
}

GLfloat Firework::getLightLife()
{
    return light_life;
}

GLfloat Firework::getLightIntensity()
{
    return light_intensity;
}


glm::vec3 Firework::getLightColor()
{
    return light_color;
}