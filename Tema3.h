#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "components/simple_scene.h"
#include "components/transform.h"

namespace m1
{
    struct BalloonData;

    class Tema3 : public gfxc::SimpleScene
    {
    public:
        Tema3();
        ~Tema3();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,
            Texture2D* texture1 = nullptr, Texture2D* texture2 = nullptr);
        Texture2D* CreateRandomTexture(unsigned int width, unsigned int height);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        std::unordered_map<std::string, Texture2D*> mapTextures;

        std::vector<BalloonData> balloons;

        int deformBalloon = 0;
    };

    struct BalloonData {
        Texture2D* texture;
        float radius;
        float omega;
        float height;
        float amplitude;
        float freq;
        float offset;

        glm::vec3 axis;     
        glm::vec3 position;  
    };
}   // namespace m1
