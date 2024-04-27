#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/*
着色器类储存了着色器程序的ID。它的构造器需要顶点和片段着色器源代码的文件路径，
这样我们就可以把源码的文本文件储存在硬盘上了。除此之外，为了让我们的生活更轻松
一点，还加入了一些工具函数：use用来激活着色器程序，所有的set…函数能够查询一个
unform的位置值并设置它的值。
*/

class Shader
{
public:
    unsigned int ID;
    //构造器读取并构建着色器
    Shader(const char *vertexPath, const char *fragmentPath);
    //使用激活程序
    void use();
    //uniform工具函数
    //const位于参数列表后，表示这是一个常量成员函数,意味该函数不会修改类的任何成员变量
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    //从文件路径获取着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
} 


//着色器源码
//------------------------------------------------------------------
//顶点着色器
const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

//片段着色器
const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

#endif