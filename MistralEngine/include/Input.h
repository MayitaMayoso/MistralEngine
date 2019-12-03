#include <list>
#include <string>
#include <map>
#include <iostream>
#include <GL/glut.h>

using namespace std;

enum InputState {
	PRESSED = 0,
	RELEASED = 1,
	HOLD = 2
};

enum InputKey {
	A = (int)'A',
	B = (int)'B',
	C = (int)'C',
	D = (int)'D',
	E = (int)'E',
	F = (int)'F',
	G = (int)'G',
	H = (int)'H',
	I = (int)'I',
	J = (int)'J',
	K = (int)'K',
	L = (int)'L',
	M = (int)'M',
	N = (int)'N',
	O = (int)'O',
	P = (int)'P',
	Q = (int)'Q',
	R = (int)'R',
	S = (int)'S',
	T = (int)'T',
	U = (int)'U',
	V = (int)'V',
	W = (int)'W',
	X = (int)'X',
	Y = (int)'Y',
	Z = (int)'Z',

	ZERO = (int)'0',
	ONE = (int)'1',
	TWO = (int)'2',
	THREE = (int)'3',
	FOUR = (int)'4',
	FIVE = (int)'5',
	SIX = (int)'6',
	SEVEN = (int)'7',
	EIGHT = (int)'8',
	NINE = (int)'9',

	ARROWRIGHT = GLUT_KEY_RIGHT,
	ARROWUP = GLUT_KEY_UP,
	ARROWLEFT = GLUT_KEY_LEFT,
	ARROWDOWN = GLUT_KEY_DOWN,

	SPACE = 32,
	

	F1 = GLUT_KEY_F1,
	F2 = GLUT_KEY_F2,
	F3 = GLUT_KEY_F3,
	F4 = GLUT_KEY_F4,
	F5 = GLUT_KEY_F5,
	F6 = GLUT_KEY_F6,
	F7 = GLUT_KEY_F7,
	F8 = GLUT_KEY_F8,
	F9 = GLUT_KEY_F9,
	F10 = GLUT_KEY_F10,
	F11 = GLUT_KEY_F11,
	F12 = GLUT_KEY_F12,

	PAGEDOWN = GLUT_KEY_PAGE_DOWN,
	PAGEUP = GLUT_KEY_PAGE_UP,
	HOME = GLUT_KEY_HOME,
	END = GLUT_KEY_END,
	INSERT = GLUT_KEY_INSERT
};

struct InputItem {
	list<int> keymap;
	bool pressed = false;
	bool released = false;
	bool hold = false;
};

class Input {
public:
	Input();
	bool InputCheck( string input , int state );
	void UpdateInputs();

	void KeyboardPressHandle(int key);
	void KeyboardReleaseHandle(int key);

private:
	void addInput( string name, list<int> keymap );
	void InitializeKeys();

	map<int, bool> keyStates;
	map<string, InputItem> inputList;
};