#include "base_func.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "model.h"
#include "bloom.h"
#include "particle_system.h"
#include "firework.h"
#include "skybox.h"
#include "sound.h"
#include <irrklang/irrKlang.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);
void set_point_light(Shader& blinnphongshader);

// settings
// time scale
float time_scale = 3.0f;
vector<Firework> firework_list;
// use to indentify the press button
bool PRESS[TYPE_NUM] = { 0 };                                               // whether the 1~7 button is pressed
bool PRESS_CHAR[CHAR_TYPE_NUM] = { 0 };                                               // whether the char button is pressed
bool PRESS_MY[MY_TYPE_NUM] = {0};
bool MOUSEPRESS = false;                                                    // whether press
bool MOUSEABLE = false;                                                     // whether enable


// camera
Camera camera(glm::vec3(0.0f, 180.0f, -22.0f));
//Camera camera(glm::vec3(0.0f, 1300.f, 110.0f));
float NEAR = 0.1f;
float FAR = 800.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.1f;                                                     // indentify the frame's time gap
float lastFrame = 0.0f;                                                     // indentify the last frame

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// sound
double volume = 0.1f;

// skybox's images
vector<std::string> faces
{
    "resources/textures/skybox/right.jpg",
    "resources/textures/skybox/left.jpg",
    "resources/textures/skybox/top.jpg",
    "resources/textures/skybox/bottom.jpg",
    "resources/textures/skybox/front.jpg",
    "resources/textures/skybox/back.jpg"
};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------

    // modify the screen's settings according to the monitor
    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
    SCR_WIDTH = mode->width / 1.2;
    SCR_HEIGHT = mode->height / 1.2;
    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    // create the window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGFINALPROJECT-FIREWORK", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader zprogram
    // ------------------------------------
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader ColorShader("shaders/Color.vs", "shaders/Color.fs");
    Shader BloomShader("shaders/Result.vs", "shaders/Bloom.fs");
    Shader ResultShader("shaders/Result.vs", "shaders/Result.fs");
    Shader FloorShader("shaders/Blinn_Phong.vs", "shaders/Blinn_Phong.fs");
    Shader CastleShader("shaders/Blinn_Phong.vs", "shaders/Blinn_Phong.fs");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    unsigned int cubemapTexture = loadCubemap(faces);

    
    //////////////////////////////////////////////////////////////////////////////////////////
    
    // 辉光效果初始化
    Bloom bloom;

    // 加载烟花图元
    ParticleSystem particle_system;

    Skybox skybox;

    // 加载地面模型
    cout << "floor" << endl;
    Model floor("resources/ground/uploads_files_3829365_church+floor.obj"); 
    cout << "castle" << endl;
    Model castle("resources/Japanese_Temple_Model/Japanese_Temple.obj");
    sound::init(volume);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // firework
        // 背景颜色
        bloom.bindFrameBuffer();

        // 设置烟花着色器
        ColorShader.use();
        // 视角变换、投影变换
        // 世界变换交给draw_firework函数
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR, FAR);
        ColorShader.setMat4("view", view);
        ColorShader.setMat4("projection", projection);
        // draw the firework
        for (vector<Firework>::iterator firework_it = firework_list.begin(); firework_it != firework_list.end();)
        {
            particle_system.draw_firework(firework_it, ColorShader);
            firework_it->move(time_scale * deltaTime);
            // exploded and dead
            if (firework_it->isExploded() && firework_it->getParticleAliveNum() <= 0)
            {
                firework_it = firework_list.erase(firework_it);
                std::cout << "Delete a firework." << std::endl;
            }
            else
            {
                firework_it++;
            }
        }

        // floor shader
        FloorShader.use();
        // set the MVP transformation
        FloorShader.setMat4("view", view);
        FloorShader.setMat4("projection", projection);
        glm::mat4 floorTransform = glm::mat4(1.0f);
        floorTransform = glm::scale(floorTransform, glm::vec3(200.0f));
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, -200.0f, 0.0f));
        floorTransform = trans * floorTransform;
        floorTransform = glm::rotate(floorTransform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        FloorShader.setMat4("model", floorTransform);
        // send the light point
        set_point_light(FloorShader);
        // draw the floor
        floor.Draw(FloorShader);

        // floor shader
        CastleShader.use();
        // set the MVP transformation
        CastleShader.setMat4("view", view);
        CastleShader.setMat4("projection", projection);
        glm::mat4 castleTransform = glm::mat4(1.0f);
        castleTransform = glm::scale(castleTransform, glm::vec3(7.0f));
        trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        //castleTransform = trans * castleTransform;
        castleTransform = glm::rotate(castleTransform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        CastleShader.setMat4("model", castleTransform);
        // send the light point
        set_point_light(CastleShader);
        // draw the floor
        castle.Draw(CastleShader);
        
        // draw skybox as last
        skyboxShader.use();
        skyboxShader.setInt("skybox", 0);
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skybox.render(view, projection, cubemapTexture, skyboxShader);
        //////////////////////////////////////////////////////////////////////////////////////////

        // modify to bloom
        bloom.BloomDraw(BloomShader, ResultShader);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    // ESC 退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // fire the work for num
    for (int i = 0; i < TYPE_NUM; i++)
    {
        if (glfwGetKey(window, GLFW_KEY_1 + i) == GLFW_PRESS)
        {
            // 只有按键按下瞬间会发射烟花(松开->按下)
            if (!PRESS[i] && firework_list.size() < MAX_FIREWORK_NUMBER)
            {
                fireworktype type = fireworktype(i);
                Firework newfirework(type);
                firework_list.push_back(newfirework);
                sound::fire();
            }
            PRESS[i] = true;
        }
        if (glfwGetKey(window, GLFW_KEY_1 + i) == GLFW_RELEASE)
            PRESS[i] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        fireworktype type;
        // 只有按键按下瞬间会发射烟花(松开->按下)
        if (!PRESS_MY[7] && firework_list.size() < MAX_FIREWORK_NUMBER)
        {
            type = fireworktype('s'-'a'+TYPE_NUM);
            Firework newfirework1(type);
            firework_list.push_back(newfirework1);
            sound::fire();
            type = fireworktype('y'-'a'+TYPE_NUM);
            Firework newfirework2(type);
            firework_list.push_back(newfirework2);
            sound::fire();
            type = fireworktype('s'-'a'+TYPE_NUM);
            Firework newfirework3(type);
            firework_list.push_back(newfirework3);
            sound::fire();
            type = fireworktype('u'-'a'+TYPE_NUM);
            Firework newfirework4(type);
            firework_list.push_back(newfirework4);
            sound::fire();
        }
        PRESS_MY[7] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_RELEASE)
        PRESS_MY[7] = false;
    // fire the work for char
    for (int i = 0; i < CHAR_TYPE_NUM; i++)
    {
        if (glfwGetKey(window, GLFW_KEY_A + i) == GLFW_PRESS)
        {
            // 只有按键按下瞬间会发射烟花(松开->按下)
            if (!PRESS_CHAR[i] && firework_list.size() < MAX_FIREWORK_NUMBER)
            {
                fireworktype type = fireworktype(i+TYPE_NUM);
                Firework newfirework(type);
                firework_list.push_back(newfirework);
                sound::fire();
            }
            PRESS_CHAR[i] = true;
        }
        if (glfwGetKey(window, GLFW_KEY_A + i) == GLFW_RELEASE)
            PRESS_CHAR[i] = false;
    }
    // 上 下 调整烟花速度
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        time_scale = (time_scale + 0.01f) > 4.0f ? 4.0f : (time_scale + 0.01f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        time_scale = (time_scale - 0.01f) < 2.0f ? 2.0f : (time_scale - 0.01f);
    // mouse enable
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && MOUSEPRESS == false)
    {
        if (MOUSEABLE)
        {
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            MOUSEABLE = false;
        }
        else
        {
            firstMouse = true;
            glfwSetCursorPosCallback(window, NULL);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            MOUSEABLE = true;
        }
        MOUSEPRESS = true;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        MOUSEPRESS = false;
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
void set_point_light(Shader& blinnphongshader)
{
    int count = 0;
    string struct_string = "light_list[";
    string color_string = "].Color";
    string pos_string = "].Position";
    string intensity_string = "].intensity";
    for (int i = 0; i < firework_list.size(); i++)
    {
        if (firework_list[i].isExploded() && firework_list[i].getLightLife() > 0)
        {
            Firework* ptr = &firework_list[i];
            blinnphongshader.setVec3(struct_string + to_string(count) + color_string, ptr->getLightColor());
            blinnphongshader.setVec3(struct_string + to_string(count) + pos_string, ptr->getPosition());
            blinnphongshader.setFloat(struct_string + to_string(count) + intensity_string, ptr->getLightIntensity());
            count++;
        }
    }
    blinnphongshader.setInt("num_lights", count);
}
