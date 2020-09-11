#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window)//�Զ���getkey 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//���ESC�����£������û�ñ����£�glfwGetKey�᷵��GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);//��������ڵ�shouldcloseָΪtrue
}
float vertices[] = {//��������
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};


const char* vertexShaderSource =
"#version 330 core\n"//���ַ���ȥд,������ɫ��GLSLԴ����
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";


const char* fragmentShaderSource = "#version 330 core\n"//Ƭ����ɫ��GLSLԴ����
"out vec4 FragColor; \n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\n";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ú���ģʽ
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//����һ�����ڣ�����������
	if (window == NULL)//�����ʧ��
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//��ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window);//�������Ϊ��ǰ�����ģ������

	//��ʼ��GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("glew init failed.");
		glfwTerminate();//��ֹ����
		return -1;
	}

	glViewport(0, 0, 800, 600);//�����ӿڴ�С�������濪�Ĵ���һ����Ϊȫ�����ڶ�����

	unsigned int VAO;//����VAO�������������
	glGenVertexArrays(1, &VAO);//��Ҫ��һ����1����VAO����������Ұ�����id�����Ҷ�����޷������ͱ���VAO���棬�������һ�����Ƕ����Ҫ����һ����Ӧ���ȵ���������
	glBindVertexArray(VAO);

	unsigned int VBO;//�������㻺�����
	glGenBuffers(1, &VBO);//����һ���������ID��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//ע�⣬Ҫ����������ʲô���Ļ����������������黺�塣

	unsigned int vertexShader;//����������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//��Ҫ����һ��shader���Ҹ������������ͣ��㷵������ID����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//���Ҹ����Ǹ��ַ�����Ĵ���ȥ��һ��shader!
	glCompileShader(vertexShader);//ȥ�������ɡ�
	/*������Գ�����*/


	unsigned int fragmentShader;//ͬ������ƬԪ��ɫ������
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/*������Գ�����*/

	unsigned int shaderProgram;//������ɫ������Ҫ�Ѹո���������ɫ��ȫ������������ΪOpenGLֻ�������ɫ������
	shaderProgram = glCreateProgram();//�������õ�ID
	glAttachShader(shaderProgram, vertexShader);//������
	glAttachShader(shaderProgram, fragmentShader);//������
	glLinkProgram(shaderProgram);//���ӣ�
	/*���Ӳ��Գ�����*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//����OpenGL�������������Ҫ��ô��
	/*���ϵ��·ֱ��ǣ�
	1��Ҫ������Щ����0��ʼ����Ͷ�����ɫ�������locationһ��
	2. ��������һ�飿����
	3.�������ͣ�
	4.Ҫ��׼����0-1������-1��1���𣿲���Ҫ
	5.�ڴ�����ÿһ�������ڴ����Ƕ��٣���������������У�����Ҫָ��
	6.��ͷƫ�ơ���Ҫת��void��ָ��
	*/
	glEnableVertexAttribArray(0);//���ö�������

	glDeleteShader(vertexShader);//���Ѿ�������ճ��ȥ�ˣ��Ҳ�����Ҫ��Щ�ˣ������Ѿ�������ȥ��һ�ݵĸо�
	glDeleteShader(fragmentShader);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�Ѷ�������ѹ�뻺����

	while (!glfwWindowShouldClose(window))//ֱ��������Ҫ���ر�֮ʱΪֹ
	{
		/*ΪʲôҪ�Ȳ�input�������pollEvents,������Ϊ������һ֡��������ǽ����¼�������һ֡�Ŀ�ʼ����������¼����������*/
		processInput(window);//���������Զ��巽��������esc���ޱ�����

		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//������ջ������õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�ô���ɫ�����ɫ������
		/*glClearColor������һ��״̬���ú�������glClear��������һ��״̬ʹ�õĺ�������ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ��*/
			/*��ʼ��������*/
		glBindVertexArray(VAO);//��ǰ���Ƶ�ģ��
		glUseProgram(shaderProgram);//���ĸ���ɫ������
		glDrawArrays(GL_TRIANGLES, 0, 3);//��ʲô�����ﻭ�����Σ���0�����Ķ�����ʼ����������������

		glfwSwapBuffers(window);//����˫���塣
		glfwPollEvents();//����¼����������ȣ�
	}
	glfwTerminate();
	return 0;


}
