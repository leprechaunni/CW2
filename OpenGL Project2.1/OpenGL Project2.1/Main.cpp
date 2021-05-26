#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm/vec2.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "ShaderProgram.h"
#include "Manager.h"
#include "stb_image.h"
#include "Texture2D.h"
#include "Camera.h"


using namespace std;

//������� ��������� ������ � �����

GLfloat octahedron[] = {
	//vertices            colors
	-0.5f, 0.f,  0.f,	1.f, 0.f, 0.f, //1 ����
	 0.f,  0.f,  0.5f,  1.f, 0.f, 0.f,
	 0.f,  0.5f, 0.f,   1.f, 0.f, 0.f,

	 0.f,  0.f,  0.5f,	0.f, 1.f, 0.f, //2 ����
	 0.5f, 0.f,  0.f,	0.f, 1.f, 0.f,
	 0.f,  0.5f, 0.f,	0.f, 1.f, 0.f,

	-0.5f, 0.f,  0.f,	0.f, 1.f, 1.f, //1 ���
	 0.f, -0.5f, 0.f,	0.f, 1.f, 1.f,
	 0.f,  0.f,  0.5f,	0.f, 1.f, 1.f,

	 0.f,  0.f,  0.5f,	1.f, 0.f, 0.f, //2 ���
	 0.f, -0.5f, 0.f,	1.f, 0.f, 0.f,
	 0.5f, 0.f,  0.f,	1.f, 0.f, 0.f,

	-0.5f, 0.f,  0.f,	0.f, 0.f, 1.f, //3 ����
	 0.f,  0.f, -0.5f,	0.f, 0.f, 1.f,
	 0.f,  0.5f, 0.f,	0.f, 0.f, 1.f,

	 0.f,  0.5f, 0.f,	0.f, 1.f, 1.f, //4 ����
	 0.f,  0.f, -0.5f,	0.f, 1.f, 1.f,
	 0.5f, 0.f,  0.f,	0.f, 1.f, 1.f,

	-0.5f, 0.f,  0.f,	0.f, 1.f, 0.f, //3 ���
	 0.f, -0.5f, 0.f,	0.f, 1.f, 0.f,
	 0.f,  0.f, -0.5f,	0.f, 1.f, 0.f,

	 0.f,  0.f, -0.5f,	0.f, 0.f, 1.f, //4 ���
	 0.f, -0.5f, 0.f,	0.f, 0.f, 1.f,
	 0.5f, 0.f,  0.f,	0.f, 0.f, 1.f
};

GLfloat pyramid[] = {
	//vertices            colors
	 0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,
	 0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,
	 0.f,  0.5f,  0.f,  0.f, 1.f, 0.f,

	 0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,
	 0.f,  0.5f,  0.f,  0.f, 0.f, 1.f,

	-0.5f, -0.5f,  0.5f,  0.f, 1.f, 1.f,
	-0.5f, -0.5f, -0.5f,  0.f, 1.f, 1.f,
	 0.f,  0.5f,  0.f,  0.f, 1.f, 1.f,

	-0.5f, -0.5f, -0.5f,  1.f, 0.f, 1.f,
	 0.5f, -0.5f, -0.5f,  1.f, 0.f, 1.f,
	 0.f,  0.5f,  0.f,  1.f, 0.f, 1.f,

	 0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	-0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	-0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,
	 0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	-0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,
	 0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f

};
float a = 1.5; //����� �����
GLfloat tetrahedron[] = {
	//vertices            colors
	 0.f,  0.f,  a*sqrt(6)/4,  0.f, 1.f, 0.f,
	 a/sqrt(3), 0.f, -a*sqrt(6)/12,  0.f, 1.f, 0.f,
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  0.f, 1.f, 0.f,

	 0, 0, a*sqrt(6)/4,  0.f, 0.f, 1.f, 
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  0.f, 0.f, 1.f,
	 a/sqrt(3), 0, -a*sqrt(6)/12,  0.f, 0.f, 1.f, 

	 0, 0, a*sqrt(6)/4,  0.f, 1.f, 1.f,
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  0.f, 1.f, 1.f, 
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  0.f, 1.f, 1.f, 

	 a/sqrt(3), 0, -a*sqrt(6)/12,  1.f, 0.f, 1.f,
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  1.f, 0.f, 1.f,
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  1.f, 0.f, 1.f 
};
/*unsigned int indices1[] = {
	0, 1, 2, //1
	0, 3, 1,
	0, 2, 3,
	1, 3, 2
};*/

