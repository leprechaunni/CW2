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


using namespace std;

//задание координат вершин и цвета

GLfloat octahedron[] = {
	//vertices            colors
	-0.5f, 0.f, 0.f,
	 0.f, 0.f, 0.5f,
	 0.f, 0.5f, 0.f,

	 0.f, 0.f, 0.5f,
	 0.5f, 0.f, 0.f,
	 0.f, 0.5f, 0.f,

	-0.5f, 0.f, 0.f,
	 0.f, -0.5f, 0.f,
	 0.f, 0.f, 0.5f,

	 0.f, 0.f, 0.5f,
	 0.f, -0.5f, 0.f,
	 0.5f, 0.f, 0.f,

	-0.5f, 0.f, 0.f,
	 0.f, 0.f, -0.5f,
	 0.f, 0.5f, 0.f,

	 0.f, 0.5f, 0.f,
	 0.f, 0.f, -0.5f,
	 0.5f, 0.f, 0.f,

	-0.5f, 0.f, 0.f,
	 0.f, -0.5f, 0.f,
	 0.f, 0.f, -0.5f,

	 0.f, 0.f, -0.5f,
	 0.f, -0.5f, 0.f,
	 0.5f, 0.f, 0.f
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
float a = 1.5; //длина ребра
GLfloat tetrahedron[] = {
	//vertices            colors
	 0.f,  0.f,  a*sqrt(6)/4,  0.f, 1.f, 0.f,
	 a/sqrt(3), 0.f, -a*sqrt(6)/12,  0.f, 1.f, 0.f,
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  0.f, 1.f, 0.f,

	 0, 0, a*sqrt(6)/4,  0.f, 0.f, 1.f, //(0)
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  0.f, 0.f, 1.f,
	 a/sqrt(3), 0, -a*sqrt(6)/12,  0.f, 0.f, 1.f, //(1)

	 0, 0, a*sqrt(6)/4,  0.f, 1.f, 1.f,// (0)
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  0.f, 1.f, 1.f, //(2)
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  0.f, 1.f, 1.f, //(3)

	 a/sqrt(3), 0, -a*sqrt(6)/12,  1.f, 0.f, 1.f,// (1)
	-a/sqrt(12), -a/2, -a*sqrt(6)/12,  1.f, 0.f, 1.f,// (3)
	-a/sqrt(12), a/2, -a*sqrt(6)/12,  1.f, 0.f, 1.f //(2)
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

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};


//объявление переменных для работы с выбором фигуры, изменением ее цвета, размера и формы
float m_rotate = 0;
float m_left_right = 0;
float m_up_down = 0;
float m_sizex = 1;
float m_sizey = 1;
float m_size = 1;
int m_change = 0;
int m_color;

//функция обратного вызова
//вызывается при каждом изменении размера окна, чтобы скорректировать размер области окна просмотра
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//убеждаемся, что окно просмотра соответствует новым размерам окна
	glViewport(0, 0, width, height);
}

//функция пользовательского ввода с клавиатуры
/*void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && m_left_right >= -1.f)
		m_left_right -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && m_left_right <= 1.f)
		m_left_right += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && m_up_down <= 1.f)
		m_up_down += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && m_up_down >= -1.f)
		m_up_down -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		m_rotate += glm::radians(0.1f);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		m_rotate -= glm::radians(0.1f);

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		m_sizex += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && m_sizex > 0)
		m_sizex -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		m_sizey += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS && m_sizey > 0)
		m_sizey -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		m_size += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && m_size > 0)
		m_size -= 0.001f;
}*/

//функция определения координат курсора на экране
/*static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}
//объявление переменных, в которые будут записаны х и у координаты положения курсора
double xpos, ypos;*/

//функция пользовательского ввода с помощью мыши
/*void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (xpos < 80 && xpos > 40 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 1;
	if (xpos < 160 && xpos > 120 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 2;
	if (xpos < 240 && xpos > 200 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 3;
	if (xpos < 320 && xpos > 280 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 4;
	if (xpos < 400 && xpos > 360 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 5;
	if (xpos < 480 && xpos > 440 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 6;
	if (xpos < 560 && xpos > 520 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 7;
	if (xpos < 640 && xpos > 600 && ypos > 30 && ypos < 60 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_color = 8;

	if (xpos < 70 && xpos > 49 && ypos > 95 && ypos < 112 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 1;
	if (xpos < 100 && xpos > 20 && ypos > 140 && ypos < 155 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 2;
	if (xpos < 88 && xpos > 32 && ypos > 180 && ypos < 225 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 3;
	if (xpos < 88 && xpos > 32 && ypos > 237 && ypos < 285 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 4;
	if (xpos < 100 && xpos > 20 && ypos > 300 && ypos < 360 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 5;
	if (xpos < 100 && xpos > 20 && ypos > 375 && ypos < 440 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 6;
	if (xpos < 82 && xpos > 35 && ypos > 458 && ypos < 543 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_change = 7;
}*/



