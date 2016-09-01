/****************************************************************************************************
//
//		MainLoop.h
//
//		@brief	メインループ制御
//		@author	Yasushi Hirakawa
//		@date	2015/11/24
//
****************************************************************************************************/

#ifndef __MAINLOOP_H__
#define __MAINLOOP_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "HirakawaLib/Inc/HirakawaLib.h"

//---------------------------------------------------------------------------------------------
//	define
//---------------------------------------------------------------------------------------------
enum MAINLOOP_STATE
{
	MAINLOOP_INIT = 0,			// 初期化
	MAINLOOP_WORK,				// 作業
	MAINLOOP_DESTROY,			// 破棄
	MAX_MAINLOOP_STATE			// 最大値
};

//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	int		Update();						// メイン関数
	void	Destroy();						// 破棄

private:
	// メインループを制御する関数ポインタの定義
	int		(MainLoop::*MainLoopFunc[MAX_MAINLOOP_STATE])();

	// 関数ポインタ呼び出しインデックス
	MAINLOOP_STATE	main_loop_state_;

	// メインループ作業関数
	int		MainLoopInit();			// メインループ 初期化
	int		MainLoopWork();			// メインループ 作業
	int		MainLoopDestroy();		// メインループ 破棄

	// ゲーム作業関数
	int		GameInit();				// ゲーム 初期化
	int		GameWork();				// ゲーム 作業
	int		GameDestroy();			// ゲーム 破棄

	// 描画作業関数
	void	DrawInit();				// 描画 初期化
	void	DrawWork();				// 描画 作業



	LPHLTextureData		p_texture_data_;
	LPHLTextureData		p_texture_data_alpha_;
	LPHLModelData		p_model_data_;
	//LPHLAudioData		p_audio_data_;

	Vector3				position_;

	Vector2				stick_;
	float				trigger_;
	MOUSE_POSITION		mouse_pos_;
	int					wheel_;
};


#endif //__MAINLOOP_H__