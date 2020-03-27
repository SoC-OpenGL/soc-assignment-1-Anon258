#include<iostream>
#include<cmath>

//GLEW
#define GLEW_STATIC
#include<GL/glew.h>

//GLFW
#include<GLFW/glfw3.h>

#include "Utility/Shader.hpp"
#include "Utility/Textures.hpp"
#include "Utility/glm/glm.hpp"
#include "Utility/glm/gtc/matrix_transform.hpp"
#include "Utility/glm/gtc/type_ptr.hpp"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int screenwidth, int screenheight);

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 800;

//Next we create a vertex data to draw
int num_sides = 50;
float radius = 0.8f;
GLfloat *points;

void SetData(){
    points[0] = points[1] = points[2] = 0.0f;
    points[3] = 0.5f;
    points[4] = points[5] = 0.0f;
    points[6]= points[7] = 0.5f;
    for(int i=8;i<8*(num_sides+2);i+=8){
        points[i] = (float)radius*cos((i-8)*M_PI/(4*num_sides));
        points[i+1] = (float)radius*sin((i-8)*M_PI/(4*num_sides));
        points[i+2] = 0.0f;
        points[i+3] = 0.2f;
        points[i+4] = 0.0f;
        points[i+5] = 0.0f;
        points[i+6] = (float)(1+cos((i-8)*M_PI/(4*num_sides)))/2.0f;
        points[i+7] = (float)(1+sin((i-8)*M_PI/(4*num_sides)))/2.0f;
    }
}

int main(){
    //Initialise glfw
    glfwInit();
    
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );
    
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glewExperimental = GL_TRUE;
    if(GLEW_OK != glewInit()){
        std::cout<<"Failed to initialise GLEW"<<std::endl;
        
        return EXIT_FAILURE;
    }
    
    //Now we will build and compile our shaders
    Shader shader("Shaders/vertex_shader.vs", "Shaders/fragment_shader.fs");
    Texture texture1("Images/moon.jpg");
    
    points = new GLfloat[8*(num_sides+2)];
    SetData();
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8*(num_sides+2)*sizeof(points[0]), points, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    glm::mat4 transformation = glm::mat4(1.0f);
    shader.use();
    GLuint transformLoc = glGetUniformLocation(shader.program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
    
    //Now we draw in the game loop
    while(!glfwWindowShouldClose(window)){
        
        processInput(window);
        //Check if any events have been activated - key press or something
        glfwPollEvents();
        
        //Render and Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        texture1.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_sides+2);
        glBindVertexArray(0);
        
        //swap screen buffers
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);  //We put them to 1 on line 128
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    
    return EXIT_SUCCESS;
}

//To exit
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int screenwidth, int screenheight){
    glViewport(0, 0, screenwidth, screenheight);
}
