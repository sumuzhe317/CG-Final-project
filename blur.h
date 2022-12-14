// Blur：进行辉光处理

#ifndef __SHADING_H__
#define __SHADING_H__

// 窗口大小
unsigned int SCR_WIDTH = 1440;
unsigned int SCR_HEIGHT = 900;

class Blur
{
public:
    Blur();
    ~Blur();
    // 其他渲染需要先调用此函数，在类的帧缓冲中渲染方便后续处理
    void bindFrameBuffer();
    // 辉光后处理
    void blurTheFrame(Shader& BlurShader, Shader& ResultShader);
private:
    GLuint framebuffer;
    GLuint texColorBuffer[2];
    GLuint BlurFBO[2];
    GLuint BlurColorbuffers[2];
    GLuint VAO, VBO, EBO, RBO;
    void init_rectangle();
    void init_framebuffer();
    void init_Blur();
    void BlurShading(Shader& BlurShader);
    void ResultShading(Shader& BlurShader);
};

//初始化
Blur::Blur()
{
    init_framebuffer();
    init_Blur();
    init_rectangle();
}

Blur::~Blur()
{
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(2, texColorBuffer);
    glDeleteRenderbuffers(1, &RBO);

    glDeleteFramebuffers(2, BlurFBO);
    glDeleteTextures(2, BlurColorbuffers);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// 将所有的渲染结果先渲染到缓冲区中
void Blur::bindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// 经过处理最后再将结果渲染到屏幕上
void Blur::blurTheFrame(Shader& BlurShader, Shader& ResultShader)
{
    BlurShading(BlurShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ResultShading(ResultShader);
}

// 初始化帧缓冲
void Blur::init_framebuffer()
{
    // 生成FBO，对其绑定两个颜色缓冲，一个是原图，一个是提取的需要模糊的亮部
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(2, texColorBuffer);
    // 纹理 生成窗口大小的空白纹理
    for (int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texColorBuffer[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texColorBuffer[i], 0);
    }

    // RBO 渲染缓冲由于以OpenGL原生数据存储，OpenGL进行一定内存优化速度更快
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    // 对FBO绑定两个attchment，一个是原图，一个是提取的需要模糊的亮部，这一步是用于color.fs着色器输出
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

    // 绑定默认帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Blur缓冲初始化
void Blur::init_Blur()
{
    // 生成两个FBO，用于 水平和垂直两方向 多次模糊
    glGenFramebuffers(2, BlurFBO);
    glGenTextures(2, BlurColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, BlurFBO[i]);
        glBindTexture(GL_TEXTURE_2D, BlurColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, BlurColorbuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }
}

// 将帧缓冲渲染到屏幕上的矩形初始化
void Blur::init_rectangle()
{
    float vertices[] = {
        // positions     // texture coords
         1.0f,  1.0f,    1.0f, 1.0f, // top right
         1.0f, -1.0f,    1.0f, 0.0f, // bottom right
        -1.0f, -1.0f,    0.0f, 0.0f, // bottom left
        -1.0f,  1.0f,    0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //生成VAO、VBO、EBO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // texture coord attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void Blur::BlurShading(Shader& BlurShader)
{
    // 将提取的亮部作为输入纹理，高斯模糊本是二维的模糊，可分解为两次一维模糊，以下实现是轮流进行五次水平模糊和垂直模糊。
    GLuint input_texture = texColorBuffer[1];
    // horizontal = true 是水平模糊 ，first_iteration用于将input_texture作为输入，amount/2为模糊次数
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    // 激活texture0，用于绑定输入，下面setInt("image", 0) 的0的来源
    BlurShader.use();
    glActiveTexture(GL_TEXTURE0);

    // 以先水平模糊后垂直模糊的顺序进行模糊
    for (unsigned int i = 0; i < amount; i++)
    {
        // 每次绑定horizontal对应的FBO作为输出，并设置相应模糊方式
        glBindFramebuffer(GL_FRAMEBUFFER, BlurFBO[horizontal]);
        BlurShader.setInt("horizontal", horizontal);
        // 第一次绑定input_texture作为输入，之后以!horizontal的纹理作为输入
        glBindTexture(GL_TEXTURE_2D, first_iteration ? input_texture : BlurColorbuffers[!horizontal]);
        BlurShader.setInt("image", 0);
        // 切换模糊方式
        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
        // 绑定VAO画矩形框
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Blur::ResultShading(Shader& ResultShader)
{
    // 输入两个纹理，一个是渲染原图，一个是模糊后图象
    GLuint tex1 = texColorBuffer[0];
    GLuint tex2 = BlurColorbuffers[0];
    // 分别绑定到GL_TEXTURE0、GL_TEXTURE1上用于输入
    ResultShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    ResultShader.setInt("screenTexture", 0);
    ResultShader.setInt("BlurTexture", 1);
    // 画矩形框
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#endif