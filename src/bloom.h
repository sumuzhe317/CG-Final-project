// Bloom：进行辉光处理

#ifndef __BLOOM_H__
#define __BLOOM_H__

#include "shader.h"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

class Bloom
{
public:
    Bloom();
    ~Bloom();
    // first call this func
    void bindFrameBuffer();
    // bloom set
    void BloomDraw(Shader& BloomShader, Shader& ResultShader);
private:
    GLuint framebuffer;
    GLuint texColorBuffer[2];
    GLuint BloomFBO[2];
    GLuint BloomColorbuffers[2];
    GLuint VAO, VBO, EBO, RBO;
    void init_rectangle();
    void init_framebuffer();
    void init_Bloom();
    void BloomShading(Shader& BloomShader);
    void ResultShading(Shader& BloomShader);
};



#endif