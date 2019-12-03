#include <vector>
#include <string>
#include <map>

using namespace std;

#define PRESSED 0
#define RELEASED 1
#define HOLD 2

enum InputKey {
	Q = (int)'Q',
	W = (int)'W',
	E = (int)'E',
	R = (int)'R',
	T = (int)'T',
	Y = (int)'Y',
	U = (int)'U',
	I = (int)'I',
	O = (int)'O',
	P = (int)'P',
	A = (int)'A',
	S = (int)'S',
	D = (int)'D',
	F = (int)'F',
	G = (int)'G',
	H = (int)'H',
	J = (int)'J',
	K = (int)'K',
	L = (int)'L',
	Z = (int)'Z',
	X = (int)'X',
	C = (int)'C',
	V = (int)'V',
	B = (int)'B',
	N = (int)'N',
	M = (int)'M',
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
	ARROWDOWN = GLUT_KEY_END,
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
	F12 = GLUT_KEY_F12
};

struct InputItem {
	string Name;
	vector<int> keymap;
	bool pressed = false;
	bool released = false;
	bool hold = false;
};

class Input {
public:
	Input();
	bool InputCheck( string input , int state );
	void UpdateInputs();

private:
	map<int, bool> KeyStates;
	bool GeneralCheck( InputItem input );

	void KeyboardPressHandle( int key );
	void SpecialPressHandle( int key );
	void KeyboardReleaseHandle( int key );
	void SpecialReleaseHandle(int key);
};