#ifndef Shader_H
#define Shader_H
#include <glad/gl.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
// the program ID
unsigned int ID;
// constructor reads and builds the shader
Shader(const char* vertexPath, const char* fragmentPath)
{
// 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
        catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    // Check compilation
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);

        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    };
    

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    
        if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);

        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
    }
    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);


}
// use/activate the shader
void use(){
    glUseProgram(ID);
}
// utility uniform functions
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

void setVec4(
    const std::string &name,
    float x,
    float y,
    float z,
    float w
) const
{
    glUniform4f(
        glGetUniformLocation(ID, name.c_str()),
        x, y, z, w
    );
}
};
#endif
