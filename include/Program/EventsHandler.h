/**
* @brief
*
* @author  spjuanjoc
* @date    2020-08-20
*/

#ifndef PROGRAM_EVENTSHANDLER_H
#define PROGRAM_EVENTSHANDLER_H

#include <map>

namespace sf
{
class Event;
class RenderWindow;
}  // namespace sf

namespace Program
{
enum class KEY_NAMES : std::int32_t
{
  UNKNOWN   = -1,  ///< Unhandled key
  A         = 0,   ///< The A key
  B         = 1,   ///< The B key
  C         = 2,   ///< The C key
  D         = 3,   ///< The D key
  E         = 4,   ///< The E key
  F         = 5,   ///< The F key
  G         = 6,   ///< The G key
  H         = 7,   ///< The H key
  I         = 8,   ///< The I key
  J         = 9,   ///< The J key
  K         = 10,  ///< The K key
  L         = 11,  ///< The L key
  M         = 12,  ///< The M key
  N         = 13,  ///< The N key
  O         = 14,  ///< The O key
  P         = 15,  ///< The P key
  Q         = 16,  ///< The Q key
  R         = 17,  ///< The R key
  S         = 18,  ///< The S key
  T         = 19,  ///< The T key
  U         = 20,  ///< The U key
  V         = 21,  ///< The V key
  W         = 22,  ///< The W key
  X         = 23,  ///< The X key
  Y         = 24,  ///< The Y key
  Z         = 25,  ///< The Z key
  Num0      = 26,  ///< The 0 key
  Num1      = 27,  ///< The 1 key
  Num2      = 28,  ///< The 2 key
  Num3      = 29,  ///< The 3 key
  Num4      = 30,  ///< The 4 key
  Num5      = 31,  ///< The 5 key
  Num6      = 32,  ///< The 6 key
  Num7      = 33,  ///< The 7 key
  Num8      = 34,  ///< The 8 key
  Num9      = 35,  ///< The 9 key
  Escape    = 36,  ///< The Escape key
  LControl  = 37,  ///< The left Control key
  LShift    = 38,  ///< The left Shift key
  LAlt      = 39,  ///< The left Alt key
  LSystem   = 40,  ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
  RControl  = 41,  ///< The right Control key
  RShift    = 42,  ///< The right Shift key
  RAlt      = 43,  ///< The right Alt key
  RSystem   = 44,  ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
  Menu      = 45,  ///< The Menu key
  LBracket  = 46,  ///< The [ key
  RBracket  = 47,  ///< The ] key
  Enhe      = 48,  ///< The ; key (Ñ is ES)
  Comma     = 49,  ///< The , key
  Period    = 50,  ///< The . key
  Quote     = 51,  ///< The ' key
  Slash     = 52,  ///< The / key
  Backslash = 53,  ///< The \ key
  Tilde     = 54,  ///< The ~ key
  Equal     = 55,  ///< The = key
  Hyphen    = 56,  ///< The - key (hyphen)
  Space     = 57,  ///< The Space key
  Enter     = 58,  ///< The Enter/Return keys
  Backspace = 59,  ///< The Backspace key
  Tab       = 60,  ///< The Tabulation key
  PageUp    = 61,  ///< The Page up key
  PageDown  = 62,  ///< The Page down key
  End       = 63,  ///< The End key
  Home      = 64,  ///< The Home key
  Insert    = 65,  ///< The Insert key
  Delete    = 66,  ///< The Delete key
  Add       = 67,  ///< The + key
  Subtract  = 68,  ///< The - key (minus, usually from numpad)
  Multiply  = 69,  ///< The * key
  Divide    = 70,  ///< The / key
  Left      = 71,  ///< Left arrow
  Right     = 72,  ///< Right arrow
  Up        = 73,  ///< Up arrow
  Down      = 74,  ///< Down arrow
  Numpad0   = 75,  ///< The numpad 0 key
  Numpad1   = 76,  ///< The numpad 1 key
  Numpad2   = 77,  ///< The numpad 2 key
  Numpad3   = 78,  ///< The numpad 3 key
  Numpad4   = 79,  ///< The numpad 4 key
  Numpad5   = 80,  ///< The numpad 5 key
  Numpad6   = 81,  ///< The numpad 6 key
  Numpad7   = 82,  ///< The numpad 7 key
  Numpad8   = 83,  ///< The numpad 8 key
  Numpad9   = 84,  ///< The numpad 9 key
  F1        = 85,  ///< The F1 key
  F2        = 86,  ///< The F2 key
  F3        = 87,  ///< The F3 key
  F4        = 88,  ///< The F4 key
  F5        = 89,  ///< The F5 key
  F6        = 90,  ///< The F6 key
  F7        = 91,  ///< The F7 key
  F8        = 92,  ///< The F8 key
  F9        = 93,  ///< The F9 key
  F10       = 94,  ///< The F10 key
  F11       = 95,  ///< The F11 key
  F12       = 96,  ///< The F12 key
  F13       = 97,  ///< The F13 key
  F14       = 98,  ///< The F14 key
  F15       = 99,  ///< The F15 key
  Pause     = 100  ///< The Pause key
};

const std::map<KEY_NAMES, std::string_view> KEY_STRINGS{
  {KEY_NAMES::UNKNOWN, " "},            ///< Unhandled key
  {KEY_NAMES::A, "A"},                  ///< The A key
  {KEY_NAMES::B, "B"},                  ///< The B key
  {KEY_NAMES::C, "C"},                  ///< The C key
  {KEY_NAMES::D, "D"},                  ///< The D key
  {KEY_NAMES::E, "E"},                  ///< The E key
  {KEY_NAMES::F, "F"},                  ///< The F key
  {KEY_NAMES::G, "G"},                  ///< The G key
  {KEY_NAMES::H, "H"},                  ///< The H key
  {KEY_NAMES::I, "I"},                  ///< The I key
  {KEY_NAMES::J, "J"},                  ///< The J key
  {KEY_NAMES::K, "K"},                  ///< The K key
  {KEY_NAMES::L, "L"},                  ///< The L key
  {KEY_NAMES::M, "M"},                  ///< The M key
  {KEY_NAMES::N, "N"},                  ///< The N key
  {KEY_NAMES::O, "O"},                  ///< The O key
  {KEY_NAMES::P, "P"},                  ///< The P key
  {KEY_NAMES::Q, "Q"},                  ///< The Q key
  {KEY_NAMES::R, "R"},                  ///< The R key
  {KEY_NAMES::S, "S"},                  ///< The S key
  {KEY_NAMES::T, "T"},                  ///< The T key
  {KEY_NAMES::U, "U"},                  ///< The U key
  {KEY_NAMES::V, "V"},                  ///< The V key
  {KEY_NAMES::W, "W"},                  ///< The W key
  {KEY_NAMES::X, "X"},                  ///< The X key
  {KEY_NAMES::Y, "Y"},                  ///< The Y key
  {KEY_NAMES::Z, "Z"},                  ///< The Z key
  {KEY_NAMES::Num0, "Num0"},            ///< The 0 key
  {KEY_NAMES::Num1, "Num1"},            ///< The 1 key
  {KEY_NAMES::Num2, "Num2"},            ///< The 2 key
  {KEY_NAMES::Num3, "Num3"},            ///< The 3 key
  {KEY_NAMES::Num4, "Num4"},            ///< The 4 key
  {KEY_NAMES::Num5, "Num5"},            ///< The 5 key
  {KEY_NAMES::Num6, "Num6"},            ///< The 6 key
  {KEY_NAMES::Num7, "Num7"},            ///< The 7 key
  {KEY_NAMES::Num8, "Num8"},            ///< The 8 key
  {KEY_NAMES::Num9, "Num9"},            ///< The 9 key
  {KEY_NAMES::Escape, "Escape"},        ///< The Escape key
  {KEY_NAMES::LControl, "LControl"},    ///< The left Control key
  {KEY_NAMES::LShift, "LShift"},        ///< The left Shift key
  {KEY_NAMES::LAlt, "LAlt"},            ///< The left Alt key
  {KEY_NAMES::LSystem, "LSystem"},      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
  {KEY_NAMES::RControl, "RControl"},    ///< The right Control key
  {KEY_NAMES::RShift, "RShift"},        ///< The right Shift key
  {KEY_NAMES::RAlt, "RAlt"},            ///< The right Alt key
  {KEY_NAMES::RSystem, "RSystem"},      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
  {KEY_NAMES::Menu, "Menu"},            ///< The Menu key
  {KEY_NAMES::LBracket, "LBracket"},    ///< The [ key
  {KEY_NAMES::RBracket, "RBracket"},    ///< The ] key
  {KEY_NAMES::Enhe, "Ñ"},               ///< The ; key (Ñ is ES)
  {KEY_NAMES::Comma, "Comma"},          ///< The , key
  {KEY_NAMES::Period, "Period"},        ///< The . key
  {KEY_NAMES::Quote, "Quote"},          ///< The ' key
  {KEY_NAMES::Slash, "Slash"},          ///< The / key
  {KEY_NAMES::Backslash, "Backslash"},  ///< The \ key
  {KEY_NAMES::Tilde, "Tilde"},          ///< The ~ key
  {KEY_NAMES::Equal, "Equal"},          ///< The = key
  {KEY_NAMES::Hyphen, "Hyphen"},        ///< The - key (hyphen)
  {KEY_NAMES::Space, "Space"},          ///< The Space key
  {KEY_NAMES::Enter, "Enter"},          ///< The Enter/Return keys
  {KEY_NAMES::Backspace, "Backspace"},  ///< The Backspace key
  {KEY_NAMES::Tab, "Tab"},              ///< The Tabulation key
  {KEY_NAMES::PageUp, "PageUp"},        ///< The Page up key
  {KEY_NAMES::PageDown, "PageDown"},    ///< The Page down key
  {KEY_NAMES::End, "End"},              ///< The End key
  {KEY_NAMES::Home, "Home"},            ///< The Home key
  {KEY_NAMES::Insert, "Insert"},        ///< The Insert key
  {KEY_NAMES::Delete, "Delete"},        ///< The Delete key
  {KEY_NAMES::Add, "Add"},              ///< The + key
  {KEY_NAMES::Subtract, "Subtract"},    ///< The - key (minus, usually from numpad)
  {KEY_NAMES::Multiply, "Multiply"},    ///< The * key
  {KEY_NAMES::Divide, "Divide"},        ///< The / key
  {KEY_NAMES::Left, "Left"},            ///< Left arrow
  {KEY_NAMES::Right, "Right"},          ///< Right arrow
  {KEY_NAMES::Up, "Up"},                ///< Up arrow
  {KEY_NAMES::Down, "Down"},            ///< Down arrow
  {KEY_NAMES::Numpad0, "Numpad0"},      ///< The numpad 0 key
  {KEY_NAMES::Numpad1, "Numpad1"},      ///< The numpad 1 key
  {KEY_NAMES::Numpad2, "Numpad2"},      ///< The numpad 2 key
  {KEY_NAMES::Numpad3, "Numpad3"},      ///< The numpad 3 key
  {KEY_NAMES::Numpad4, "Numpad4"},      ///< The numpad 4 key
  {KEY_NAMES::Numpad5, "Numpad5"},      ///< The numpad 5 key
  {KEY_NAMES::Numpad6, "Numpad6"},      ///< The numpad 6 key
  {KEY_NAMES::Numpad7, "Numpad7"},      ///< The numpad 7 key
  {KEY_NAMES::Numpad8, "Numpad8"},      ///< The numpad 8 key
  {KEY_NAMES::Numpad9, "Numpad9"},      ///< The numpad 9 key
  {KEY_NAMES::F1, "F1"},                ///< The F1 key
  {KEY_NAMES::F2, "F2"},                ///< The F2 key
  {KEY_NAMES::F3, "F3"},                ///< The F3 key
  {KEY_NAMES::F4, "F4"},                ///< The F4 key
  {KEY_NAMES::F5, "F5"},                ///< The F5 key
  {KEY_NAMES::F6, "F6"},                ///< The F6 key
  {KEY_NAMES::F7, "F7"},                ///< The F7 key
  {KEY_NAMES::F8, "F8"},                ///< The F8 key
  {KEY_NAMES::F9, "F9"},                ///< The F9 key
  {KEY_NAMES::F10, "F10"},              ///< The F10 key
  {KEY_NAMES::F11, "F11"},              ///< The F11 key
  {KEY_NAMES::F12, "F12"},              ///< The F12 key
  {KEY_NAMES::F13, "F13"},              ///< The F13 key
  {KEY_NAMES::F14, "F14"},              ///< The F14 key
  {KEY_NAMES::F15, "F15"},              ///< The F15 key
  {KEY_NAMES::Pause, "Pause"},          ///< The Pause key
};

class EventsHandler
{
public:
  void poll(sf::RenderWindow& window);

  [[nodiscard]]
  bool isRunning() const
  {
    return m_isRunning;
  }

  void pause()
  {
    m_isRunning = false;
  }

  [[nodiscard]]
  KEY_NAMES pressedKey() const
  {
    return static_cast<KEY_NAMES>(m_key);
  }

  [[nodiscard]]
  std::string_view pressedKeyName() const
  {
    return Program::KEY_STRINGS.at(m_key);
  }

private:
  KEY_NAMES m_key{-1};
  bool isAlt{};      ///< Is the Alt key pressed?
  bool isControl{};  ///< Is the Control key pressed?
  bool isShift{};    ///< Is the Shift key pressed?
  bool isSystem{};   ///< Is the System key pressed?
  bool isClick{};
  bool m_isRunning{false};
};

}  // namespace Program

#endif /* PROGRAM_EVENTSHANDLER_H */
