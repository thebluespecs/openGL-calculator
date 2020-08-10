#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./vendor/imgui/imgui.h"
#include "./vendor/imgui/imgui_impl_opengl3.h"
#include "./vendor/imgui/imgui_impl_glfw.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout<< "Error!"<<std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    float positions[] = {
            -0.5f, -0.5f, -1.0f, 
             0.5f, -0.5f, -1.0f, 
             0.5f,  0.5f, -1.0f, 
            -0.5f,  0.5f, -1.0f     
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 0, 3
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);  

    VertexArray va;
    VertexBuffer vb(positions, 4*3*sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    // layout.Push<float>(2);

    va.AddBuffer(vb, layout);
    
    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0, 0)); 
    
    Shader shader("./res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

    // Texture texture("./res/textures/smoke.png");
    // texture.Bind();
    // shader.SetUniform1i("u_Texture", 0);

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    shader.UnBind();

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    glm::vec3 translationA(0.0f, 0.0f, 0);
    // glm::vec3 translationB(0.0f, 0.0f, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */ 
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        {

            glm::mat4 model  = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model; 
    

            shader.Bind();
            // shader.SetUniform4f("u_color", r, 0.3f, 0.5f, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);

        }

        {
            
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat3("Translation A", &translationA.x, -0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            // ImGui::SliderFloat3("Translation B", &translationB.x, -0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}