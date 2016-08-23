/****************************************************************************************************
//
//		KoudoLib.h
//
//		@brief	KoudoLib 
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KOUDOLIB_H__
#define __KOUDOLIB_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------

#include "../Src/KLFrameRate.h"
#include "../Src/KLDirect3D.h"
#include "../Src/KLSprite.h"
#include "../Src/KLTexture.h"
#include "../Src/KLModel.h"
#include "../Src/KLInput.h"
#include "../Src/KLAudio.h"

//---------------------------------------------------------------------------------------------
//	define
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KoudoLib
{
public:
	KoudoLib();
	~KoudoLib();

	static bool		Init(HWND hWnd);		// 初期化
	static void		Destroy();				// 破棄
	static bool		Update();				// 更新


	// カメラ命令 ------------------------------------------------------------------
	// ビュー行列の設定
	static Matrix SetCameraViewMatrix(Vector3 Position, Vector3 Lookat, Vector3 Up = Vector3(0.0F, 1.0F, 0.0F));
	// 射影行列の設定
	static Matrix SetCameraProjectionMatrix(unsigned int Width, unsigned int Height, float Near = 1.0F, float Far = 1000.0F);


	// 入力命令 --------------------------------------------------------------------
	// ウィンドウの入力コールバックを受け取る
	static void SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam);
	// キーボード：ボタンが押されたか？(押しっぱなし有効)
	static bool IsPressKeyboard(Keyboard::Keys Key);
	// キーボード：ボタンが押されたか？(押しっぱなし無効)
	static bool IsPushKeyboard(Keyboard::Keys Key);
	// キーボード：ボタンが離されたか
	static bool IsReleaseKeyboard(Keyboard::Keys Key);
	// マウス：ボタンが押されたか？(押しっぱなし有効)
	static bool IsPressMouse(KLMOUSE_BUTTONS Button);
	// マウス：ボタンが押されたか？(押しっぱなし無効)
	static bool IsPushMouse(KLMOUSE_BUTTONS Button);
	// マウス：ボタンが離されたか
	static bool IsReleaseMouse(KLMOUSE_BUTTONS Button);
	// マウス：座標取得
	static MOUSE_POSITION GetMousePosition();
	// マウス：スクロールホイール取得
	static int GetMouseScrollWheel();
	// ゲームパッド：ボタンが押されたか？(押しっぱなし有効)
	static bool IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：ボタンが押されたか？(押しっぱなし無効)
	static bool IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：ボタンが離されたか
	static bool IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// ゲームパッド：左スティック取得
	static Vector2 GetGamePadLeftStick(int Number);
	// ゲームパッド：右スティック取得
	static Vector2 GetGamePadRightStick(int Number);
	// ゲームパッド：左トリガー取得
	static float GetGamePadLeftTrigger(int Number);
	// ゲームパッド：右トリガー取得
	static float GetGamePadRightTrigger(int Number);


	// リソースデータの作成・解放 -----------------------------------------------------
	// テクスチャデータ作成・解放
	static bool CreateTextureData(wchar_t* pFilename, LPKLTextureData* ppTextureData);
	static bool ReleaseTextureData(LPKLTextureData pTextureData);
	// モデルデータ作成・解放
	static bool CreateModelData(wchar_t* pFilename, LPKLModelData* ppModelData);
	static bool ReleaseModelData(LPKLModelData pModelData);
	// オーディオデータ作成・解放
	static bool CreateAudioData(wchar_t* pFilename, LPKLAudioData* ppAudioData);
	static bool ReleaseAudioData(LPKLAudioData pAudioData);

	// 描画の開始・終了 --------------------------------------------------------------
	// 描画開始・終了
	inline static void	BeginScene() { p_kl_direct3d_->BeginScene(); p_kl_model_->Update(); }
	inline static void	EndScene() { p_kl_direct3d_->EndScene(); }
	// スプライト描画開始・終了
	inline static void	BeginSprite() { p_kl_sprite_->BeginSprite(p_kl_direct3d_->GetCommonStates()); }
	inline static void	EndSprite() { p_kl_sprite_->EndSprite(); }


	// 描画命令 --------------------------------------------------------------------
	// スプライト描画
	static void	DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect,
							Vector4 Color = Vector4(1.0F, 1.0F, 1.0F, 1.0F), 
							Vector2 Origin = Vector2(0.0F, 0.0F),
							float Rotation = 0.0F, float Scale = 1.0F);
	// フォント描画
	static void	DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color = Colors::White);
	// ワールド行列作成
	static Matrix CreateWorldMatrix(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	// モデル描画
	static void DrawModel(LPKLModelData pModel, Matrix WorldMatrix);
	// ライト情報の取得・設定
	inline static KLLightInfo GetLightInfo() { return p_kl_model_->GetLightInfo(); }
	inline static void SetLightInfo(KLLightInfo LightInfo) { p_kl_model_->SetLightInfo(LightInfo); }
	// フォグ情報の取得・設定
	inline static KLFogInfo GetFogInfo() { return p_kl_model_->GetFogInfo(); }
	inline static void SetFogInfo(KLFogInfo FogInfo) { p_kl_model_->SetFogInfo(FogInfo); }


private:
	static KLDirect3D*		p_kl_direct3d_;			// Direct3D管理
	static KLFrameRate*		p_kl_framer_rate_;		// フレームレート管理
	static KLSprite*		p_kl_sprite_;			// スプライト管理
	static KLTexture*		p_kl_texture_;			// テクスチャデータ管理
	static KLModel*			p_kl_model_;			// モデルデータ管理
	static KLInput*			p_kl_input_;			// 入力管理
	static KLAudio*			p_kl_audio_;			// オーディオ管理

	static Matrix			camera_view_matrix_;		// カメラのビュー行列
	static Matrix			camera_projection_matrix_;	// カメラの射影行列
};


#endif //__KOUDOLIB_H__