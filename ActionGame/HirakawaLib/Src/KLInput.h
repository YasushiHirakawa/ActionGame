/****************************************************************************************************
//
//		KLInput.h
//
//		@brief	KoudoLib ���͊Ǘ�
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KLINPUT_H__
#define __KLINPUT_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "KLCommon.h"
#include "KLDirect3D.h"

//---------------------------------------------------------------------------------------------
//	enum
//---------------------------------------------------------------------------------------------
// �}�E�X�{�^����`
enum KLMOUSE_BUTTONS
{
	KLMOUSE_L = 0,			// ��
	KLMOUSE_R,				// �E
	KLMOUSE_CENTER,			// �^��
	MAX_KLMOUSE_BUTTONS
};

// �Q�[���p�b�h�{�^����`
enum KLGAMEPAD_BUTTONS
{
	KLGAMEPAD_A = 0,		// A
	KLGAMEPAD_B,			// B
	KLGAMEPAD_X,			// X
	KLGAMEPAD_Y,			// Y
	KLGAMEPAD_LB,			// LB
	KLGAMEPAD_RB,			// RB
	KLGAMEPAD_BACK,			// BACK
	KLGAMEPAD_START,		// START
	KLGAMEPAD_D_UP,			// D UP
	KLGAMEPAD_D_DOWN,		// D DOWN
	KLGAMEPAD_D_LEFT,		// D LEFT
	KLGAMEPAD_D_RIGHT,		// D RIGHT
	KLGAMEPAD_L_STICK_BUTTON,// L STICK BUTTON
	KLGAMEPAD_L_STICK_UP,	// L STICK UP
	KLGAMEPAD_L_STICK_DOWN,	// L STICK DOWN
	KLGAMEPAD_L_STICK_LEFT,	// L STICK LEFT
	KLGAMEPAD_L_STICK_RIGHT,// L STICK RIGHT
	KLGAMEPAD_R_STICK_BUTTON,// R STICK BUTTON
	KLGAMEPAD_R_STICK_UP,	// R STICK UP
	KLGAMEPAD_R_STICK_DOWN,	// R STICK DOWN
	KLGAMEPAD_R_STICK_LEFT,	// R STICK LEFT
	KLGAMEPAD_R_STICK_RIGHT,// R STICK RIGHT
	MAX_KLGAMEPAD_BUTTONS
};

//---------------------------------------------------------------------------------------------
//	const
//---------------------------------------------------------------------------------------------
const float kGamePadStickButtonRegion = 0.5F;		// �Q�[���p�b�h�X�e�B�b�N�{�^������̈� 

//---------------------------------------------------------------------------------------------
//	struct
//---------------------------------------------------------------------------------------------
// �}�E�X���W
struct MOUSE_POSITION
{
	int	x, y;
};

//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KLInput
{
public:
	KLInput();
	~KLInput();

	bool Init();			// ������
	void Destroy();			// �j��
	void Update();			// �X�V

	// �E�B���h�E�̓��̓R�[���o�b�N���󂯎��
	void SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam);

	// �L�[�{�[�h�F�L�[�������ꂽ���H(�������ςȂ��L��)
	bool IsPressKeyboard(Keyboard::Keys Key);
	// �L�[�{�[�h�F�L�[�������ꂽ���H(�������ςȂ�����)
	bool IsPushKeyboard(Keyboard::Keys Key);
	// �L�[�{�[�h�F�L�[�������ꂽ��
	bool IsReleaseKeyboard(Keyboard::Keys Key);
	
	// �}�E�X�F�{�^���������ꂽ���H(�������ςȂ��L��)
	bool IsPressMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F�{�^���������ꂽ���H(�������ςȂ�����)
	bool IsPushMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F�{�^���������ꂽ��
	bool IsReleaseMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F���W�擾
	MOUSE_POSITION GetMousePosition();
	// �}�E�X�F�X�N���[���z�C�[���擾
	int GetMouseScrollWheel();

	// �Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ��L��)
	bool IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ�����)
	bool IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F�{�^���������ꂽ��
	bool IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F���X�e�B�b�N�擾
	Vector2 GetGamePadLeftStick(int Number);
	// �Q�[���p�b�h�F�E�X�e�B�b�N�擾
	Vector2 GetGamePadRightStick(int Number);
	// �Q�[���p�b�h�F���g���K�[�擾
	float GetGamePadLeftTrigger(int Number);
	// �Q�[���p�b�h�F�E�g���K�[�擾
	float GetGamePadRightTrigger(int Number);

private:
	Keyboard*			p_keyboard_;			// �L�[�{�[�h
	Keyboard::State		keyboard_state_;		// �L�[�{�[�h�̏��
	Keyboard::State		prev_keyboard_state_;	// �O�̃L�[�{�[�h�̏��

	Mouse*				p_mouse_;				// �}�E�X
	Mouse::State		mouse_state_;			// �}�E�X�̏��
	Mouse::State		prev_mouse_state_;		// �O�̃}�E�X�̏��

	GamePad*			p_game_pad_;			// �Q�[���p�b�h
	GamePad::State		game_pad_state_[GamePad::MAX_PLAYER_COUNT];			// �Q�[���p�b�h�̏��
	GamePad::State		prev_game_pad_state_[GamePad::MAX_PLAYER_COUNT];	// �O�̃Q�[���p�b�h�̏��
};


#endif //__KLINPUT_H__