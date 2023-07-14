/**
 * @brief Defines ImGui boxes.
 *
 * @author  spjuanjoc
 * @date    2021-11-26
 */

#ifndef CORE_BOXES_H
#define CORE_BOXES_H

#include <imgui.h>

/**
 * Adds a text window with the regular decoration
 *
 * @param label The window id.
 * @param data  The text to show.
 */
//static void addTextBox(const std::string& label, const std::string& data)
//{
//  ImGui::Begin(label.c_str());
//  ImGui::TextUnformatted(data.c_str());
//  ImGui::End();
//}

/**
 * Adds a box window with no decoration
 *
 * @param label The window id.
 * @param data The text to show.
 */
//static void addOverlayBox(const std::string& label, const std::string& data)
//{
//  ImVec2         window_pos{0,0};
//  constexpr auto transparency = 0.25F;
//  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration;
//
//  ImGui::SetNextWindowBgAlpha(transparency);
//  ImGui::SetNextWindowPos(window_pos, ImGuiCond_Appearing);
//  ImGui::SetNextWindowSize({480, 720});
//
//  if (ImGui::Begin(label.c_str(), nullptr, window_flags))
//  {
//    ImGui::TextUnformatted(data.c_str());
//  }
//
//  ImGui::End();
//}

#endif /* CORE_BOXES_H */
