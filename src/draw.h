// Draw：渲染烟花

#ifndef __DRAW_H__
#define __DRAW_H__

#include <glad/glad.h>
#include "firework.h"
#include "shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

// 生成基本几何体的顶点数组和索引数组
void init_vertices();

class Draw
{
private:
    // 粒子形状顶点的缓存
    GLuint VAO[POLYGON_NUM], VBO[POLYGON_NUM], EBO[POLYGON_NUM];
public:
    // 将基本几何体的顶点和索引绑定到 OpenGL缓存
    Draw();
    // 释放缓存
    ~Draw();
    // 渲染单个几何体
    void draw_polygon(glm::vec3* position, GLint pos_cnt, GLfloat radius, glm::vec4 color, polygon type, Shader& myshader);
    // 渲染一个烟花
    void draw_firework(vector<Firework>::iterator fw, Shader& myshader);
};

#endif