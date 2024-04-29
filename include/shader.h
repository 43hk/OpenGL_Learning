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
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }   
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
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
    checkCompileErrors(vertex, "VERTEX");

    //片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //如果出错，打印错误
    checkCompileErrors(fragment, "FRAGMENT");

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

#endif

