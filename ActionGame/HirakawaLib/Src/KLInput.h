/****************************************************************************************************
//
//		KLInput.h
//
//		@brief	KoudoLib 入力管理
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
// マウスボタン定義
enum KLMOUSE_BUTTONS
{
	KLMOUSE_L = 0,			// 左
	KLMOUSE_R,				// 右
	KLMOUSE_CENTER,			// 真ん中
	MAX_KLMOUSE_BUTTONS
};

// ゲームパッドボタン定義
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
const float kGamePadStickButtonRegion = 0.5F;		// ゲームパッドスティックボタン判定領域 

//---------------------------------------------------------------------------------------------
//	struct
//---------------------------------------------------------------------------------------------
// マウス座標
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

	bool Init();			// 初期化
	void Destroy();			// 破棄
	void Update();			// 更新

	// ウィンドウの入力コールバックを受け取る
	void SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam);

	// キーボード：キーが押されたか？(押しっぱなし有効)
	bool IsPressKeyboard(Keyboard::Keys Key);
	// キーボード：キーが押されたか？(押しっぱなし無効)
	bool IsPushKeyboard(Keyboard::Keys Key);
	// キーボード：キーが離されたか
	bool IsReleaseKeyboard(Keyboard::Keys Key);
	
	// マウス：ボタンが押されたか？(押しっぱなし有効)
	bool IsPressMouse(KLMOUSE_BUTTONS Button);
	// マウス：ボタンが押されたか？(押しっぱなし無効)
	bool IsPushMouse(KLMOUSE_BUTTONS Button);
	// マウス：ボタンが離されたか
	bool IsReleaseMouse(KLMOUSE_BUTTONS Button);
	// マウス：座標取得
	MOUSE_POSITION GetMousePosition();
	// マウス：スクロールホイール取得
	int GetMouseScrollWheel();

	// ゲームパッド：ボタンが押されたか？(押しっぱなし有効)
	bool IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：ボタンが押されたか？(押しっぱなし無効)
	bool IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：ボタンが離されたか
	bool IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：左スティック取得
	Vector2 GetGamePadLeftStick(int Number);
	// ゲームパッド：右スティック取得
	Vector2 GetGamePadRightStick(int Number);
	// ゲームパッド：左トリガー取得
	float GetGamePadLeftTrigger(int Number);
	// ゲームパッド：右トリガー取得
	float GetGamePadRightTrigger(int Number);

private:
	Keyboard*			p_keyboard_;			// キーボード
	Keyboard::State		keyboard_state_;		// キーボードの状態
	Keyboard::State		prev_keyboard_state_;	// 前のキーボードの状態

	Mouse*				p_mouse_;				// マウス
	Mouse::State		mouse_state_;			// マウスの状態
	Mouse::State		prev_mouse_state_;		// 前のマウスの状態

	GamePad*			p_game_pad_;			// ゲームパッド
	GamePad::State		game_pad_state_[GamePad::MAX_PLAYER_COUNT];			// ゲームパッドの状態
	GamePad::State		prev_game_pad_state_[GamePad::MAX_PLAYER_COUNT];	// 前のゲームパッドの状態
};


#endif //__KLINPUT_H__