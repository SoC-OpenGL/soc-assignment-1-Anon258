#include<iostream>
#include<cmath>

//GLEW
#define GLEW_STATIC
#include<GL/glew.h>

//GLFW
#include<GLFW/glfw3.h>

#include "Utility/Shader.hpp"
#include "Utility/glm/glm.hpp"
#include "Utility/glm/gtc/matrix_transform.hpp"
#include "Utility/glm/gtc/type_ptr.hpp"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int screenwidth, int screenheight);

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 800;

glm::vec3 points[2*6*64];  //2* for color
glm::vec3 locations[12] = {
    glm::vec3(-1.0f,1.0f,0.0),
    glm::vec3(-1.0f,0.0f,0.0),
    glm::vec3(0.0f,1.0f,0.0),
    glm::vec3(-1.0f,0.0f,0.0),
    glm::vec3(0.0f,1.0f,0.0),
    glm::vec3(0.0f,0.0f,0.0),  //first square
};

glm::vec3 color[2] ={
    glm::vec3(0.0f,0.0f,0.0f),
    glm::vec3(1.0f,1.0f,1.0f)
};

int ind = 0;

void DrawChess(){
    for(int j =-4;j<4;j++){
        for(int i = -3;i<5;i++){
            glm::mat4 trans = glm::mat4(1.0f);
            trans = glm::scale(trans, glm::vec3(1.0f/5.0f,1.0f/5.0f,0.0f));
            trans = glm::translate(trans, glm::vec3((float)i, (float)j,0.0f));
            for(int k=0;k<6;k++){
                glm::vec4 fin = trans * glm::vec4(locations[k].x, locations[k].y, locations[k].z, 1.0f);
                points[ind] = glm::vec3(fin.x, fin.y, fin.z);
                ind++;
                points[ind] = color[(i+j+7)%2];
                ind++;
            }
        }
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
    Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
    DrawChess();
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
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
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 64*6);
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
