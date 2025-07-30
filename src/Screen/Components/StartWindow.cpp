/**
 * @brief Defines the start window class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#include "Screen/Components/StartWindow.h"
#include "Screen/Components/Constants.h"

#include "Core/Logging/Logger.h"

namespace Screen::Components
{

StartWindow::StartWindow()
{
  Logger::Info(">>StartWindow");
  loadTexturesFiles();
  setTextures();
  Logger::Info("<<StartWindow");
}

void
StartWindow::draw(sf::RenderWindow& window)
{
  Logger::Debug(">>draw");
  const auto  window_size = window.getSize();
  const float window_x    = static_cast<float>(window_size.x) / HALF_DIVISOR;
  const float texture_x   = static_cast<float>(m_texture.getSize().x) / HALF_DIVISOR;
  const float window_y    = static_cast<float>(window_size.y) / HALF_DIVISOR;
  const float texture_y   = static_cast<float>(m_texture.getSize().y) / HALF_DIVISOR;
  const float sprite_x    = window_x - texture_x;
  const float sprite_y    = window_y - texture_y;

  m_sprite.setPosition(sprite_x, sprite_y);
  setText({ window_x, window_y });

  window.draw(m_sprite);
  Logger::Debug("<<draw");
}

void
StartWindow::loadTexturesFiles()
{
  Logger::Debug(">>loadTexturesFiles");
  m_texture.loadFromFile(START_FILENAME);
  Logger::Debug("<<loadTexturesFiles");
}

void
StartWindow::setTextures()
{
  Logger::Debug(">>setTextures");
  m_sprite.setTexture(m_texture);
  Logger::Debug("<<setTextures");
}

void
StartWindow::setText(const ImVec2& origin)
{
  Logger::Debug(">>setText");
  constexpr std::string_view label        = "Overlay Start Window";
  constexpr float            transparency = 0.75F;
  constexpr float            window_x     = 220.0F;
  constexpr float            window_y     = 40.0F;
  const float                texture_y    = static_cast<float>(m_texture.getSize().y);
  const ImVec2               position { origin.x - (window_x / HALF_DIVISOR), origin.y + (texture_y / HALF_DIVISOR) };
  ImGuiWindowFlags           flags = ImGuiWindowFlags_NoDecoration;
  bool                       is_window_active {};

  ImGui::SetNextWindowBgAlpha(transparency);
  ImGui::SetNextWindowPos(position, ImGuiCond_Appearing);
  ImGui::SetNextWindowSize({ window_x, window_y });

  if (ImGui::Begin(label.data(), &is_window_active, flags))
  {
    ImGui::TextUnformatted(m_text.data());
  }

  ImGui::End();
  Logger::Debug("<<setText");
}

}  // namespace Game::Components
