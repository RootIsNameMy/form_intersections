#include "game.h"

#include "glad/glad.h"
Game::Game() {}

void Game::Init() {
  renderer_.Init();
  std::string name = "Tilen KorenTilen Koren";
  int width = arc::Engine::window().width();
  int height = arc::Engine::window().height();
  camera_.SetProjection((float)width / (float)height, 1);
  glGenFramebuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

  glGenTextures(1, &color_buffer_);
  glBindTexture(GL_TEXTURE_2D, color_buffer_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  // attach it to currently bound framebuffer object
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         color_buffer_, 0);
  arc_core_assert(
      glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
      "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  shader_.Create("simple_shader");
  vertex_array_.Create();
  vertex_buffer_.set_layout({
      {arc::ShaderDataType::Float3, "a_position"},
      {arc::ShaderDataType::Float2, "a_tex_coord"},
  });
  uint indices[6];

  uint vertex_index = 0;
  for (int i = 0; i < 6; i += 6) {
    indices[i + 0] = vertex_index;
    indices[i + 1] = vertex_index + 1;
    indices[i + 2] = vertex_index + 2;

    indices[i + 3] = vertex_index + 2;
    indices[i + 4] = vertex_index + 3;
    indices[i + 5] = vertex_index;
    vertex_index += 4;
  }

  index_buffer_.Create(indices, 6);
  vertex_array_.set_index_buffer(index_buffer_);

  arc::VertexMarch vertices[4];
  float aspect =
      arc::Engine::window().width() / (float)arc::Engine::window().height();
  vertices[0].pos = {-1, -1, 0};
  vertices[1].pos = {1, -1, 0};
  vertices[2].pos = {1, 1, 0};
  vertices[3].pos = {-1, 1, 0};

  vertices[0].tex_coord = {-aspect, -1};
  vertices[1].tex_coord = {aspect, -1};
  vertices[2].tex_coord = {aspect, 1};
  vertices[3].tex_coord = {-aspect, 1};
  vertex_buffer_.Create((float*)vertices, 4);
  vertex_array_.AddVertexBuffer(vertex_buffer_);
  camera_.SetView({});
}

void Game::Dispose() { renderer_.Destroy(); }

void Game::Update() {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
  {
    arc::RenderCommand::SetClearColor({0.25, 0.25, 0.75, 1});
    arc::RenderCommand::Clear();
    renderer_.Begin();
    {}
    renderer_.End();
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  arc::RenderCommand::SetClearColor({0.25, 0.25, 0.75, 1});
  arc::RenderCommand::Clear();
  shader_.Bind();
  vertex_array_.Bind();
  glBindTexture(GL_TEXTURE_2D, color_buffer_);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  shader_.Unbind();
}

void Game::ImGuiRender() {
  /* ImGui::Begin("ImGui window"); */

  /* ImGui::End(); */
}
