#include <glad/gl.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Shader.h"
#include <cmath>
#include <optional>
#include <iostream>
#include "stb_image.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}),"Primitives");
    int version = gladLoadGL(reinterpret_cast<GLADloadfunc>(sf::Context::getFunction));

    if (version == 0){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    
      float vertices[] = {
// positions // colors // texture coords
0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};
    
    unsigned int indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
       
        };

    glViewport(0, 0, 800, 600);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
   
        unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //creates a buffer that will hold the vertex data for the triangle
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
    
    
    Shader ourShader("src/triangleShader","src/FragmentShader");
  
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("src/Sprites/ODG24R0.jpg", &width, &height,
    &nrChannels, 0);
    
    if (data)
        {

    GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
            GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
            else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

    stbi_image_free(data);
        
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    sf::Clock gameClock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

       
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
       float timeValue = gameClock.getElapsedTime().asSeconds();

    float greenValue =
        (std::sin(timeValue) / 2.0f) + 0.5f;
    float green2Value = (std::cos(timeValue) /1.5f +.2f);
    // Activate shader
    ourShader.use();

    // Update uniform EVERY FRAME
    ourShader.setVec4(
        "ourcolor",
        0.0f,
        greenValue,
        0.0f,
        1.0f
    );
     ourShader.setVec4(
        "ourcolor2",
        0.0f,
        0.0f,
        green2Value,
        1.0f
    );
        
       glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //WireFrame mode
       // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        window.display();
    }

    return 0;
}