// 顶点生成器：生成几何体的顶点和索引数组

#ifndef __GENERATE_VERTICES_H__
#define __GENERATE_VERTICES_H__

#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#define M_PI 3.14159265358979323846
using namespace std;

// 球的顶点和索引
vector<float> sphere_vertices;
vector<int> sphere_indices;

// 立方体的顶点和索引
vector<float> cube_vertices;
vector<int> cube_indices;

// 顶点数组，索引数组
vector<float>* vertices[] = { &sphere_vertices, &cube_vertices };
vector<int>* indices[] = { &sphere_indices, &cube_indices };

// 生成球的顶点和索引
void generate_sphere_vertices(vector<float>& polygon_vertices, vector<int>& polygon_indices)
{
    polygon_indices.clear();
    polygon_vertices.clear();

    glm::vec3 position = glm::vec3(0.0f);
    float radius = 1.0f;

    const int xymax = 5;
    const int maximum = xymax * xymax;

    // 顶点数组：根据经纬线在球上取样
    for (int x = 0; x < xymax; x++)
        for (int y = 0; y < xymax; y++)
        {
            float xseg = (float)x / (float)xymax;
            float yseg = (float)y / (float)xymax;
            float xPos = std::cos(xseg * 2.0f * M_PI) * std::sin(yseg * M_PI);
            float yPos = std::cos(yseg * M_PI);
            float zPos = std::sin(xseg * 2.0f * M_PI) * std::sin(yseg * M_PI);
            sphere_vertices.push_back(xPos);
            sphere_vertices.push_back(yPos);
            sphere_vertices.push_back(zPos);
        }

    // 索引数组：将顶点组成三角面片
    for (int i = 0;i < xymax;i++)
        for (int j = 0;j < xymax;j++)
        {
            sphere_indices.push_back((i * xymax + j) % maximum);
            sphere_indices.push_back(((i + 1) * xymax + j) % maximum);
            sphere_indices.push_back(((i + 1) * xymax + j + 1) % maximum);
            sphere_indices.push_back((i * xymax + j) % maximum);
            sphere_indices.push_back(((i + 1) * xymax + j + 1) % maximum);
            sphere_indices.push_back((i * xymax + j + 1) % maximum);
        }
}

// 生成立方体的顶点和索引
void generate_cube_vertices(vector<float>& polygon_vertices, vector<int>& polygon_indices)
{
    float cubev[24] = {
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
    };
    int cubei[24] = {
        0, 2, 3, 1,
        0, 4, 6, 2,
        0, 1, 5, 4,
        4, 5, 7, 6,
        1, 3, 7, 5,
        2, 6, 7, 3,
    };
    polygon_vertices.clear();
    polygon_indices.clear();
    for (int i = 0; i < 24; i++)
    {
        polygon_vertices.push_back(cubev[i]);
        polygon_indices.push_back(cubei[i]);
    }
}

#endif