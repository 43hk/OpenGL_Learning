#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "my.h"
#include "shader.h"

#include <iostream>
#include <cmath>

//用户改变窗口的时候视口应当同时调整，注册一个回调函数在每次窗口大小被调整的时候被调用

int main()
{
    //初始化glfw
    init_glfw();

    //创建窗口（申明一个GLFWindow类的指针window，函数根据参数创建一个窗口结构体
    //然后返回这个结构体的指针，将指针赋值给window指针）
    GLFWwindow *window = glfwCreateWindow(1600, 900, "Vulightan", NULL, NULL);
    
    /*
    if (window == NULL)
    {
        std::cout <<"Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        return -1;
    }
    */
    
    //通知GLFW将窗口设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    //将frame···函数设置为glfwSet···的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //GLAD用来管理OpenGL的函数指针，所以调用OpenGL的函数之前先初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout <<"Failed to initialize GLAD" <<std::endl;
        return -1;
    }
    
    //设置视口的维度
    glViewport(0, 0, 1600, 900);
    
    //配置着色器
    //-------------------------------------------------------
    //着色器类型以参数形式入参，函数创建对应的着色器对象，并返回其ID（引用）
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //把着色器源码附加到着色器对象上（1表示传递源码字符串数量）
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //编译顶点着色器
    glCompileShader(vertexShader);

    //配置片段着色器并编译
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //创建着色器程序对象链接两个着色器对象
    unsigned int shaderProgram;
    shaderProgram = setShaderProgram(vertexShader, fragmentShader);

    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //配置物体
    //-------------------------------------------------------
    //定义三角形顶点数组
    float vertices[] = 
    {
        0.5f, 0.5f,0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    //定义索引EBO
    unsigned int indices[] = 
    {
        0, 1, 3,
        1, 2, 3
    };

    
    //创建顶点缓冲对象，配置顶点属性
    //-----------------------------------------------------
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);//函数生成一个VBO缓冲对象，并将其ID传递到第二个参数的地址上
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);//创建EBO缓冲对象
    
    
    glBindVertexArray(VAO);//绑定VAO，即将该VAO设定为上下文活动的VAO

    //把新创建的缓冲绑定到GL_A···目标上（一种缓冲类型）
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //把之前定义的数组复制到缓冲的内存里
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //告诉Opengl如何解析顶点数据，应用到逐个点属性上
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //以顶点属性位置作为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    
    //渲染循环
    //-------------------------------------------------------
    while(!glfwWindowShouldClose(window))
    {
        //监听输入
        processInput_escape(window);
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数，用来设置清空屏幕所用的颜色
        glClear(GL_COLOR_BUFFER_BIT);//状态使用函数，清除color缓冲

        //激活着色器程序
        glUseProgram(shaderProgram);
        
        //更新uniform
        double time_value = glfwGetTime();
        float green_value = sin(time_value)/2.0f + 0.5f;
        //查询uniform变量ourcolor的位置，参数还要提供着色器程序
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //注：查询uniform位置不需要使用过着色器程序，但是更新之前必须先使用
        //因为他是在当前激活的着色器程序中设置的uniform
        //设置uniform值
        glUniform4f(vertexColorLocation, 0.0f, green_value, 0.0f, 1.0f);

        glBindVertexArray(VAO);//确保绑定
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);//解绑

        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();  
    }
    
    //渲染循环结束之后需要正确释放之前分配的所有资源
    glfwTerminate();
    
    return 0;
}

