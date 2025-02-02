#pragma once
#include "IMF_PCH.h"

#include "GameContext.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"


class GameScene : public GameLayer
{
private:
    std::vector<float> vertices =
    {   // positions            // colors
        -0.5f, -0.5f, 0.0f,     0.5f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 0.5f, 1.0f, 1.0f,
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.5f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.5f, 1.0f, 1.0f, 1.0f
    };
    std::vector<uint32_t> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<VertexBuffer> m_VB;
    std::shared_ptr<IndexBuffer> m_IB;
    std::shared_ptr<VertexArray> m_VA;

    uint32_t m_VBID;
    uint32_t m_IBID;
    uint32_t m_VAID;

    std::vector<std::string> m_shaderSources = 
    {
        "imClient/assets/shaders/2DShader.vertex.glsl",
        "imClient/assets/shaders/2DShader.fragment.glsl"
    };
    std::shared_ptr<Shader> m_shader;

public:
    GameScene();
    void OnEvent(const SDL_Event* event) override;
    void OnStart() override;
    void OnUpdate(float dt) override;
};