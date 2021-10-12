/*
Type your name and student ID here
    - Name:       ********
    - Student ID: 1155******
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

typedef struct object
{
    int index;
    GLuint VAO;
    int verticesNumber;
    char useIndexing;
    char useColorPerVertex;
    glm::vec3 color;
} Object;

int objectNumber = 0;
Object objectArr[11];

GLint programID;
const int width = 800, height = 600;
const int skyboxSize = 1200;

// Global parameters
int cameraZRotate = 0, cameraXRotate = 75, treeRotate = 0;
const int cameraXRMax = 90, cameraXRMin = 0;
int riverx = 0, rivery = 0;
const int riverxMax = 15, riverxMin = -15, riveryMax = 20, riveryMin = -20;
char showRabbit = 0;
float bushScale = 1.0f;
const float bushMax = 1.5f, bushMin = 0.5f;
int fov = 45;
const int fovMax = 60, fovMin = 30;

// Model vertices and indices
float groundVertices[] = {
        15.0f, 60.0f, 0.0f, -15.0f, 60.0f, 0.0f, -20.0f, 30.0f, 0.0f,
        -50.0f, 30.0f, 0.0f, -70.0f, -10.0f, 0.0f, -90.0f, -10.0f, 0.0f,
        -120.0f, -50.0f, 0.0f, -1000.0f, -50.0f, 0.0f, -30.0f, -1000.0f, 0.0f,
        -40.0f, -110.0f, 0.0f, -60.0f, -100.0f, 0.0f, -60.0f, -85.0f, 0.0f,
        -45.0f, -85.0f, 0.0f, -40.0f, -65.0f, 0.0f, -25.0f, -65.0f, 0.0f,
        -7.0f, -50.0f, 0.0f, 5.0f, -50.0f, 0.0f, 10.0f, -40.0f, 0.0f,
        20.0f, -40.0f, 0.0f, 40.0f, -10.0f, 0.0f, 40.0f, 10.0f, 0.0f,
        25.0f, 30.f, 0.0f
};
unsigned int groundIndices[] = {
        0, 1, 2, 2, 3, 15, 0, 2, 21, 2, 17, 21, 17, 19, 21, 19, 20, 21, 17, 18, 19,
        2, 16, 17, 2, 15, 16, 3, 4, 15, 4, 14, 15, 4, 5, 14, 5, 13, 14, 5, 6, 13,
        6, 12, 13, 6, 11, 12, 6, 10, 11, 8, 9, 10, 6, 8, 10, 6, 7, 8
};
float logVertices[] = {
    2.0f, 0.0f, 0.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
    1.0f, 1.73f, 0.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
    -1.0f, 1.73f, 0.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
    -2.0, 0.0f, 0.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
    -1.0f, -1.73f, 0.0f, 60.0f / 255.0f, 40.0f / 255.0f, 30.0f / 255.0f,
    1.0f, -1.73f, 0.0f, 60.0f / 255.0f, 40.0f / 255.0f, 30.0f / 255.0f,

    2.0f, 0.0f, 20.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
    1.0f, 1.73f, 20.0f, 100.0f / 255.0f, 75.0f / 255.0f, 70.0f / 255.0f,
    -1.0f, 1.73f, 20.0f, 100.0f / 255.0f, 75.0f / 255.0f, 70.0f / 255.0f,
    -2.0, 0.0f, 20.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
    -1.0f, -1.73f, 20.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
    1.0f, -1.73f, 20.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
};
unsigned int logIndices[] = {
        0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 6, 7, 8, 6, 8, 9, 6, 9, 10,
        6, 10, 11, 0, 1, 6, 1, 6, 7, 1, 2, 7, 2, 7, 8, 2, 3, 8, 3, 8, 9,
        3, 4, 9, 4, 9, 10, 4, 5, 10, 5, 10, 11, 5, 6, 11, 0, 5, 6
};
float rabbitVertices[] = {
    49.22f, -58.75f, 0.0f, 66.09375f, -48.90625f, 0.0f, 33.125f, -28.4375f, 0.0f,
    27.65625f, -16.71875f, 0.0f, 3.125f, -35.625f, 0.0f, 0.3125f, -35.9375f, 0.0f,
    27.03125f, -14.6875f, 0.0f, 20.9375f, 1.71875f, 0.0f, 1.25f, 18.28125f, 0.0f,
    -40.9375f, -9.53125f, 0.0f, 14.21875f, 53.59375f, 0.0f, -15.9375f, 55.625f, 0.0f,
    25.15625f, 3.4375f, 0.0f, -12.03125f, 78.4375f, 0.0f, 33.75f, 79.375f, 0.0f,
    7.34375f, 64.0625f, 0.0f, 79.53125f, 47.96875f, 0.0f, 88.90625f, 44.53125f, 0.0f,
    92.96875f, 35.625f, 0.0f, 86.25f, 30.625f, 0.0f, 80.78125f, 39.53125f, 0.0f
};
unsigned int rabbitIndices[] = {
    0, 1, 2, 0, 3, 4, 5, 6, 8, 5, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 20, 17, 18, 20, 18, 19, 20
};
float trunkVertices[] = {
    4.0f, 4.0f, 0.0f, -4.0f, 4.0f, 0.0f, -4.0f, -4.0f, 0.0f,
    4.0f, -4.0f, 0.0f, 4.0f, 4.0f, 40.0f, -4.0f, 4.0f, 40.0f,
    -4.0f, -4.0f, 40.0f, 4.0f, -4.0f, 40.0f
};
unsigned int trunkIndices[] = {
    0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 0, 1, 4, 1, 4, 5, 1, 2, 5,
    2, 5, 6, 2, 3, 6, 3, 6, 7, 3, 4, 7, 0, 3, 4
};
float leafVertices[] = {
    4.0f, 4.0f, 0.0f, 10.0f / 255.0f, 80.0f / 255.0f, 10.0f / 255.0f,
    -4.0f, 4.0f, 0.0f, 10.0f / 255.0f, 80.0f / 255.0f, 10.0f / 255.0f,
    -4.0f, -4.0f, 0.0f, 10.0f / 255.0f, 80.0f / 255.0f, 10.0f / 255.0f,
    4.0f, -4.0f, 0.0f, 10.0f / 255.0f, 80.0f / 255.0f, 10.0f / 255.0f,
    4.0f, 4.0f, 8.0f, 64.0f / 255.0f, 140.0f / 255.0f, 64.0f / 255.0f,
    -4.0f, 4.0f, 8.0f, 64.0f / 255.0f, 140.0f / 255.0f, 64.0f / 255.0f,
    -4.0f, -4.0f, 8.0f, 64.0f / 255.0f, 140.0f / 255.0f, 64.0f / 255.0f,
    4.0f, -4.0f, 8.0f, 64.0f / 255.0f, 140.0f / 255.0f, 64.0f / 255.0f
};
unsigned int leafIndices[] = {
    0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 0, 1, 4, 1, 4, 5,
    1, 2, 5, 2, 5, 6, 2, 3, 6, 3, 6, 7, 3, 4, 7, 0, 3, 4
};
float riverVertices[] = {
    2.0f, 2.0f, 0.0f, 0.25f, 0.25f, 0.25f, // 0
    -2.0f, 2.0f, 0.0f, 0.25f, 0.25f, 0.25f,
    -2.0f, -2.0f, 0.0f, 0.25f, 0.25f, 0.25f,
    2.0f, -2.0f, 0.0f, 0.25f, 0.25f, 0.25f,
    2.0f, 2.0f, 10.0f, 1.0f, 1.0f, 1.0f,
    -2.0f, 2.0f, 10.0f, 1.0f, 1.0f, 1.0f,
    -2.0f, -2.0f, 10.0f, 1.0f, 1.0f, 1.0f,
    2.0f, -2.0f, 10.0f, 1.0f, 1.0f, 1.0f,

    8.0f, 8.0f, 10.0f, 0.2f, 0.4f, 0.7f, // 8
    -8.0f, 8.0f, 10.0f, 0.2f, 0.4f, 0.7f,
    -8.0f, -8.0f, 10.0f, 0.2f, 0.4f, 0.7f,
    8.0f, -8.0f, 10.0f, 0.2f, 0.4f, 0.7f,
    0.0f, 0.0f, 24.0f, 0.4f, 0.6f, 1.0f,

    5.0f, 5.0f, 22.0f, 0.8f, 0.6f, 0.5f, // 13
    -5.0f, 5.0f, 22.0f, 0.6f, 0.2f, 0.1f,
    -5.0f, -5.0f, 22.0f, 0.6f, 0.2f, 0.1f,
    5.0f, -5.0f, 22.0f, 0.8f, 0.6f, 0.5f,
    5.0f, 5.0f, 32.0f, 0.8f, 0.6f, 0.5f,
    -5.0f, 5.0f, 32.0f, 0.6f, 0.2f, 0.1f,
    -5.0f, -5.0f, 32.0f, 0.6f, 0.2f, 0.1f,
    5.0f, -5.0f, 32.0f, 0.8f, 0.6f, 0.5f,
};
unsigned int riverIndices[] = {
    0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 0, 1, 4, 1, 4, 5, 1, 2, 5,
    2, 5, 6, 2, 3, 6, 3, 6, 7, 3, 4, 7, 0, 3, 4, 12, 8, 9, 12, 9, 10,
    12, 10, 11, 12, 8, 11, 8, 9, 10, 8, 10, 11, 13, 14, 15, 13, 15, 16,
    17, 18, 19, 17, 19, 20, 13, 14, 17, 14, 17, 18, 14, 15, 18,
    15, 18, 19, 15, 16, 19, 16, 19, 20, 16, 17, 20, 13, 16, 17
};
float stumpVertices[] = {
        2.4f, 0.0f, 0.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
        1.2f, 2.08f, 0.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
        -1.2f, 2.08f, 0.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
        -2.4, 0.0f, 0.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
        -1.2f, -2.08f, 0.0f, 60.0f / 255.0f, 40.0f / 255.0f, 30.0f / 255.0f,
        1.2f, -2.08f, 0.0f, 60.0f / 255.0f, 40.0f / 255.0f, 30.0f / 255.0f,

        2.0f, 0.0f, 3.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
        1.0f, 1.73f, 3.0f, 100.0f / 255.0f, 75.0f / 255.0f, 70.0f / 255.0f,
        -1.0f, 1.73f, 3.0f, 100.0f / 255.0f, 75.0f / 255.0f, 70.0f / 255.0f,
        -2.0, 0.0f, 3.0f, 90.0f / 255.0f, 65.0f / 255.0f, 55.0f / 255.0f,
        -1.0f, -1.73f, 3.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
        1.0f, -1.73f, 3.0f, 75.0f / 255.0f, 53.0f / 255.0f, 42.0f / 255.0f,
};
unsigned int stumpIndices[] = {
    0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 6, 7, 8, 6, 8, 9,
    6, 9, 10, 6, 10, 11, 0, 1, 6, 1, 6, 7, 1, 2, 7, 2, 7, 8,
    2, 3, 8, 3, 8, 9, 3, 4, 9, 4, 9, 10, 4, 5, 10, 5, 10, 11,
    5, 6, 11, 0, 5, 6
};
float bushVertices[] = {
    2.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.1f,
    1.0f, 1.73f, 0.0f, 0.1f, 0.2f, 0.1f,
    -1.0f, 1.73f, 0.0f, 0.1f, 0.2f, 0.1f,
    -2.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.1f,
    -1.0f, -1.73f, 0.0f, 0.1f, 0.2f, 0.1f,
    1.0f, -1.73f, 0.0f, 0.1f, 0.2f, 0.1f,

    3.0f, 1.73f, 3.0f, 0.2f, 0.3f, 0.1f,
    0.0f, 3.46f, 3.0f, 0.2f, 0.3f, 0.1f,
    -3.0f, 1.73f, 3.0f, 0.2f, 0.3f, 0.1f,
    -3.0f, -1.73f, 3.0f, 0.2f, 0.3f, 0.1f,
    0.0f, -3.46f, 3.0f, 0.2f, 0.3f, 0.1f,
    3.0f, -1.73f, 3.0f, 0.2f, 0.3f, 0.1f,

    2.0f, 0.0f, 6.0f, 0.3f, 0.4f, 0.2f,
    1.0f, 1.73f, 6.0f, 0.3f, 0.4f, 0.2f,
    -1.0f, 1.73f, 6.0f, 0.3f, 0.4f, 0.2f,
    -2.0f, 0.0f, 6.0f, 0.3f, 0.4f, 0.2f,
    -1.0f, -1.73f, 6.0f, 0.3f, 0.4f, 0.2f,
    1.0f, -1.73f, 6.0f, 0.3f, 0.4f, 0.2f,
};
unsigned int bushIndices[] = {
    6, 0, 1, 7, 1, 2, 8, 2, 3, 9, 3, 4, 10, 4, 5, 11, 5, 0, 6, 12, 13,
    7, 13, 14, 8, 14, 15, 9, 15, 16, 10, 16, 17, 11, 17, 12, 0, 6, 11,
    12, 6, 11, 1, 6, 7, 13, 6, 7, 2, 7, 8, 14, 7, 8, 3, 8, 9, 15, 8, 9,
    4, 9, 10, 16, 9, 10, 5, 10, 11, 17, 10, 11, 0, 1, 2, 0, 2, 3, 0, 3, 4,
    0, 4, 5, 12, 13, 14, 12, 14, 15, 12, 15, 16, 12, 16, 17
};

// For making stars
void makeTriangle(
    float* vertices, int index, int component, float x, float y, float fixed, float size
)
{
    index = index * 9;
    int com1, com2;
    if (component == 0)
    {
        com1 = 1;
        com2 = 2;
    }
    else if (component == 1)
    {
        com1 = 0;
        com2 = 2;
    }
    else
    {
        com1 = 0;
        com2 = 1;
    }
    for (int i = 0; i < 3; i++)
    {
        vertices[index + i * 3 + component] = fixed;
    }
    vertices[index + com1] = x;
    vertices[index + com1 + 3] = x;
    vertices[index + com1 + 6] = x + size;
    vertices[index + com2] = y;
    vertices[index + com2 + 3] = y - size;
    vertices[index + com2 + 6] = y - size;
}

void get_OpenGL_info()
{
    // OpenGL information
    const GLubyte* name = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* glversion = glGetString(GL_VERSION);
    std::cout << "OpenGL company: " << name << std::endl;
    std::cout << "Renderer name: " << renderer << std::endl;
    std::cout << "OpenGL version: " << glversion << std::endl;
}

bool checkStatus(
    GLuint objectID,
    PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
    PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
    GLenum statusType)
{
    GLint status;
    objectPropertyGetterFunc(objectID, statusType, &status);
    if (status != GL_TRUE)
    {
        GLint infoLogLength;
        objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* buffer = new GLchar[infoLogLength];

        GLsizei bufferSize;
        getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
        std::cout << buffer << std::endl;

        delete[] buffer;
        return false;
    }
    return true;
}

bool checkShaderStatus(GLuint shaderID)
{
    return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
    return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string readShaderCode(const char* fileName)
{
    std::ifstream meInput(fileName);
    if (!meInput.good())
    {
        std::cout << "File failed to load ... " << fileName << std::endl;
        exit(1);
    }
    return std::string(
        std::istreambuf_iterator<char>(meInput),
        std::istreambuf_iterator<char>());
}

void installShaders()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* adapter[1];
    //adapter[0] = vertexShaderCode;
    std::string temp = readShaderCode("VertexShaderCode.glsl");
    adapter[0] = temp.c_str();
    glShaderSource(vertexShaderID, 1, adapter, 0);
    //adapter[0] = fragmentShaderCode;
    temp = readShaderCode("FragmentShaderCode.glsl");
    adapter[0] = temp.c_str();
    glShaderSource(fragmentShaderID, 1, adapter, 0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
        return;

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    if (!checkProgramStatus(programID))
        return;

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // We only have one shader program, so call this here rather than paint
    glUseProgram(programID);
}

// Calculate model transformation matrix
glm::mat4 modelMat(int objectIndex)
{
    glm::mat4 mat = glm::mat4(1.0f);
    switch (objectIndex)
    {
    case 0:
    case 1:
        // Ground
        mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, -30.0f));
        return mat;
    case 2:
    default:
        // Skybox
        return glm::mat4(1.0f);
    case 3:
        // Log
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, -30.0f));
        mat = glm::scale(mat, glm::vec3(2.0f, 1.4f, 2.0f));
        mat = glm::translate(mat, glm::vec3(0.0f, 10.0f, 1.74f));
        mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        return mat;
    case 4:
        // Moon
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(skyboxSize - 1.0f, 0.0f, 0.0f));
        mat = glm::scale(mat, glm::vec3(0.8f, 0.8f, 0.8f));
        mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return mat;
    case 5:
        // Rabbit
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(skyboxSize - 2.0f, 40.0f, 40.0f));
        mat = glm::scale(mat, glm::vec3(1.0f, 1.0f, 1.0f));
        mat = glm::rotate(
            mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)
        );
        mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return mat;
    case 6:
        // Tree trunk
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(-30.0f, -30.0f, -29.9f));
        mat = glm::rotate(
            mat, glm::radians((float)treeRotate), glm::vec3(0.0f, 0.0f, 1.0f)
        );
        mat = glm::scale(mat, glm::vec3(0.75f, 0.75f, 0.75f));
        return mat;
    case 7:
        // Tree leaf
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(-30.0f, -30.0f, -8.0f));
        mat = glm::rotate(
            mat, glm::radians((float)treeRotate), glm::vec3(0.0f, 0.0f, 1.0f)
        );
        mat = glm::scale(mat, glm::vec3(3.0f, 3.0f, 3.0f));
        return mat;
    case 8:
        // River
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3((float)riverx, (float)rivery, 0.0f));
        mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, -29.0f));
        mat = glm::scale(mat, glm::vec3(0.6f, 0.6f, 0.6f));
        return mat;
    case 9:
        // Stump
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(0.0f, -36.0f, -30.0f));
        mat = glm::scale(mat, glm::vec3(1.8f, 1.8f, 1.6f));
        return mat;
    case 10:
        // Bush
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, glm::vec3(-56.0f, -64.0f, -30.0f));
        mat = glm::scale(mat, glm::vec3(bushScale, bushScale, bushScale));
        mat = glm::scale(mat, glm::vec3(4.0f, 4.0f, 3.2f));
        return mat;
    }
}

void sendDataToOpenGL()
{
    // create 2D objects and 3D objects and/or lines (points) here and bind to VAOs & VBOs

    // Ground
    GLuint groundVAO;
    glGenVertexArrays(1, &groundVAO);
    glBindVertexArray(groundVAO);

    GLuint groundVBO;
    glGenBuffers(1, &groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    GLuint groundEBO;
    glGenBuffers(1, &groundEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 0;
    objectArr[objectNumber].VAO = groundVAO;
    objectArr[objectNumber].verticesNumber = sizeof(groundIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 0.247f;
    objectArr[objectNumber].color.g = 0.388f;
    objectArr[objectNumber].color.b = 0.184f;
    objectNumber++;


    // Ground Side (Cliff)
    GLuint groundSideVAO;
    glGenVertexArrays(1, &groundSideVAO);
    glBindVertexArray(groundSideVAO);

    // Copy from ground
    int groundVerticesNumber = sizeof(groundVertices) / sizeof(float) / 3;
    float* groundSideVertices = (float*) malloc(sizeof(float) * groundVerticesNumber * 3 * 2);
    memcpy(groundSideVertices, groundVertices, sizeof(groundVertices));
    memcpy(
        (float*)((unsigned long long)groundSideVertices + sizeof(groundVertices)),
        groundVertices,
        sizeof(groundVertices)
    );
    for (int i = 0; i < groundVerticesNumber * 3; i += 3)
    {
        groundSideVertices[i + groundVerticesNumber * 3 + 2] = -1000.0f;
    }
    GLuint groundSideVBO;
    glGenBuffers(1, &groundSideVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundSideVBO);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(float) * groundVerticesNumber * 3 * 2, groundSideVertices, GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    unsigned int* groundSideIndices = (unsigned int*) malloc(
        sizeof(unsigned int) * groundVerticesNumber * 2 * 3
    );
    for (int i = 0; i < groundVerticesNumber; i++)
    {
        groundSideIndices[i * 6] = i;
        groundSideIndices[i * 6 + 1] = (i + 1) % groundVerticesNumber;
        groundSideIndices[i * 6 + 2] = i + groundVerticesNumber;
        groundSideIndices[i * 6 + 3] = (i + 1) % groundVerticesNumber;
        groundSideIndices[i * 6 + 4] = i + groundVerticesNumber;
        groundSideIndices[i * 6 + 5] = (i + 1) % groundVerticesNumber + groundVerticesNumber;
    }
    GLuint groundSideEBO;
    glGenBuffers(1, &groundSideEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundSideEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * groundVerticesNumber * 2 * 3, groundSideIndices, GL_STATIC_DRAW
    );
    free(groundSideVertices);
    free(groundSideIndices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 1;
    objectArr[objectNumber].VAO = groundSideVAO;
    objectArr[objectNumber].verticesNumber = groundVerticesNumber * 2 * 3;
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 111.0f / 255.0f;
    objectArr[objectNumber].color.g = 95.0f / 255.0f;
    objectArr[objectNumber].color.b = 78.0f / 255.0f;
    objectNumber++;


    // Skybox
    GLuint skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glBindVertexArray(skyboxVAO);

    const int starNumber = 700;
    int starSize = 3;
    srand(4869);
    // 3 components * 3 points * 6 surfaces
    float skyboxVertices[starNumber * 3 * 3 * 6];
    // For each component (x, y, z surfaces)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < starNumber; j++)
        {
            float cox = (float)((double)rand() / RAND_MAX * 2 * skyboxSize - skyboxSize);
            float coy = (float)((double)rand() / RAND_MAX * 2 * skyboxSize - skyboxSize);
            int index = i * 2 * starNumber + j * 2;
            // Mirror for another side
            makeTriangle(skyboxVertices, index++, i, cox, coy, skyboxSize, starSize);
            makeTriangle(skyboxVertices, index, i, cox, coy, -skyboxSize, starSize);
        }
    }
    GLuint skyboxVBO;
    glGenBuffers(1, &skyboxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 2;
    objectArr[objectNumber].VAO = skyboxVAO;
    objectArr[objectNumber].verticesNumber = 6 * starNumber * 3;
    objectArr[objectNumber].useIndexing = 0;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 1.0f;
    objectArr[objectNumber].color.g = 1.0f;
    objectArr[objectNumber].color.b = 1.0f;
    objectNumber++;


    // Log
    GLuint logVAO;
    glGenVertexArrays(1, &logVAO);
    glBindVertexArray(logVAO);

    GLuint logVBO;
    glGenBuffers(1, &logVBO);
    glBindBuffer(GL_ARRAY_BUFFER, logVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(logVertices), logVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    GLuint logEBO;
    glGenBuffers(1, &logEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, logEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(logIndices), logIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 3;
    objectArr[objectNumber].VAO = logVAO;
    objectArr[objectNumber].verticesNumber = sizeof(logIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 1;
    objectNumber++;


    // Moon
    GLuint moonVAO;
    glGenVertexArrays(1, &moonVAO);
    glBindVertexArray(moonVAO);
    // Use 30 edges to emulate a circle
    const int moonVerticesNumber = 30;
    float radius = 50;
    float moonVertices[(moonVerticesNumber + 1) * 3];
    std::memset(moonVertices, 0, sizeof(moonVertices));
    for (int i = 1; i <= moonVerticesNumber; i++)
    {
        double theta = (i - 1) * ((double)360 / moonVerticesNumber);
        float x = radius * sin(theta / 180 * 3.14159f);
        float y = radius * cos(theta / 180 * 3.14159f);
        moonVertices[i * 3] = x;
        moonVertices[i * 3 + 1] = y;
    }
    GLuint moonVBO;
    glGenBuffers(1, &moonVBO);
    glBindBuffer(GL_ARRAY_BUFFER, moonVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(moonVertices), moonVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    unsigned int moonIndices[moonVerticesNumber * 3];
    for (int i = 0; i < moonVerticesNumber; i++) {
        moonIndices[i * 3] = 0;
        moonIndices[i * 3 + 1] = i + 1;
        moonIndices[i * 3 + 2] = (i + 1) % moonVerticesNumber + 1;
    }
    GLuint moonEBO;
    glGenBuffers(1, &moonEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moonEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(moonIndices), moonIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 4;
    objectArr[objectNumber].VAO = moonVAO;
    objectArr[objectNumber].verticesNumber = (moonVerticesNumber + 1) * 3;
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 1.0f;
    objectArr[objectNumber].color.g = 0.83f;
    objectArr[objectNumber].color.b = 0.0f;
    objectNumber++;


    // Rabbit
    GLuint rabbitVAO;
    glGenVertexArrays(1, &rabbitVAO);
    glBindVertexArray(rabbitVAO);

    GLuint rabbitVBO;
    glGenBuffers(1, &rabbitVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rabbitVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rabbitVertices), rabbitVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    GLuint rabbitEBO;
    glGenBuffers(1, &rabbitEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rabbitEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(rabbitIndices), rabbitIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 5;
    objectArr[objectNumber].VAO = rabbitVAO;
    objectArr[objectNumber].verticesNumber = sizeof(rabbitIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 0.18f;
    objectArr[objectNumber].color.g = 0.43f;
    objectArr[objectNumber].color.b = 0.64f;
    objectNumber++;


    // Tree trunk
    GLuint trunkVAO;
    glGenVertexArrays(1, &trunkVAO);
    glBindVertexArray(trunkVAO);

    GLuint trunkVBO;
    glGenBuffers(1, &trunkVBO);
    glBindBuffer(GL_ARRAY_BUFFER, trunkVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trunkVertices), trunkVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    GLuint trunkEBO;
    glGenBuffers(1, &trunkEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trunkEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(trunkIndices), trunkIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 6;
    objectArr[objectNumber].VAO = trunkVAO;
    objectArr[objectNumber].verticesNumber = sizeof(trunkIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 0;
    objectArr[objectNumber].color.r = 74.0f / 255.0f;
    objectArr[objectNumber].color.g = 47.0f / 255.0f;
    objectArr[objectNumber].color.b = 22.0f / 255.0f;
    objectNumber++;


    // Tree leaves
    GLuint leafVAO;
    glGenVertexArrays(1, &leafVAO);
    glBindVertexArray(leafVAO);

    GLuint leafVBO;
    glGenBuffers(1, &leafVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leafVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leafVertices), leafVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
    GLuint leafEBO;
    glGenBuffers(1, &leafEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leafEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(leafIndices), leafIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 7;
    objectArr[objectNumber].VAO = leafVAO;
    objectArr[objectNumber].verticesNumber = sizeof(leafIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 1;
    objectNumber++;


    // River
    GLuint riverVAO;
    glGenVertexArrays(1, &riverVAO);
    glBindVertexArray(riverVAO);

    GLuint riverVBO;
    glGenBuffers(1, &riverVBO);
    glBindBuffer(GL_ARRAY_BUFFER, riverVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(riverVertices), riverVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
    GLuint riverEBO;
    glGenBuffers(1, &riverEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, riverEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(riverIndices), riverIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 8;
    objectArr[objectNumber].VAO = riverVAO;
    objectArr[objectNumber].verticesNumber = sizeof(riverIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 1;
    objectNumber++;


    // Stump
    GLuint stumpVAO;
    glGenVertexArrays(1, &stumpVAO);
    glBindVertexArray(stumpVAO);

    GLuint stumpVBO;
    glGenBuffers(1, &stumpVBO);
    glBindBuffer(GL_ARRAY_BUFFER, stumpVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(stumpVertices), stumpVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    GLuint stumpEBO;
    glGenBuffers(1, &stumpEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stumpEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(stumpIndices), stumpIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 9;
    objectArr[objectNumber].VAO = stumpVAO;
    objectArr[objectNumber].verticesNumber = sizeof(stumpIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 1;
    objectNumber++;


    // Bushes
    GLuint bushVAO;
    glGenVertexArrays(1, &bushVAO);
    glBindVertexArray(bushVAO);

    GLuint bushVBO;
    glGenBuffers(1, &bushVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bushVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bushVertices), bushVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    GLuint bushEBO;
    glGenBuffers(1, &bushEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bushEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(bushIndices), bushIndices, GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    objectArr[objectNumber].index = 10;
    objectArr[objectNumber].VAO = bushVAO;
    objectArr[objectNumber].verticesNumber = sizeof(bushIndices) / sizeof(unsigned int);
    objectArr[objectNumber].useIndexing = 1;
    objectArr[objectNumber].useColorPerVertex = 1;
    objectNumber++;
}

void paintGL(void)
{
    // always run
    // render your objects and control the transformation here

    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
    view = glm::scale(view, glm::vec3(0.01f, 0.01f, 0.01f));
    view = glm::rotate(
        view, glm::radians((float)cameraXRotate), glm::vec3(-1.0f, 0.0f, 0.0f)
    );
    view = glm::rotate(
        view, glm::radians((float)cameraZRotate), glm::vec3(0.0f, 0.0f, 1.0f)
    );
    view = glm::translate(view, glm::vec3(-(float)riverx, -(float)rivery, 0.0f));
    // Set projection
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(
        glm::radians((float)fov), (float)width / height, 0.1f, 20.0f
    );
    GLint viewLoc = glGetUniformLocation(programID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    GLint projectionLoc = glGetUniformLocation(programID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

    // Draw objects
    for (int i = 0; i < objectNumber; i++)
    {
        // Rabbit is toggled by keyboard
        if (i == 5 && !showRabbit)
            continue;
        glm::mat4 model = modelMat(objectArr[i].index);
        GLint modelLoc = glGetUniformLocation(programID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

        glBindVertexArray(objectArr[i].VAO);
        GLint colorPerVertexLoc = glGetUniformLocation(programID, "colorPerVertex");
        
        if (objectArr[i].useColorPerVertex == 1)
        {
            // If specify color in vertex array
            glUniform1i(colorPerVertexLoc, 1);
        }
        else
        {
            // Else: use same color for all vertices
            glUniform1i(colorPerVertexLoc, 0);
            GLint colorLoc = glGetUniformLocation(programID, "color");
            glUniform3fv(colorLoc, 1, &(objectArr[i].color[0]));
        }
        // Use vertex indexing or not
        if (objectArr[i].useIndexing == 1)
            glDrawElements(GL_TRIANGLES, objectArr[i].verticesNumber, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, objectArr[i].verticesNumber);
        glBindVertexArray(0);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS) return;
    if (key == GLFW_KEY_Q)
        cameraZRotate = (cameraZRotate + 360 + 10) % 360;
    else if (key == GLFW_KEY_E)
        cameraZRotate = (cameraZRotate - 10 + 360) % 360;
    else if (key == GLFW_KEY_Z)
    {
        int tmp = cameraXRotate + 10;
        cameraXRotate = tmp <= cameraXRMax && tmp >= cameraXRMin ? tmp : cameraXRotate;
    }
    else if (key == GLFW_KEY_X)
    {
        int tmp = cameraXRotate - 10;
        cameraXRotate = tmp <= cameraXRMax && tmp >= cameraXRMin ? tmp : cameraXRotate;
    }
    else if (key == GLFW_KEY_R)
        treeRotate = (treeRotate + 10 + 360) % 360;
    else if (key == GLFW_KEY_SPACE)
        showRabbit = !showRabbit;
    else if (key == GLFW_KEY_C)
    {
        float tmp = bushScale - 0.1f;
        bushScale = tmp >= bushMin ? tmp : bushScale;
    }
    else if (key == GLFW_KEY_V)
    {
        float tmp = bushScale + 0.1f;
        bushScale = tmp <= bushMax ? tmp : bushScale;
    }
    else if (key == GLFW_KEY_F)
    {
        int tmp = fov - 5;
        fov = tmp >= fovMin ? tmp : fov;
    }
    else if (key == GLFW_KEY_G)
    {
        int tmp = fov + 5;
        fov = tmp <= fovMax ? tmp : fov;
    }
    // For adaptive control, we need to know current camera angle
    else if (cameraZRotate < 45 || cameraZRotate >= 315)
    {
        if (key == GLFW_KEY_W && rivery < riveryMax) rivery += 8;
        if (key == GLFW_KEY_D && riverx < riverxMax) riverx += 8;
        if (key == GLFW_KEY_S && rivery > riveryMin) rivery -= 8;
        if (key == GLFW_KEY_A && riverx > riverxMin) riverx -= 8;
    }
    else if (cameraZRotate < 135 && cameraZRotate >= 45)
    {
        if (key == GLFW_KEY_A && rivery < riveryMax) rivery += 8;
        if (key == GLFW_KEY_W && riverx < riverxMax) riverx += 8;
        if (key == GLFW_KEY_D && rivery > riveryMin) rivery -= 8;
        if (key == GLFW_KEY_S && riverx > riverxMin) riverx -= 8;

    }
    else if (cameraZRotate < 225 && cameraZRotate >= 135)
    {
        if (key == GLFW_KEY_S && rivery < riveryMax) rivery += 8;
        if (key == GLFW_KEY_A && riverx < riverxMax) riverx += 8;
        if (key == GLFW_KEY_W && rivery > riveryMin) rivery -= 8;
        if (key == GLFW_KEY_D && riverx > riverxMin) riverx -= 8;
    }
    else if (cameraZRotate < 315 && cameraZRotate >= 225)
    {
        if (key == GLFW_KEY_D && rivery < riveryMax) rivery += 8;
        if (key == GLFW_KEY_S && riverx < riverxMax) riverx += 8;
        if (key == GLFW_KEY_A && rivery > riveryMin) rivery -= 8;
        if (key == GLFW_KEY_W && riverx > riverxMin) riverx -= 8;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void initializedGL(void)
{
    // run only once
    glEnable(GL_DEPTH_TEST);
    sendDataToOpenGL();
    installShaders();
}

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the glfw */
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    /* glfw: configure; necessary for MAC */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* do not allow resizing */
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Assignment 1", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    /* Initialize the glew */
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    get_OpenGL_info();
    initializedGL();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        paintGL();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/**
 * Ground x 1                  Done
 *   Refine model              Done
 * Bush x 1                    Done
 *   Key - scale               Done
 * Tree x 1                    Done
 *   Key - rotate              Done
 *   Refine model              Skipped
 * Stump x 1                   Done
 * Moon x 1                    Done
 * Rabbit x 1                  Done
 *   Enter key toggle rabbit   Done
 * Character? x 1              Done
 *   WASD move (within area)   Done
 * Flower x n *                Skipped
 * Limit camera view           Done
 * Try different perspective   Done
 */
