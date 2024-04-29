#include <glad/glad.h>
#include <GLFW/glfw3.h>

//初始化glfw
void init_glfw()
{
    //初始化glfw，使用核心模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//使用OpenGL3.3版本
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
}

//回调函数用来在用户改变窗口的大小时刷新视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//处理escape输入
void processInput_escape(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}