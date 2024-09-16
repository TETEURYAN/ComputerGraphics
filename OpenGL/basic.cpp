#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


// Função para inicializar GLFW e criar uma janela
GLFWwindow* initializeGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    // Definindo o contexto OpenGL para 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criando a janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    return window;
}

// Função de inicialização do GLEW
bool initializeGLEW() {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    return true;
}

// Função para configurar os dados do triângulo
GLuint setupTriangle() {
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Vertex 1 (x, y, z)
       -0.5f, -0.5f, 0.0f, // Vertex 2 (x, y, z)
        0.5f, -0.5f, 0.0f  // Vertex 3 (x, y, z)
    };

    GLuint vertexArray, vertexBuffer, vertexShader, fragmentShader, shaderProgram;
    GLint success;
    GLchar infoLog[512];

    // Criação e configuração do Vertex Array Object (VAO)
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // Criação e configuração do Vertex Buffer Object (VBO)
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Definindo os atributos dos vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Shaders
    const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    })";

    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Vermelho
    })";

    // Compilação do Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader Compilation Error: " << infoLog << std::endl;
    }

    // Compilação do Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader Compilation Error: " << infoLog << std::endl;
    }

    // Linkando shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArray);

    return shaderProgram;
}

// Função principal
int main() {
    GLFWwindow* window = initializeGLFW();
    if (!window) return -1;

    if (!initializeGLEW()) return -1;

    GLuint shaderProgram = setupTriangle();

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Processar entrada
        glfwPollEvents();

        // Renderizar
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Trocar buffers e renderizar
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
