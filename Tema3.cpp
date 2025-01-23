#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>       
#include <stdlib.h>     
#include <cmath>

using namespace std;
using namespace m1;


Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
    srand((unsigned int)time(NULL));
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "grass_bilboard.png").c_str(), GL_REPEAT);
        mapTextures["grass"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["crate"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "earth.png").c_str(), GL_REPEAT);
        mapTextures["earth"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "cola.png").c_str(), GL_REPEAT);
        mapTextures["cola"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "brazil.png").c_str(), GL_REPEAT);
        mapTextures["brazil"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "rainbow.png").c_str(), GL_REPEAT);
        mapTextures["rainbow"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "dinamo.png").c_str(), GL_REPEAT);
        mapTextures["dinamo"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "romania.png").c_str(), GL_REPEAT);
        mapTextures["romania"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "soare.png").c_str(), GL_REPEAT);
        mapTextures["soare"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "striped.png").c_str(), GL_REPEAT);
        mapTextures["striped"] = texture;
    }

    {
        mapTextures["random"] = CreateRandomTexture(25, 25);
    }

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.5f,  0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f,  0.5f, 0.0f),
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f)
        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    GetSceneCamera()->SetPosition(glm::vec3(0, 3, 15));
    GetSceneCamera()->SetRotation(glm::vec3(0, 0, 0));
    GetSceneCamera()->Update();


    vector<string> possibleTextures = {
       "brazil", "dinamo", "striped", "romania" , "earth"
    };

    int numberOfBalloons = 5;

    float minDistanceBetweenCenters = 1.6f;

    for (int i = 0; i < numberOfBalloons; i++)
    {
        BalloonData bData;

        bData.texture = mapTextures[possibleTextures[i]];

        float newRadius = 2 + rand() % 6;
        float newOmega = 0.1f + (float)(rand() % 5) * 0.1f;

        bData.radius = newRadius;
        bData.omega = newOmega;
        bData.height = 0.5f + rand() % 3;
        bData.amplitude = 0.2f + (rand() % 4) * 0.1f;
        bData.freq = 2.0f;
        bData.offset = (float)(rand() % 360);
        bool collision;
        int attempts = 0;
        do {
            collision = false;
            for (int j = 0; j < i; j++)
            {
                float rDiff = fabs(newRadius - balloons[j].radius);
                if (rDiff < minDistanceBetweenCenters)
                {
                    collision = true;
                    newRadius += 0.5f;
                    break;
                }
            }
            attempts++;
        } while (collision && attempts < 20);

        bData.radius = newRadius;

        balloons.push_back(bData);
    }
}

void Tema3::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(6.0f, 5.0f, -10.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f));
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, mapTextures["soare"]);
    }
    float timeTotal = (float)Engine::GetElapsedTime();

    for (auto& b : balloons)
    {
        float angle = b.omega * timeTotal + b.offset;
        float x = b.radius * cos(angle);
        float z = b.radius * sin(angle);

        float yOsc = b.amplitude * sin(b.freq * timeTotal);

        glm::vec3 balloonCenter = glm::vec3(x, b.height + yOsc, z);

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, balloonCenter);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 1.2f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
            deformBalloon = 1;
            RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, b.texture);
            deformBalloon = 0;
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, balloonCenter);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 0.4f, 0.4f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.5f, 0.0f));
            RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["crate"]);
        }

        for (int conn = 0; conn < 4; conn++)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, balloonCenter);

            float angleConn = conn * 3.14159f / 2.0f;
            float offsetX = 0.2f * cos(angleConn);
            float offsetZ = 0.2f * sin(angleConn);

            modelMatrix = glm::translate(modelMatrix, glm::vec3(offsetX, 0.0f, offsetZ));

            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f, 1.0f, 0.02f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, 0.0f));

            RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["crate"]);
        }
    }
}

void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader,
    const glm::mat4& modelMatrix,
    Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int loc_mix = glGetUniformLocation(shader->program, "mixer");
    if (texture2) glUniform1i(loc_mix, 1);
    else          glUniform1i(loc_mix, 0);

    int loc_deform = glGetUniformLocation(shader->program, "u_deformBalon");
    glUniform1i(loc_deform, deformBalloon);

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_2"), 1);
    }

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(),
        static_cast<int>(mesh->indices.size()),
        GL_UNSIGNED_INT, 0);
}

Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    for (unsigned int i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }

    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
        0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    CheckOpenGLError();

    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema3::OnKeyPress(int key, int mods)
{
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
