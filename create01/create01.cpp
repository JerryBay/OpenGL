// 引入GLEW库 定义静态链接
#define GLEW_STATIC
#include <GL/glew.h>
// 引入GLFW库
#include <GLFW/glfw3.h>
#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char* fragmentShaderSource =
"#version 330 core                             \n   "
"out vec4 FragColor;                           \n   "
"void main()                                   \n   "
"{                                             \n   "
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n   "
"}                                             \0   ";

// 定义程序常量
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window,true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600,"Demo of createContext", NULL, NULL);
    if (!window)
    {
        std::cout << "Error::GLFW could not create window!" << std::endl;
        glfwTerminate();
		return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (glewInit() != GLEW_OK) {
        printf("glew init failed.");
        glfwTerminate();//��ֹ����
        return -1;
    }
    glViewport(0, 0, 800, 600);

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.5, 0, 0.5,1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();                        
    system("pause");                        
    return 0;                               
}                                           
