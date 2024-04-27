//着色器源码
//------------------------------------------------------------------
//顶点着色器
const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//片段着色器
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "uniform vec4 ourColor;"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\0";