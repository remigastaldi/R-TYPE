#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class GUI
{
public:
	//imgui-SFML overload
	static void	GUIInit(sf::RenderTarget& target, bool loadDefaultFont = true) { return ImGui::SFML::Init(target, loadDefaultFont); }
	static void	GUIProcessEvent(const sf::Event& event) { return ImGui::SFML::ProcessEvent(event); }
	static void	GUIUpdate(sf::RenderWindow& window, sf::Time dt) { return ImGui::SFML::Update(window, dt); }
	static void	GUIUpdate(sf::Window& window, sf::RenderTarget& target, sf::Time dt) { return ImGui::SFML::Update(window, target, dt); }
	static void	GUIUpdate(const sf::Vector2i& mousePos, const sf::Vector2f& displaySize, sf::Time dt) { return ImGui::SFML::Update(mousePos, displaySize, dt); }
	static void	GUIRender(sf::RenderTarget& target) { return ImGui::SFML::Render(target); }
	static void	GUIShutdown() { return ImGui::SFML::Shutdown(); }
	static void	GUIUpdateFontTexture() { return ImGui::SFML::UpdateFontTexture(); }
	static sf::Texture& GUIGetFontTexture() { return ImGui::SFML::GetFontTexture(); }
	static void	GUIImage(const sf::Texture& texture, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent) { return ImGui::Image(texture, tintColor, borderColor); }
	static void	GUIImage(const sf::Texture& texture, const sf::Vector2f& size, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent) { return ImGui::Image(texture, size, tintColor, borderColor); }
	static void	GUIImage(const sf::Texture& texture, const sf::FloatRect& textureRect, const sf::Color& tintColor = sf::Color::White, const sf::Color& bordercolor = sf::Color::Transparent) { return ImGui::Image(texture, textureRect, tintColor, bordercolor); }
	static void	GUIImage(const sf::Texture& texture, const sf::Vector2f& size, const sf::FloatRect& textureRect, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent) { return ImGui::Image(texture, size, textureRect, tintColor, borderColor); }
	static void	GUIImage(const sf::Sprite& sprite, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent) { return ImGui::Image(sprite, tintColor, borderColor); }
	static void	GUIImage(const sf::Sprite& sprite, const sf::Vector2f& size, const sf::Color& tintColor = sf::Color::White, const sf::Color& borderColor = sf::Color::Transparent) { return ImGui::Image(sprite, size, tintColor, borderColor); }
	static bool	GUIImageButton(const sf::Texture& texture, const int framePadding = -1, const sf::Color& bgColor = sf::Color::Transparent, const sf::Color& tintColor = sf::Color::White) { return ImGui::ImageButton(texture, framePadding, bgColor, tintColor); }
	static bool	GUIImageButton(const sf::Texture& texture, const sf::Vector2f& size, const int framePadding = -1, const sf::Color& bgColor = sf::Color::Transparent, const sf::Color& tintColor = sf::Color::White) { return ImGui::ImageButton(texture, size, framePadding, bgColor, tintColor); }
	static bool	GUIImageButton(const sf::Sprite& sprite, const int framePadding = -1, const sf::Color& bgColor = sf::Color::Transparent, const sf::Color& tintColor = sf::Color::White) { return ImGui::ImageButton(sprite, framePadding, bgColor, tintColor); }
	static bool	GUIImageButton(const sf::Sprite& sprite, const sf::Vector2f& size, const int framePadding = -1, const sf::Color& bgColor = sf::Color::Transparent, const sf::Color& tintColor = sf::Color::White) { return ImGui::ImageButton(sprite, size, framePadding, bgColor, tintColor); }
	static void	GUIDrawLine(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& col, float thickness = 1.0f) { return ImGui::DrawLine(a, b, col, thickness); }
	static void	GUIDrawRect(const sf::FloatRect& rect, const sf::Color& color, float rounding = 0.0f, int rouding_corners = 0x0F, float thickness = 1.0f) { return ImGui::DrawRect(rect, color, rounding, rouding_corners, thickness); }
	static void	GUIDrawRectFilled(const sf::FloatRect& rect, const sf::Color& color, float rounding = 0.0f, int rounding_corners = 0x0F) { return ImGui::DrawRectFilled(rect, color, rounding, rounding_corners); }

	//imgui overload
	static bool	GUIBegin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0) { return ImGui::Begin(name, p_open, flags); }
	static void	GUIEnd() { return ImGui::End(); }
	static bool	GUIBeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags extra_flags = 0) { return ImGui::BeginChild(str_id, size, border, extra_flags); }
	static void	GUIEndChild() { return ImGui::EndChild(); }
	static bool GUIButton(const char* label, const ImVec2& size = ImVec2(0, 0)) { return ImGui::Button(label, size); }
	static bool GUIColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0) { return ImGui::ColorEdit3(label, col, flags); }
	static bool GUIInputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = NULL, void* user_data = NULL) { return ImGui::InputText(label, buf, buf_size, flags, callback, user_data); }


protected:

private:

};