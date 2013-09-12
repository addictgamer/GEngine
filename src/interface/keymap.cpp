/* Please refer to license.txt */

/*
 * Shamelessly taken from: http://www.cegui.org.uk/wiki/index.php/SFML_to_CEGUI_keytable :)
 * By the way, thanks a ton to whoever made that. SFML 0.8 documentation is severely lacking.
 */

#include "interface.hpp"

namespace mui
{

void Interface::mapSFMLKeysToCEGUI()
{
	sfml_cegui_keymap[sf::Keyboard::A]			= CEGUI::Key::A;
	sfml_cegui_keymap[sf::Keyboard::B]			= CEGUI::Key::B;
	sfml_cegui_keymap[sf::Keyboard::C]			= CEGUI::Key::C;
	sfml_cegui_keymap[sf::Keyboard::D]			= CEGUI::Key::D;
	sfml_cegui_keymap[sf::Keyboard::E]			= CEGUI::Key::E;
	sfml_cegui_keymap[sf::Keyboard::F]			= CEGUI::Key::F;
	sfml_cegui_keymap[sf::Keyboard::G]			= CEGUI::Key::G;
	sfml_cegui_keymap[sf::Keyboard::H]			= CEGUI::Key::H;
	sfml_cegui_keymap[sf::Keyboard::I]			= CEGUI::Key::I;
	sfml_cegui_keymap[sf::Keyboard::J]			= CEGUI::Key::J;
	sfml_cegui_keymap[sf::Keyboard::K]			= CEGUI::Key::K;
	sfml_cegui_keymap[sf::Keyboard::L]			= CEGUI::Key::L;
	sfml_cegui_keymap[sf::Keyboard::M]			= CEGUI::Key::M;
	sfml_cegui_keymap[sf::Keyboard::N]			= CEGUI::Key::N;
	sfml_cegui_keymap[sf::Keyboard::O]			= CEGUI::Key::O;
	sfml_cegui_keymap[sf::Keyboard::P]			= CEGUI::Key::P;
	sfml_cegui_keymap[sf::Keyboard::Q]			= CEGUI::Key::Q;
	sfml_cegui_keymap[sf::Keyboard::R]			= CEGUI::Key::R;
	sfml_cegui_keymap[sf::Keyboard::S]			= CEGUI::Key::S;
	sfml_cegui_keymap[sf::Keyboard::T]			= CEGUI::Key::T;
	sfml_cegui_keymap[sf::Keyboard::U]			= CEGUI::Key::U;
	sfml_cegui_keymap[sf::Keyboard::V]			= CEGUI::Key::V;
	sfml_cegui_keymap[sf::Keyboard::W]			= CEGUI::Key::W;
	sfml_cegui_keymap[sf::Keyboard::X]			= CEGUI::Key::X;
	sfml_cegui_keymap[sf::Keyboard::Y]			= CEGUI::Key::Y;
	sfml_cegui_keymap[sf::Keyboard::Z]			= CEGUI::Key::Z;
	sfml_cegui_keymap[sf::Keyboard::Num0]			= CEGUI::Key::Zero;
	sfml_cegui_keymap[sf::Keyboard::Num1]			= CEGUI::Key::One;
	sfml_cegui_keymap[sf::Keyboard::Num2]			= CEGUI::Key::Two;
	sfml_cegui_keymap[sf::Keyboard::Num3]			= CEGUI::Key::Three;
	sfml_cegui_keymap[sf::Keyboard::Num4]			= CEGUI::Key::Four;
	sfml_cegui_keymap[sf::Keyboard::Num5]			= CEGUI::Key::Five;
	sfml_cegui_keymap[sf::Keyboard::Num6]			= CEGUI::Key::Six;
	sfml_cegui_keymap[sf::Keyboard::Num7]			= CEGUI::Key::Seven;
	sfml_cegui_keymap[sf::Keyboard::Num8]			= CEGUI::Key::Eight;
	sfml_cegui_keymap[sf::Keyboard::Num9]			= CEGUI::Key::Nine;
	sfml_cegui_keymap[sf::Keyboard::Escape]			= CEGUI::Key::Escape;
	sfml_cegui_keymap[sf::Keyboard::LControl]		= CEGUI::Key::LeftControl;
	sfml_cegui_keymap[sf::Keyboard::LShift]			= CEGUI::Key::LeftShift;
	sfml_cegui_keymap[sf::Keyboard::LAlt]			= CEGUI::Key::LeftAlt;
	sfml_cegui_keymap[sf::Keyboard::LSystem]		= CEGUI::Key::LeftWindows;
	sfml_cegui_keymap[sf::Keyboard::RControl]		= CEGUI::Key::RightControl;
	sfml_cegui_keymap[sf::Keyboard::RShift]			= CEGUI::Key::RightShift;
	sfml_cegui_keymap[sf::Keyboard::RAlt]			= CEGUI::Key::RightAlt;
	sfml_cegui_keymap[sf::Keyboard::RSystem]		= CEGUI::Key::RightWindows;
	//sfml_cegui_keymap[sf::Keyboard::Menu]			= CEGUI::Key: --Dunno what this is
	sfml_cegui_keymap[sf::Keyboard::LBracket]		= CEGUI::Key::LeftBracket;
	sfml_cegui_keymap[sf::Keyboard::RBracket]		= CEGUI::Key::RightBracket;
	sfml_cegui_keymap[sf::Keyboard::SemiColon]		= CEGUI::Key::Semicolon;
	sfml_cegui_keymap[sf::Keyboard::Comma]			= CEGUI::Key::Comma;
	sfml_cegui_keymap[sf::Keyboard::Period]			= CEGUI::Key::Period;
	sfml_cegui_keymap[sf::Keyboard::Quote]			= CEGUI::Key::Apostrophe;
	sfml_cegui_keymap[sf::Keyboard::Slash]			= CEGUI::Key::Slash;
	sfml_cegui_keymap[sf::Keyboard::BackSlash]		= CEGUI::Key::Backslash;
	sfml_cegui_keymap[sf::Keyboard::Tilde]			= CEGUI::Key::Grave;
	sfml_cegui_keymap[sf::Keyboard::Equal]			= CEGUI::Key::Equals;
	sfml_cegui_keymap[sf::Keyboard::Dash]			= CEGUI::Key::Minus;
	sfml_cegui_keymap[sf::Keyboard::Space]			= CEGUI::Key::Space;
	sfml_cegui_keymap[sf::Keyboard::Return]			= CEGUI::Key::Return;
	sfml_cegui_keymap[sf::Keyboard::BackSpace]		= CEGUI::Key::Backspace;
	sfml_cegui_keymap[sf::Keyboard::Tab]			= CEGUI::Key::Tab;
	sfml_cegui_keymap[sf::Keyboard::PageUp]			= CEGUI::Key::PageUp;
	sfml_cegui_keymap[sf::Keyboard::PageDown]		= CEGUI::Key::PageDown;
	sfml_cegui_keymap[sf::Keyboard::End]			= CEGUI::Key::End;
	sfml_cegui_keymap[sf::Keyboard::Home]			= CEGUI::Key::Home;
	sfml_cegui_keymap[sf::Keyboard::Insert]			= CEGUI::Key::Insert;
	sfml_cegui_keymap[sf::Keyboard::Delete]			= CEGUI::Key::Delete;
	sfml_cegui_keymap[sf::Keyboard::Add]			= CEGUI::Key::Add;
	sfml_cegui_keymap[sf::Keyboard::Subtract]		= CEGUI::Key::Subtract;
	sfml_cegui_keymap[sf::Keyboard::Multiply]		= CEGUI::Key::Multiply;
	sfml_cegui_keymap[sf::Keyboard::Divide]			= CEGUI::Key::Divide;
	sfml_cegui_keymap[sf::Keyboard::Left]			= CEGUI::Key::ArrowLeft;
	sfml_cegui_keymap[sf::Keyboard::Right]			= CEGUI::Key::ArrowRight;
	sfml_cegui_keymap[sf::Keyboard::Up]			= CEGUI::Key::ArrowUp;
	sfml_cegui_keymap[sf::Keyboard::Down]			= CEGUI::Key::ArrowDown;
	sfml_cegui_keymap[sf::Keyboard::Numpad0] 		= CEGUI::Key::Numpad0;
	sfml_cegui_keymap[sf::Keyboard::Numpad1] 		= CEGUI::Key::Numpad1;
	sfml_cegui_keymap[sf::Keyboard::Numpad2] 		= CEGUI::Key::Numpad2;
	sfml_cegui_keymap[sf::Keyboard::Numpad3] 		= CEGUI::Key::Numpad3;
	sfml_cegui_keymap[sf::Keyboard::Numpad4] 		= CEGUI::Key::Numpad4;
	sfml_cegui_keymap[sf::Keyboard::Numpad5] 		= CEGUI::Key::Numpad5;
	sfml_cegui_keymap[sf::Keyboard::Numpad6] 		= CEGUI::Key::Numpad6;
	sfml_cegui_keymap[sf::Keyboard::Numpad7] 		= CEGUI::Key::Numpad7;
	sfml_cegui_keymap[sf::Keyboard::Numpad8] 		= CEGUI::Key::Numpad8;
	sfml_cegui_keymap[sf::Keyboard::Numpad9] 		= CEGUI::Key::Numpad9;
	sfml_cegui_keymap[sf::Keyboard::F1]			= CEGUI::Key::F1;
	sfml_cegui_keymap[sf::Keyboard::F2]			= CEGUI::Key::F2;
	sfml_cegui_keymap[sf::Keyboard::F3]			= CEGUI::Key::F3;
	sfml_cegui_keymap[sf::Keyboard::F4]			= CEGUI::Key::F4;
	sfml_cegui_keymap[sf::Keyboard::F5]			= CEGUI::Key::F5;
	sfml_cegui_keymap[sf::Keyboard::F6]			= CEGUI::Key::F6;
	sfml_cegui_keymap[sf::Keyboard::F7]			= CEGUI::Key::F7;
	sfml_cegui_keymap[sf::Keyboard::F8]			= CEGUI::Key::F8;
	sfml_cegui_keymap[sf::Keyboard::F9]			= CEGUI::Key::F9;
	sfml_cegui_keymap[sf::Keyboard::F10]			= CEGUI::Key::F10;
	sfml_cegui_keymap[sf::Keyboard::F11]			= CEGUI::Key::F11;
	sfml_cegui_keymap[sf::Keyboard::F12]			= CEGUI::Key::F12;
	sfml_cegui_keymap[sf::Keyboard::F13]			= CEGUI::Key::F13;
	sfml_cegui_keymap[sf::Keyboard::F14]			= CEGUI::Key::F14;
	sfml_cegui_keymap[sf::Keyboard::F15]			= CEGUI::Key::F15;
	sfml_cegui_keymap[sf::Keyboard::Pause]			= CEGUI::Key::Pause;
}

void Interface::mapSFMLMouseToCEGUI()
{
	sfml_cegui_mousemap[sf::Mouse::Left]			= CEGUI::LeftButton;
	sfml_cegui_mousemap[sf::Mouse::Right]			= CEGUI::RightButton;
	sfml_cegui_mousemap[sf::Mouse::Middle]			= CEGUI::MiddleButton;
	sfml_cegui_mousemap[sf::Mouse::XButton1]		= CEGUI::X1Button;
	sfml_cegui_mousemap[sf::Mouse::XButton2]		= CEGUI::X2Button;
}

} //namespace mui
