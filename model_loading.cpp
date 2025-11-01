#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <stb_image.h>
#include <ctime>
#include <iostream>

 // callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float camYaw = 0.0f;
float camPitch = 45.0f;


unsigned int cubeVAO = 0, cubeVBO = 0;
void renderCube()
{
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // positions          // normals           // texcoords
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f,0.0f, -1.0f, 0.0f,0.0f,
             0.5f, 0.5f, -0.5f, 0.0f,0.0f, -1.0f, 1.0f,1.0f,
             0.5f, -0.5f, -0.5f, 0.0f,0.0f, -1.0f, 1.0f,0.0f,
             0.5f, 0.5f, -0.5f, 0.0f,0.0f, -1.0f, 1.0f,1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f,0.0f, -1.0f, 0.0f,0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f,0.0f, -1.0f, 0.0f,1.0f,
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f,0.0f, 1.0f, 0.0f,0.0f,
             0.5f, -0.5f, 0.5f, 0.0f,0.0f, 1.0f, 1.0f,0.0f,
             0.5f, 0.5f, 0.5f, 0.0f,0.0f, 1.0f, 1.0f,1.0f,
             0.5f, 0.5f, 0.5f, 0.0f,0.0f, 1.0f, 1.0f,1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f,0.0f, 1.0f, 0.0f,1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f,0.0f, 1.0f, 0.0f,0.0f,
            // Left face
            -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f,0.0f,0.0f, 1.0f,1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f,1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f,1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f,0.0f,0.0f, 0.0f,0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f,0.0f,0.0f, 1.0f,0.0f,
            // Right face
             0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f, 1.0f,0.0f,
             0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,
             0.5f, 0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f,1.0f,
             0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f,1.0f,
             0.5f, 0.5f, 0.5f, 1.0f,0.0f,0.0f, 1.0f,0.0f,
             0.5f, -0.5f, 0.5f, 1.0f,0.0f,0.0f, 0.0f,0.0f,
             // Bottom face
             -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,0.0f, 0.0f,1.0f,
              0.5f, -0.5f, -0.5f, 0.0f, -1.0f,0.0f, 1.0f,1.0f,
              0.5f, -0.5f, 0.5f, 0.0f, -1.0f,0.0f, 1.0f,0.0f,
              0.5f, -0.5f, 0.5f, 0.0f, -1.0f,0.0f, 1.0f,0.0f,
             -0.5f, -0.5f, 0.5f, 0.0f, -1.0f,0.0f, 0.0f,0.0f,
             -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,0.0f, 0.0f,1.0f,
             // Top face
             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f, 0.0f,1.0f,
              0.5f, 0.5f, 0.5f, 0.0f, 1.0f,0.0f, 1.0f,0.0f,
              0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f, 1.0f,1.0f,
              0.5f, 0.5f, 0.5f, 0.0f, 1.0f,0.0f, 1.0f,0.0f,
             -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f, 0.0f,1.0f,
             -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,0.0f, 0.0f,0.0f
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// Floor texture
unsigned int floorTexture = 0;
// Wall texture
unsigned int wallTexture = 0;

const float MAP_HALF = 245.0f; 
const float WALL_LENGTH = 490.0f; 
const float WALL_HEIGHT = 20.0f; 

const float PLAYER_RADIUS = 1.0f; // Player collision radius

float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL UV Layout", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    
    Shader ourShader("1.model_loading.vs", "1.model_loading.fs");
    stbi_set_flip_vertically_on_load(false);
    // load model
    Model player(FileSystem::getPath("resources/objects/padoru/padoru.obj"));
    Model sack(FileSystem::getPath("resources/objects/padoru/sack.obj"));
    unsigned int uvTexture;
    glGenTextures(1, &uvTexture);
    glBindTexture(GL_TEXTURE_2D, uvTexture);

    // Load floor 
    glGenTextures(1, &floorTexture);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/padoru/Floor.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = nrChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load floor texture!" << std::endl;
    }
    stbi_image_free(data);

    // Load wall texture
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    int wallWidth, wallHeight, wallChannels;
    unsigned char* wallData = stbi_load(FileSystem::getPath("resources/textures/padoru/wall.jpg").c_str(), &wallWidth, &wallHeight, &wallChannels, 0);
    if (wallData)
    {
        GLenum wallFormat = wallChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, wallFormat, wallWidth, wallHeight, 0, wallFormat, GL_UNSIGNED_BYTE, wallData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load wall texture!" << std::endl;
    }
    stbi_image_free(wallData);

    // Model positions
    glm::vec3 playerPos(0.0f, 0.0f, 0.0f); // padoru lower to ground
    glm::vec3 sackPos(0.0f, 0.5f, 0.0f); // sack
    glm::vec3 playerDir(0.0f, 0.0f, 1.0f); // initial facing direction
    int score =0;
    // Sacks positions
    const int sackCount =10;
    glm::vec3 sackPositions[sackCount];
    for (int i =0; i < sackCount; ++i) {
        float angle = (i / (float)sackCount) *2.0f *3.14159f;
        float radius =10.0f + randomFloat(-240.0f,240.0f) *0.1f;
        sackPositions[i] = glm::vec3(cos(angle) * radius,0.5f, sin(angle) * radius);
    }

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // Move player
        glm::vec3 move(0.0f);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) move.z -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) move.z += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) move.x += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) move.x -= 1.0f;
        if (move != glm::vec3(0.0f)) {
            float yawRad = glm::radians(camYaw);
            glm::vec3 camForward = glm::normalize(glm::vec3(cos(yawRad), 0.0f, sin(yawRad)));
            glm::vec3 camRight = glm::normalize(glm::vec3(-sin(yawRad), 0.0f, cos(yawRad)));
            glm::vec3 moveDir = move.x * camRight + move.z * camForward;
            playerDir = glm::normalize(moveDir);
            moveDir = playerDir * deltaTime * 50.0f;
            glm::vec3 newPlayerPos = playerPos + moveDir;
            // Wall hit detection: prevent moving through walls
            newPlayerPos.x = glm::clamp(newPlayerPos.x, -MAP_HALF + PLAYER_RADIUS, MAP_HALF - PLAYER_RADIUS);
            newPlayerPos.z = glm::clamp(newPlayerPos.z, -MAP_HALF + PLAYER_RADIUS, MAP_HALF - PLAYER_RADIUS);
            playerPos = newPlayerPos;
        }

        // Camera position and front
        float camHeight = 30.0f;
        float camRadius = 15.0f; 
        float yawRad = glm::radians(camYaw);
        float pitchRad = glm::radians(camPitch);
        glm::vec3 camOffset(
            camRadius * cos(pitchRad) * cos(yawRad),
            camRadius * sin(pitchRad),
            camRadius * cos(pitchRad) * sin(yawRad)
        );
        camera.Position = playerPos + camOffset;
        camera.Front = glm::normalize(playerPos - camera.Position);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Draw ground
        ourShader.setInt("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glm::mat4 groundModel = glm::scale(glm::mat4(1.0f), glm::vec3(WALL_LENGTH, 1.0f, WALL_LENGTH));
        groundModel = glm::translate(groundModel, glm::vec3(0.0f, -0.5f, 0.0f));
        ourShader.setMat4("model", groundModel);
        renderCube();

        for (int i = 0; i < 4; ++i) {
            glm::mat4 wallModel = glm::mat4(1.0f);
            if (i < 2) {
                float zPos = (i == 0) ? -MAP_HALF : MAP_HALF;
                wallModel = glm::translate(wallModel, glm::vec3(0.0f, WALL_HEIGHT, zPos));
                wallModel = glm::rotate(wallModel, glm::radians(90.0f), glm::vec3(0, 1, 0));
                wallModel = glm::scale(wallModel, glm::vec3(1.0f, -WALL_HEIGHT*2, WALL_LENGTH));
            }
            else {
                float xPos = (i == 2) ? -MAP_HALF : MAP_HALF;
                wallModel = glm::translate(wallModel, glm::vec3(xPos, WALL_HEIGHT, 0.0f));
                wallModel = glm::scale(wallModel, glm::vec3(1.0f, -WALL_HEIGHT*2, WALL_LENGTH));
            }
            ourShader.setMat4("model", wallModel);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, wallTexture);
            ourShader.setInt("texture_diffuse1", 0);
            renderCube();
        }

        // Draw player (padoru)
        glBindTexture(GL_TEXTURE_2D, uvTexture);
        float playerAngle = 0.0f;
        if (move != glm::vec3(0.0f)) {
            playerAngle = atan2(playerDir.x, playerDir.z); 
        }
        else {
            playerAngle = atan2(camera.Front.x, camera.Front.z); 
        }
        glm::mat4 playerModel = glm::mat4(1.0f);
        playerModel = glm::translate(playerModel, playerPos);
        playerModel = glm::rotate(playerModel, playerAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        playerModel = glm::scale(playerModel, glm::vec3(2.0f));
        ourShader.setMat4("model", playerModel);
        player.Draw(ourShader);

        // Draw sacks
        float time = static_cast<float>(glfwGetTime());
        for (int i =0; i < sackCount; ++i) {
            glm::vec3 sackPos = sackPositions[i];
            glm::vec3 sackDir = glm::normalize(playerPos - sackPos);
            float sackAngle = atan2(-sackDir.x, sackDir.z);
            glm::mat4 sackModel = glm::mat4(1.0f);
            sackModel = glm::translate(sackModel, sackPos);
            sackModel = glm::rotate(sackModel, sackAngle, glm::vec3(0.0f,1.0f,0.0f));
            sackModel = glm::rotate(sackModel, time *3.0f, glm::vec3(0.0f,1.0f,0.0f));
            sackModel = glm::scale(sackModel, glm::vec3(4.0f));
            ourShader.setMat4("model", sackModel);
            sack.Draw(ourShader);
        }

        // Hit detection 
        float hitDist =2.0f;
        for (int i =0; i < sackCount; ++i) {
            if (glm::distance(playerPos, sackPositions[i]) < hitDist) {
                
                float angle = randomFloat(-240.0f,240.0f) *3.14159f /180.0f;
                float radius =10.0f + randomFloat(-240.0f,240.0f) *0.1f;
                sackPositions[i] = playerPos + glm::vec3(cos(angle) * radius,0.5f, sin(angle) * radius); 
                sackPositions[i].x = glm::clamp(sackPositions[i].x, -120.0f,120.0f);
                sackPositions[i].z = glm::clamp(sackPositions[i].z, -120.0f,120.0f);
                score++;
                std::cout << "Score: " << score << std::endl;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// input callbacks
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// mouse_callback: update camYaw/camPitch
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    static float lastX = SCR_WIDTH / 2.0f;
    static float lastY = SCR_HEIGHT / 2.0f;
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Invert up/down
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    camYaw += xoffset * sensitivity;
    camPitch -= yoffset * sensitivity; // Inverted
    camPitch = glm::clamp(camPitch, 0.0f, 89.0f); //0=top-down,89=side
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
