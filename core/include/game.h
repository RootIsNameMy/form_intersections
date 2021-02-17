//
// Created by adolin on 21. 12. 20.
//

#ifndef ARC_ENGINE_BATTLEMAPAPP_H
#define ARC_ENGINE_BATTLEMAPAPP_H

#include "engine_includes.h"

class Game : public arc::Application {
 public:
  Game();
  void Init() override;
  void Dispose() override;
  void Update() override;
  void ImGuiRender() override;

 private:
  arc::MarchRenderer renderer_;
  arc::OrthographicCamera camera_;

  uint frame_buffer_, color_buffer_;
  arc::Shader shader_;
  arc::VertexArray vertex_array_;
  arc::IndexBuffer index_buffer_;
  arc::VertexBuffer vertex_buffer_;
};

#endif  // ARC_ENGINE_BATTLEMAPAPP_H
