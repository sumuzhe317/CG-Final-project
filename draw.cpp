// Draw：渲染烟花

#include "draw.h"
#include "generate_vertices.h"

void init_vertices()
{
    generate_sphere_vertices(sphere_vertices, sphere_indices);
    generate_cube_vertices(cube_vertices, cube_indices);
}

Draw::Draw()
{
    init_vertices();
    glGenVertexArrays(POLYGON_NUM, VAO);
    glGenBuffers(POLYGON_NUM, VBO);
    glGenBuffers(POLYGON_NUM, EBO);
    for (int i = 0; i < POLYGON_NUM; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, vertices[i]->size() * sizeof(float), &(*vertices[i])[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[i]->size() * sizeof(int), &(*indices[i])[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
}

Draw::~Draw()
{
    glDeleteVertexArrays(POLYGON_NUM, VAO);
    glDeleteBuffers(POLYGON_NUM, VBO);
    glDeleteBuffers(POLYGON_NUM, EBO);
}


void Draw::draw_polygon(glm::vec3* position, GLint pos_cnt, GLfloat radius, glm::vec4 color, polygon type, Shader& myshader)
{
    glBindVertexArray(VAO[type]);
    // 渲染多个位置实现拖尾
    for (int i = 0; i < pos_cnt; i++)
    {
        // 变换到中心，根据半径放缩比例
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position[POSITION_NUMBER - 1 - i]);
        // 半径逐渐减小
        model = glm::scale(model, glm::vec3(radius / (i + 1) * 1.5));
        myshader.setMat4("model", model);
        // 不透明度逐渐降低
        glm::vec4 fadecolor = color;
        fadecolor.w = fadecolor.w / (i + 1) * 1.5;
        myshader.setVec4("vertexColor", fadecolor);
        // 渲染
        glDrawElements(GL_TRIANGLES, indices[type]->size(), GL_UNSIGNED_INT, 0);
    }
}

void Draw::draw_firework(vector<Firework>::iterator fw, Shader& myshader)
{
    // 未爆炸：渲染一个几何体（烟花本体）
    if (!fw->isExploded())
        draw_polygon(fw->getPositionArr(), fw->getPositionCnt(), fw->getRadius(), fw->getColor(), fw->getShape(), myshader);
    // 已爆炸：渲染多个几何体（烟花粒子）
    else
    {
        for (int i = 0; i < fw->getParticleNum(); i++)
        {
            Particle* grain_ptr = fw->getParticles() + i;
            // 粒子不透明度为0即寿命结束
            if (grain_ptr->getColor().w <= 0.0f)
                continue;
            draw_polygon(grain_ptr->getPositionArr(), grain_ptr->getPositionCnt(), grain_ptr->getRadius(), grain_ptr->getColor(), grain_ptr->getShape(), myshader);
        }
    }
}