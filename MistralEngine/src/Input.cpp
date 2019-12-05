#include "Input.h"

void Input::InitializeKeys() {

	addInput("FORWARD", { InputKey::ARROWUP, InputKey::W });
	addInput("BACKWARD", { InputKey::ARROWDOWN, InputKey::S });
	addInput("LEFT", { InputKey::ARROWLEFT, InputKey::A });
	addInput("RIGHT", { InputKey::ARROWRIGHT, InputKey::D });
	addInput("UP", { InputKey::Q });
	addInput("DOWN", { InputKey::E });
}

Input::Input() {

	keyStates = {
		{ InputKey::A , false },
		{ InputKey::B , false },
		{ InputKey::C , false },
		{ InputKey::D , false },
		{ InputKey::E , false },
		{ InputKey::F , false },
		{ InputKey::G , false },
		{ InputKey::H , false },
		{ InputKey::I , false },
		{ InputKey::J , false },
		{ InputKey::K , false },
		{ InputKey::L , false },
		{ InputKey::M , false },
		{ InputKey::N , false },
		{ InputKey::O , false },
		{ InputKey::P , false },
		{ InputKey::Q , false },
		{ InputKey::R , false },
		{ InputKey::S , false },
		{ InputKey::T , false },
		{ InputKey::U , false },
		{ InputKey::V , false },
		{ InputKey::W , false },
		{ InputKey::X , false },
		{ InputKey::Y , false },
		{ InputKey::Z , false },

		{ InputKey::ZERO , false },
		{ InputKey::ONE , false },
		{ InputKey::TWO , false },
		{ InputKey::THREE , false },
		{ InputKey::FOUR , false },
		{ InputKey::FIVE , false },
		{ InputKey::SIX , false },
		{ InputKey::SEVEN , false },
		{ InputKey::EIGHT , false },
		{ InputKey::NINE , false },

		{ InputKey::ARROWRIGHT , false },
		{ InputKey::ARROWUP , false },
		{ InputKey::ARROWLEFT , false },
		{ InputKey::ARROWDOWN , false },

		{ InputKey::SPACE , false },

		{ InputKey::F1 , false },
		{ InputKey::F2 , false },
		{ InputKey::F3 , false },
		{ InputKey::F4 , false },
		{ InputKey::F5 , false },
		{ InputKey::F6 , false },
		{ InputKey::F7 , false },
		{ InputKey::F8 , false },
		{ InputKey::F9 , false },
		{ InputKey::F10 , false },
		{ InputKey::F11 , false },
		{ InputKey::F12 , false },


		{ InputKey::PAGEDOWN , false },
		{ InputKey::PAGEUP , false },
		{ InputKey::HOME , false },
		{ InputKey::END , false },
		{ InputKey::INSERT , false },
	};

	InitializeKeys();
}

void Input::KeyboardPressHandle(int key) {
	if (keyStates.find(key) != keyStates.end()) {
		keyStates.at(key) = true;
	}
}

void Input::KeyboardReleaseHandle(int key) {
	if (keyStates.find(key) != keyStates.end()) {
		keyStates.at(key) = false;
	}
}

void Input::addInput( string key, list<int> keymap) {
	InputItem it;
	it.keymap = keymap;
	inputList.insert(pair<string, InputItem>(key, it));
}

void Input::UpdateInputs() {
	for (auto currI : inputList) {
		bool currentState = false;
		for (auto k : currI.second.keymap) {
			if (keyStates.at(k)) {
				currentState = true;
			}
		}

		if (currentState && !currI.second.hold) {
			inputList.at(currI.first).pressed = true;
		}else {
			if (!currentState && currI.second.hold) {
				inputList.at(currI.first).released = true;
			} else {
				inputList.at(currI.first).pressed = false;
				inputList.at(currI.first).released = false;
			}
		}

		inputList.at(currI.first).hold = currentState;
	}
}

bool Input::InputCheck(string input, int state) {
	switch (state) {
		case InputState::PRESSED:
			return inputList.at(input).pressed;
			break;
		case InputState::RELEASED:
			return inputList.at(input).released;
			break;
		case InputState::HOLD:
			return inputList.at(input).hold;
			break;
		default:
			return false;
			break;
	}
}