#include "IMF_PCH.h"

#include "Game.h"

// @TEMP
#include <glad/glad.h>
#include <SDL3/SDL_events.h>


GameScene::GameScene()
{
    m_shader = Shader::CreateShader(m_shaderSources);
    m_VA = VertexArray::Create();
    m_IB = IndexBuffer::Create(indices.data(), indices.size());
    m_VB = VertexBuffer::Create(
        vertices.data(), vertices.size() * sizeof(float)
    );
}

void GameScene::OnEvent(const SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_EVENT_KEY_DOWN:
            switch(event->key.scancode)
            {
                case SDL_SCANCODE_W:
                    std::cout << "HEHEH" << std::endl;
                break;
            }
        break;
    }
}

void GameScene::OnStart()
{

}

void GameScene::OnUpdate(float dt)
{
    m_shader->Bind();
    m_VB->Bind();
    m_VA->Bind();
    m_IB->Bind();
    m_VB->SetBufferLayout({
        {AttribType::Vec3},
        {AttribType::Vec4}
    });
    
    m_VA->AddVertexBuffer(m_VB);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}