GLfloat cube[] = {
	//vertices            colors
	-0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,
	 0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,
	 0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f,
	 0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f,
	-0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f,
	-0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,

	-0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,
	 0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,
	 0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,
	 0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,
	-0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,
	-0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,

	-0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,
	-0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,
	-0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,
	-0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,

	 0.5f,  0.5f,  0.5f,  0.f, 1.f, 1.f,
	 0.5f,  0.5f, -0.5f,  0.f, 1.f, 1.f,
	 0.5f, -0.5f, -0.5f,  0.f, 1.f, 1.f,
	 0.5f, -0.5f, -0.5f,  0.f, 1.f, 1.f,
	 0.5f, -0.5f,  0.5f,  0.f, 1.f, 1.f,
	 0.5f,  0.5f,  0.5f,  0.f, 1.f, 1.f,

	-0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,
	 0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,
	 0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	 0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	-0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,
	-0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,

	-0.5f,  0.5f, -0.5f,  1.f, 0.f, 1.f,
	 0.5f,  0.5f, -0.5f,  1.f, 0.f, 1.f,
	 0.5f,  0.5f,  0.5f,  1.f, 0.f, 1.f,
	 0.5f,  0.5f,  0.5f,  1.f, 0.f, 1.f,
	-0.5f,  0.5f,  0.5f,  1.f, 0.f, 1.f,
	-0.5f,  0.5f, -0.5f,  1.f, 0.f, 1.f
};

GLfloat cube_t[] = {
	//vertices					//textures
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};




//������� ��������� ������
//���������� ��� ������ ��������� ������� ����, ����� ��������������� ������ ������� ���� ���������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//����������, ��� ���� ��������� ������������� ����� �������� ����
	glViewport(0, 0, width, height);
}

//������� ����������������� ����� � ����������
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// ������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;

bool firstMouse = true;

// ��������
float deltaTime = 0.0f;	// ����� ����� ������� ������ � ��������� ������
float lastFrame = 0.0f;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: ������ ���, ����� ������������ ����, ���������� ������ callback-�������
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // �����������, ��� ��� y-���������� ���� ����� �����

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: ������ ���, ����� �������������� �������� ����, ���������� ������ callback-�������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true,
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}*/



