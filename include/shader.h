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
    void use()
    {
        glUseProgram(ID);
    }
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
    //保证ifstream可以抛出异常
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        //转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str(); 
    }
    catch(std::ifstream::failure e)
    {
        std::cout <<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" <<std::endl;
    }
    
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    //编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    //如果出错，打印错误
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }

    //片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //如果出错，打印错误
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout <<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog <<std::endl;
    }

    //着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    //打印错误
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success);
    {
        glGetProgramInfoLog(ID, 512,NULL, infoLog);
        std::cout <<"ERROR_SHADER_PROGRAM::LINKING_FAILED\n" <<infoLog <<std::endl;
    }

    //删除着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
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