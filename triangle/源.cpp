#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window)//自定义getkey 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//如果ESC被按下，如果他没用被按下，glfwGetKey会返回GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);//把这个窗口的shouldclose指为true
}
float vertices[] = {//三个顶点
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};


const char* vertexShaderSource =
"#version 330 core\n"//用字符串去写,顶点着色器GLSL源代码
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";


const char* fragmentShaderSource = "#version 330 core\n"//片段着色器GLSL源代码
"out vec4 FragColor; \n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\n";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//附版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//开启一个窗口，长宽和名字
	if (window == NULL)//如果打开失败
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//中止窗口
		return -1;
	}
	glfwMakeContextCurrent(window);//这个窗口为当前上下文（句柄）

	//初始化GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("glew init failed.");
		glfwTerminate();//中止窗口
		return -1;
	}

	glViewport(0, 0, 800, 600);//定义视口大小，和上面开的窗口一样即为全部窗口都填满

	unsigned int VAO;//声明VAO，顶点数组对象
	glGenVertexArrays(1, &VAO);//我要造一个【1】个VAO变量，你给我把它的id塞给我定义的无符号整型变量VAO里面，如果不是一个而是多个，要传入一个对应长度的数组名。
	glBindVertexArray(VAO);

	unsigned int VBO;//声明顶点缓冲对象
	glGenBuffers(1, &VBO);//返回一个缓冲对象ID给VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//注意，要告诉它这是什么样的缓冲区，这里是数组缓冲。

	unsigned int vertexShader;//声明顶点着色器对象
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//我要创造一个shader，我告诉你它的类型，你返回它的ID给我
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//用我给的那个字符串里的代码去做一个shader!
	glCompileShader(vertexShader);//去编译它吧。
	/*编译测试程序略*/


	unsigned int fragmentShader;//同上声明片元着色器对象
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/*编译测试程序略*/

	unsigned int shaderProgram;//声明着色器程序，要把刚刚声明的着色器全部贴进来，因为OpenGL只认这个着色器程序。
	shaderProgram = glCreateProgram();//创建并拿到ID
	glAttachShader(shaderProgram, vertexShader);//贴进来
	glAttachShader(shaderProgram, fragmentShader);//贴进来
	glLinkProgram(shaderProgram);//连接！
	/*连接测试程序略*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGL，这个顶点数据要怎么用
	/*从上到下分别是：
	1。要配置哪些？从0开始，这和顶点着色器里面的location一致
	2. 几个顶点一组？三个
	3.顶点类型？
	4.要标准化到0-1（或者-1到1）吗？不需要
	5.内存间隔？每一组数据内存间隔是多少，如果顶点整齐排列，不需要指定
	6.开头偏移。非要转成void的指针
	*/
	glEnableVertexAttribArray(0);//启用顶点属性

	glDeleteShader(vertexShader);//我已经把他们粘进去了，我不再需要这些了，类似已经拷贝进去了一份的感觉
	glDeleteShader(fragmentShader);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把顶点数组压入缓冲区

	while (!glfwWindowShouldClose(window))//直到窗口需要被关闭之时为止
	{
		/*为什么要先查input，最后在pollEvents,这是因为，在这一帧的最后，我们接受事件，再下一帧的开始，采纳这个事件，这样最快*/
		processInput(window);//调用上面自定义方法，监听esc有无被按下

		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空缓冲所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);//用此颜色清空颜色缓冲区
		/*glClearColor函数是一个状态设置函数，而glClear函数则是一个状态使用的函数，它使用了当前的状态来获取应该清除为的颜色。*/
			/*开始画三角形*/
		glBindVertexArray(VAO);//当前绘制的模型
		glUseProgram(shaderProgram);//用哪个着色器程序画
		glDrawArrays(GL_TRIANGLES, 0, 3);//画什么？这里画三角形，从0索引的顶点起始处，绘制三个顶点

		glfwSwapBuffers(window);//设置双缓冲。
		glfwPollEvents();//检测事件（鼠标输入等）
	}
	glfwTerminate();
	return 0;


}