int main(int argc, char** argv)
{


	//������������� ���������� GLFW
	glfwInit();
	//��������� ����������� ����������� ���������� OpenGL	
	//�������, ��� ����� ����������� ������ 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor
	//���������, ��� ����� ���� ������������ core-profile
	//����� �� ���������� ������ ��� ��� OpenGL-�������, 
	//��������������� ��� ����������� �������� ������������� ����������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//������� ������ window, �������������� ���� ����������
	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		return -1;
	}
	//�������� GLFW ������� �������� ������ ���� �������� ���������� � ������� ������
	glfwMakeContextCurrent(window);

	//�������� GLFW, ��� ����� �������� ������� framebuffer_size_callback
	//������ ��� ��� ��������� �������� ����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// �������� GLFW, ����� �� �������� ��� ������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//������������� GLAD, ����� ����� ������������ ��������� OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	//� �������� ��������� �������� GLAD-�������, 
	//������� ��������� ������ ���������� �� OpenGL-�������
	//������� glfwGetProcAddress() 
	//�������������� ����� ���������� ������ ��� ������ �������


	Manager manager(argv[0]);

	//��������� ������� �� ���������� ����� � ���������
	auto pRedShaderProgram_an = manager.loadShaders("pRed_an", "resource/vertex_animation.txt", "resource/fragment_red.txt");
	if (!pRedShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pRed_an" << endl;
		return -1;
	}


	auto pOrangeShaderProgram_an = manager.loadShaders("pOrange_an", "resource/vertex_animation.txt", "resource/fragment_orange.txt");
	if (!pOrangeShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pOrange_an" << endl;
		return -1;
	}


	auto pYellowShaderProgram_an = manager.loadShaders("pYellow_an", "resource/vertex_animation.txt", "resource/fragment_yellow.txt");
	if (!pYellowShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pYellow_an" << endl;
		return -1;
	}


	auto pGreenShaderProgram_an = manager.loadShaders("pGreen_an", "resource/vertex_animation.txt", "resource/fragment_green.txt");
	if (!pGreenShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pGreen_an" << endl;
		return -1;
	}


	auto pCyanShaderProgram_an = manager.loadShaders("pCyan_an", "resource/vertex_animation.txt", "resource/fragment_cyan.txt");
	if (!pCyanShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pCyan_an" << endl;
		return -1;
	}


	auto pBlueShaderProgram_an = manager.loadShaders("pBlue_an", "resource/vertex_animation.txt", "resource/fragment_blue.txt");
	if (!pBlueShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pBlue_an" << endl;
		return -1;
	}


	auto pPurpleShaderProgram_an = manager.loadShaders("pPurple_an", "resource/vertex_animation.txt", "resource/fragment_purple.txt");
	if (!pPurpleShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pPurple_an" << endl;
		return -1;
	}


	auto pColShaderProgram_an = manager.loadShaders("pCol_an", "resource/vertex_animation.txt", "resource/fragment_pCol.txt");
	if (!pColShaderProgram_an)
	{
		cerr << "cant create shader program: " << "pCol_an" << endl;
		return -1;
	}



	auto pTextureShaderProgram_an = manager.loadShaders("texture_an", "resource/vertex_animation.txt", "resource/fragment_texture.txt");
	if (!pTextureShaderProgram_an)
	{
		cerr << "cant create shader program: " << "texture_an" << endl;
		return -1;
	}
	auto tex = manager.loadTexture("BackgroundTexture", "image/img.jpg");

	{
		//���������� ���������� ������ � ���������� �������
		GLuint VBO[2], VAO[2], EBO[1];
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO);
		glGenBuffers(1, EBO);//create

		//menu

		//triangle
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_t), cube_t, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//cube
		/*glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);*/


		//�������� �������� ���������� ������ � ���������� �������
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		//���� ����������
		while (!glfwWindowShouldClose(window))
		{
			// ���������� ����� ������ �� �������� ��� ������� �����
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//���������������� ����
			processInput(window);

			//���������� ����������
			//������ ���� ����
			glClearColor(0.9f, 0.9f, 0.98f, 1.0f);
			glEnable(GL_DEPTH_TEST);//��������� ������������
			//������� ������ ����� � �������
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glClear() ���������� ������� ��������� �����
			//������������� ��� ������ ������� glClearColor()

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //karkas regim
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			//glm::mat4 projectionMatrix = glm::ortho(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f);//clip space
			//�������� � ���������� ������ � ����������� � �������� ��������� � ������ �� ����� �������

			pTextureShaderProgram_an->use();
			pTextureShaderProgram_an->setInt("tex", 0);
			tex->bind();

			//pColShaderProgram_an->use();

			// �������� ������� ������� �������� (��������� ������������ ������� ����� ��������, �� ��� ������������� ������ ��� ��� ������� �����)
			glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)800/(float)600, 0.1f, 100.0f);
			pPurpleShaderProgram_an->setMatrix4("projectionMat", projectionMatrix);

			glm::mat4 modelMatrix = glm::mat4(1.0f); // ������� �������������� ��������� �������
			
			//������� �������������� ������/����
			glm::mat4 viewMatrix = camera.GetViewMatrix();
			pPurpleShaderProgram_an->setMatrix4("viewMat", viewMatrix);

			//glm::mat4 projectionMatrix = glm::mat4(1.0f);
			//modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			//viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.f));
			//projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.f);
			//���� ������
			//����������� ������
			//������� � ������� ��������� (���, ��� ����� ���� - ���������������)



			
			pPurpleShaderProgram_an->setMatrix4("modelMat", modelMatrix);
			
			/*unsigned int modelLoc = glGetUniformLocation(pPurpleShaderProgram_an->m_ID, "modelMatrix");
			unsigned int viewLoc = glGetUniformLocation(pPurpleShaderProgram_an->m_ID, "viewMatrix");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);*/
			
			
			
			
			//������ ���������
			/*glm::mat4 group = glm::mat4(1.f);
			group = glm::translate(group, glm::vec3(m_left_right, m_up_down, 0.f));
			group = glm::rotate(group, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			group = glm::scale(group, glm::vec3(m_sizex, m_sizey, 1.f));
			group = glm::scale(group, glm::vec3(m_size, m_size, 1.f));*/


			
			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glBindVertexArray(VAO[1]);
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			
			/*if (m_change == 7)
			{
				glBindVertexArray(VAO[19]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[20]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[21]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[22]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(VAO[23]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_LINES, 0, 2);
				glBindVertexArray(VAO[24]);
				pPurpleShaderProgram_an->setMatrix4("modelMat", group);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			}*/

			
			//����� �����
			/*if (m_color == 1) pRedShaderProgram_an->use();
			if (m_color == 2) pOrangeShaderProgram_an->use();
			if (m_color == 3) pYellowShaderProgram_an->use();
			if (m_color == 4) pGreenShaderProgram_an->use();
			if (m_color == 5) pCyanShaderProgram_an->use();
			if (m_color == 6) pBlueShaderProgram_an->use();
			if (m_color == 7) pPurpleShaderProgram_an->use();
			*/
			

			//����������� ��������� ������
			glBindVertexArray(0);

			//������ ���������� front- � back- �������
			//������������ ������� �����/������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		//����������� �������, ��� ������ ��� ��������� ���� �������
		glDeleteBuffers(1, VAO);
		glDeleteBuffers(1, VBO);
	}
	//����������, ������������ ���� ����� ��������������� GLFW-��������
	glfwTerminate();
	system("PAUSE");
	return 0;

}