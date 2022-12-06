#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

//void framebuffersize(GLFWwindow* window, int width, int height);
//void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
//void mouse(GLFWwindow* window, int button, int action, int mods);
//void cursor(GLFWwindow* window, double x, double y);
//void scroll(GLFWwindow* window, double x, double y);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 用于表示一个烟花粒子的结构体
struct Particle {
	double x, y, z;   // 粒子的位置
	double vx, vy, vz; // 粒子的速度
	double r, g, b;   // 粒子的颜色
};

// 存所有烟花粒子的数组
vector<Particle> particles;

// 初始化窗口大小
const int WIDTH = 800;
const int HEIGHT = 600;

// 每次调用display函数时，都会更新所有粒子的位置
void display(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 更新每个粒子的位置
	for (auto& p : particles) {
		p.x += p.vx;
		p.y += p.vy;
		p.z += p.vz;
	}

	// 绘制每个粒子
	for (const auto& p : particles) {
		/*glColor3f(p.r, p.g, p.b);
		glBegin(GL_POINTS);
		glVertex3f(p.x, p.y, p.z);
		glEnd();*/
		glClearColor(p.r, p.g, p.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
	}

	glfwSwapBuffers(window); // 刷新窗口
}

int main(int argc, char** argv) {
	// 初始化窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

	// 初始化烟花粒子
	for (int i = 0; i < 1000; ++i) {
		Particle p;
		p.x = WIDTH / 2;
		p.y = HEIGHT / 2;
		p.z = 0;
		p.vx = 2 * (double)rand() / RAND_MAX - 1;
		p.vy = 2 * (double)rand() / RAND_MAX - 1;
		p.vz = 2 * (double)rand() / RAND_MAX - 1;
		p.r = (double)rand() / RAND_MAX;
		p.g = (double)rand() / RAND_MAX;
		p.b = (double)rand() / RAND_MAX;
		particles.push_back(p);
	}

	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetKeyCallback(window, keyboard);
	//glfwSetMouseButtonCallback(window, mouse);
	//glfwSetCursorPosCallback(window, motion);
	//glfwSetScrollCallback(window, scroll);
	//glfwMakeContextCurrent(window);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		display(window);
		glfwSwapBuffers(window);
		glfwPollEvents();

		// input
		// -----
		//processInput(window);

		//// render
		//// ------
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		//// -------------------------------------------------------------------------------
		//glfwSwapBuffers(window);
		//glfwPollEvents();
	}
	glfwTerminate();

	// 设置绘图函数，每隔一段时间自动调用
	//glutDisplayFunc(display);
	//glutIdleFunc(display);

	//glutMainLoop(); // 进入主循环

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