/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}*/


int main(int argc, char** argv)
{


	//инициализация библиотеки GLFW
	glfwInit();
	//установка минимальных необходимых параметров OpenGL	
	//указали, что будем исользовать версию 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //minor
	//указываем, что хотим явно использовать core-profile
	//чтобы не подгружать лишние для нас OpenGL-функции, 
	//предназначенные для поддержания обратной совместимости приложений
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//создаем объект window, представляющий окно приложения
	GLFWwindow* window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "My Title", glfwGetPrimaryMonitor(), NULL);
	//to create a full screen window
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

		return -1;
	}
	//сообщаем GLFW сделать контекст нашего окна основным контекстом в текущем потоке
	glfwMakeContextCurrent(window);

	//сообщаем GLFW, что хотим вызывать функцию framebuffer_size_callback
	//каждый раз при изменении размеров окна
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//инициализация GLAD, чтобы потом пользоваться функциями OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	//в качестве параметра передаем GLAD-функцию, 
	//которая загружает адреса указателей на OpenGL-функции
	//функция glfwGetProcAddress() 
	//самостоятельно может определить нужные для работы функции


	Manager manager(argv[0]);

	//загружаем шейдеры из текстового файла в программу
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
	//auto tex = manager.loadTexture("BackgroundTexture", "resource/background.jpg");

	{
		//объявление вершинного буфера и вершинного массива
		GLuint VBO[2], VAO[2], EBO[1];
		glGenVertexArrays(2, VAO);
		glGenBuffers(2, VBO);
		glGenBuffers(1, EBO);//create

		//menu

		//triangle
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(octahedron), octahedron, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

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



		//отменяем привязку вершинного буфера и вершинного массива
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		//цикл рендеринга
		while (!glfwWindowShouldClose(window))
		{
			//пользовательский ввод
			//processInput(window);
			//glfwSetKeyCallback(window, key_callback);
			//glfwSetMouseButtonCallback(window, mouse_button_callback);
			//glfwGetCursorPos(window, &xpos, &ypos);

			//выполнение рендеринга
			//задаем цвет окна
			glClearColor(0.9f, 0.9f, 0.98f, 1.0f);
			glEnable(GL_DEPTH_TEST);//глубинное тестирование
			//очистка буфера цвета и глубины
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glClear() использует текущие настройки цвета
			//установленные при помощи функции glClearColor()

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //karkas regim
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			//glm::mat4 projectionMatrix = glm::ortho(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f);//clip space
			//передаем в вертексный шейдер и перемножаем с вектором координат и подаем на выход шейдера

			pCyanShaderProgram_an->use();

			glm::mat4 modelMatrix = glm::mat4(1.0f); // сначала инициализируем единичную матрицу
			glm::mat4 viewMatrix = glm::mat4(1.0f);
			glm::mat4 projectionMatrix = glm::mat4(1.0f);
			//modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.f));
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.f);
			//поле зрения
			//соотношение сторон
			//ближняя и дальняя плоскости (все, что между ними - визуализируется)



			
			pPurpleShaderProgram_an->setMatrix4("modelMat", modelMatrix);
			pPurpleShaderProgram_an->setMatrix4("viewMat", viewMatrix);
			/*unsigned int modelLoc = glGetUniformLocation(pPurpleShaderProgram_an->m_ID, "modelMatrix");
			unsigned int viewLoc = glGetUniformLocation(pPurpleShaderProgram_an->m_ID, "viewMatrix");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);*/
			
			pPurpleShaderProgram_an->setMatrix4("projectionMat", projectionMatrix);
			
			
			//группа элементов
			/*glm::mat4 group = glm::mat4(1.f);
			group = glm::translate(group, glm::vec3(m_left_right, m_up_down, 0.f));
			group = glm::rotate(group, m_rotate, glm::vec3(0.f, 0.f, 1.f));
			group = glm::scale(group, glm::vec3(m_sizex, m_sizey, 1.f));
			group = glm::scale(group, glm::vec3(m_size, m_size, 1.f));*/


			
			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 24);
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

			
			//выбор цвета
			/*if (m_color == 1) pRedShaderProgram_an->use();
			if (m_color == 2) pOrangeShaderProgram_an->use();
			if (m_color == 3) pYellowShaderProgram_an->use();
			if (m_color == 4) pGreenShaderProgram_an->use();
			if (m_color == 5) pCyanShaderProgram_an->use();
			if (m_color == 6) pBlueShaderProgram_an->use();
			if (m_color == 7) pPurpleShaderProgram_an->use();
			*/
			

			//освобождаем вершинный массив
			glBindVertexArray(0);

			//ообмен содержимым front- и back- буферов
			//отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		//освобождаем ресурсы, как только они выполнили свою функцию
		glDeleteBuffers(1, VAO);
		glDeleteBuffers(1, VBO);
	}
	//завершение, освобождение всех ранее задействованных GLFW-ресурсов
	glfwTerminate();
	system("PAUSE");
	return 0;

}