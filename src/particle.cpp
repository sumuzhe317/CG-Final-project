#include "particle.h"

const GLfloat Particle::GRAVITY = -2.5f;

Particle::Particle()
{
}

Particle::~Particle()
{
}

GLint Particle::getPositionCnt()
{
    return position_cnt;
}

glm::vec3 Particle::getPosition()
{
    return position[POSITION_NUMBER - 1];
}

glm::vec3* Particle::getPositionArr()
{
    return position;
}

glm::vec3 Particle::getVelocity()
{
    return velocity;
}

glm::vec4 Particle::getColor()
{
    return color;
}

GLfloat Particle::getRadius()
{
    return radius;
}

polygon Particle::getShape()
{
    return shape;
}

void Particle::setPositionCnt(GLint position_cnt)
{
    this->position_cnt = position_cnt;
}

void Particle::setPosition(glm::vec3 position)
{
    position_cnt = position_cnt + 1 < POSITION_NUMBER ? position_cnt + 1 : POSITION_NUMBER;
    for (int i = 0; i < POSITION_NUMBER - 1; i++)
        this->position[i] = this->position[i + 1];
    this->position[POSITION_NUMBER - 1] = position;
}

void Particle::setVelocity(glm::vec3 velocity)
{
    this->velocity = velocity;
}

void Particle::setColor(glm::vec4 color)
{
    this->color = color;
}

void Particle::setRadius(GLfloat radius)
{
    this->radius = radius;
}

void Particle::setShape(polygon shape)
{
    this->shape = shape;
}