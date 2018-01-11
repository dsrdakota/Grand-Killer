#pragma once

#include <SFML/Graphics.hpp>

class Keyboard
{
public:

	~Keyboard();

	Keyboard(const Keyboard &) = delete;
	void operator=(const Keyboard &) = delete;

	inline static Keyboard& Instance()
	{
		static Keyboard keyboard;
		return keyboard;
	}

	enum class Keys
	{
		Esc,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		PrintScreen,
		ScrollLock,
		Pause,
		Tilde,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,
		Dash,
		Equal,
		BackSpace,
		Insert,
		Home,
		PageUp,
		NumLock,
		Divide,
		Multiply,
		Subtract,
		Tab,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		LBracket,
		RBracket,
		Backslash,
		Delete,
		End,
		PageDown,
		Numpad7,
		Numpad8,
		Numpad9,
		Add,
		CapsLock,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		SemiColon,
		Quote,
		Enter,
		Numpad4,
		Numpad5,
		Numpad6,
		LShift,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		Period,
		Slash,
		RShift,
		Up,
		Numpad1,
		Numpad2,
		Numpad3,
		LControl,
		LSystem,
		LAlt,
		Space,
		RAlt,
		RSystem,
		Menu,
		RCtrl,
		Left,
		Down,
		Right,
		Numpad0,
	};

	sf::Sprite *getKeySprite(const Keys &key);

private:

	std::vector<sf::Sprite*>keysSprite;

	Keyboard();

	void cutRegularKeys(const int &Left, const int &Top, const size_t &count);
};