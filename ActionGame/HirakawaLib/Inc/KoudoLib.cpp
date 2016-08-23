/****************************************************************************************************
//
//		KoudoLib.cpp
//
//		@brief	KoudoLib
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#include "KoudoLib.h"


//---------------------------------------------------------------------------------------------
//	Static Member
//---------------------------------------------------------------------------------------------
KLDirect3D*		KoudoLib::p_kl_direct3d_;			// Direct3D管理
KLFrameRate*	KoudoLib::p_kl_framer_rate_;		// フレームレート管理
KLSprite*		KoudoLib::p_kl_sprite_;				// スプライトデータ管理
KLTexture*		KoudoLib::p_kl_texture_;			// テクスチャデータ管理
KLModel*		KoudoLib::p_kl_model_;				// モデルデータ管理
KLInput*		KoudoLib::p_kl_input_;				// 入力管理
KLAudio*		KoudoLib::p_kl_audio_;				// オーディオ管理

Matrix			KoudoLib::camera_view_matrix_;			// カメラのビュー行列
Matrix			KoudoLib::camera_projection_matrix_;	// カメラの射影行列


//---------------------------------------------------------------------------------------------
//	Method
//---------------------------------------------------------------------------------------------
/*---------------------------------------------------------------------------------------------
//	@brief	コンストラクタ
---------------------------------------------------------------------------------------------*/
KoudoLib::KoudoLib()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	デストラクタ
---------------------------------------------------------------------------------------------*/
KoudoLib::~KoudoLib()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	初期化
//	@param	HWND hWnd	：ウィンドウハンドル
//	@retval	true		：成功
//	@retval	false		：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::Init(HWND hWnd)
{
	bool ret = true;

	do {

		// Direct3D
		p_kl_direct3d_ = new KLDirect3D;
		if (p_kl_direct3d_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_direct3d_->Init(hWnd) == false) {
			ret = false;
			break;
		}

		// フレームレート
		p_kl_framer_rate_ = new KLFrameRate;
		if (p_kl_framer_rate_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_framer_rate_->Init() == false) {
			ret = false;
			break;
		}

		// スプライト管理
		p_kl_sprite_ = new KLSprite;
		if (p_kl_sprite_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_sprite_->Init(p_kl_direct3d_->GetDevice(), p_kl_direct3d_->GetDeviceContext()) == false) {
			ret = false;
			break;
		}

		// テクスチャデータ管理
		p_kl_texture_ = new KLTexture;
		if (p_kl_texture_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_texture_->Init() == false) {
			ret = false;
			break;
		}

		// モデルデータ管理
		p_kl_model_ = new KLModel;
		if (p_kl_model_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_model_->Init(p_kl_direct3d_->GetDevice()) == false) {
			ret = false;
			break;
		}

		// 入力管理
		p_kl_input_ = new KLInput;
		if (p_kl_input_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_input_->Init() == false) {
			ret = false;
			break;
		}

		// オーディオ管理
		p_kl_audio_ = new KLAudio;
		if (p_kl_audio_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_audio_->Init() == false) {
			ret = false;
			break;
		}

		// ウィンドウハンドルの保存
		KLCommon::SetWindowHandle(hWnd);


		BeginSprite();
		EndSprite();

	} while (0);


	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	破棄
---------------------------------------------------------------------------------------------*/
void KoudoLib::Destroy()
{
	p_kl_input_->Destroy();			// 入力
	SAFE_DELETE(p_kl_input_);
	p_kl_model_->Destroy();			// モデルデータ
	SAFE_DELETE(p_kl_model_);
	p_kl_texture_->Destroy();		// テクスチャデータ
	SAFE_DELETE(p_kl_texture_);
	p_kl_sprite_->Destroy();		// スプライト
	SAFE_DELETE(p_kl_sprite_);
	p_kl_framer_rate_->Destroy();	// フレームレート
	SAFE_DELETE(p_kl_framer_rate_);
	p_kl_direct3d_->Destroy();		// Direct3D
	SAFE_DELETE(p_kl_direct3d_);
	p_kl_audio_->Destroy();			// オーディオ
	SAFE_DELETE(p_kl_audio_);
}

/*---------------------------------------------------------------------------------------------
//	@brief	更新
//	@retval	true		：成功
//	@retval	false		：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::Update()
{
	bool ret = false;
	
	float fps = (float)p_kl_framer_rate_->GetFPS();

	// 描画フラグが立っていたらゲーム処理へ
	if (p_kl_framer_rate_->GetDrawFlag()) {
#if _DEBUG
		// フレームレート描画
		wchar_t	str[kStrMax];
		swprintf_s(str, (L"%s：%.1f"), KLCommon::GetWindowName(), fps);
		SetWindowText(KLCommon::GetWindowHandle(), str);
#endif
		// 入力更新
		p_kl_input_->Update();

		// オーディオ更新
		p_kl_audio_->Update();

		// モデル更新
		p_kl_model_->Update();
		
		// 戻り値をtrueに変更
		ret = true;
	}

	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	カメラのビュー行列の設定
//	@param	Vector3 Position	：カメラ座標
//	@param	Vector3 Lookat		：カメラ注視座標
//	@param	Vector3 Up			：カメラの上方向の向き
//	@retval	Matrix				：カメラのビュー行列
---------------------------------------------------------------------------------------------*/
Matrix KoudoLib::SetCameraViewMatrix(Vector3 Position, Vector3 Lookat, Vector3 Up)
{
	camera_view_matrix_ = p_kl_direct3d_->SetCameraViewMatrix(Position, Lookat, Up);

	return camera_view_matrix_;
}

/*---------------------------------------------------------------------------------------------
//	@brief	カメラの射影行列の設定
//	@param	unsigned int	Width	：画面サイズ横
//	@param	unsigned int	Height	：画面サイズ縦
//	@param	float			Near	：ニアクリップ距離
//	@param	float			Far		：ファークリップ距離
//	@retval	Matrix					：カメラの射影行列
---------------------------------------------------------------------------------------------*/
Matrix KoudoLib::SetCameraProjectionMatrix(unsigned int Width, unsigned int Height, float Near, float Far)
{
	camera_projection_matrix_ = p_kl_direct3d_->SetCameraProjectionMatrix(Width, Height, Near, Far);

	return camera_projection_matrix_;
}

/*---------------------------------------------------------------------------------------------
//	@brief	ウィンドウの入力コールバックを設定する
//	@param	hWnd		ウィンドウハンドル
//	@param	msg			メッセージ
//	@param	wParam		メッセージに関する追加情報
//	@param	lParam		メッセージに関する追加情報
---------------------------------------------------------------------------------------------*/
void KoudoLib::SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam)
{
	p_kl_input_->SetWindowInputCallback(hWnd, msg, wParam, lParam);
}

/*---------------------------------------------------------------------------------------------
//	@brief	キーボード：ボタンが押されたか？(押しっぱなし有効)
//	@param	Keyboard::Keys Key		：キー情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsPressKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	キーボード：ボタンが押されたか？(押しっぱなし無効)
//	@param	Keyboard::Keys Key		：キー情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsPushKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	キーボード：ボタンが離されたか
//	@param	Keyboard::Keys Key		：キー情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsReleaseKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	マウス：ボタンが押されたか？(押しっぱなし有効)
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsPressMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	マウス：ボタンが押されたか？(押しっぱなし無効)
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsPushMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	マウス：ボタンが離されたか
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsReleaseMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	マウス：座標取得
//	@retval	MOUSE_POSITION	：マウス座標
---------------------------------------------------------------------------------------------*/
MOUSE_POSITION KoudoLib::GetMousePosition()
{
	return p_kl_input_->GetMousePosition();
}

/*---------------------------------------------------------------------------------------------
//	@brief	マウス：座標取得
//	@retval	int		：ホイールの値
---------------------------------------------------------------------------------------------*/
int KoudoLib::GetMouseScrollWheel()
{
	return p_kl_input_->GetMouseScrollWheel();
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：ボタンが押されたか？(押しっぱなし有効)
//	@param	int				Number	：ゲームパッド番号
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsPressGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：ボタンが押されたか？(押しっぱなし無効)
//	@param	int				Number	：ゲームパッド番号
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsReleaseGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：ボタンが離されたか
//	@param	int				Number	：ゲームパッド番号
//	@param	KLMOUSE_BUTTONS Button	：ボタン情報
//	@retval	bool					：入力判定結果
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsPushGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：左スティック取得
//	@param	int			Number	：ゲームパッド番号
//	@retval	Vector2				：スティック情報
---------------------------------------------------------------------------------------------*/
Vector2 KoudoLib::GetGamePadLeftStick(int Number)
{
	return p_kl_input_->GetGamePadLeftStick(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：右スティック取得
//	@param	int			Number	：ゲームパッド番号
//	@retval	Vector2				：スティック情報
---------------------------------------------------------------------------------------------*/
Vector2 KoudoLib::GetGamePadRightStick(int Number)
{
	return p_kl_input_->GetGamePadRightStick(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：左トリガー取得
//	@param	int		Number	：ゲームパッド番号
//	@retval	float			：トリガー情報
---------------------------------------------------------------------------------------------*/
float KoudoLib::GetGamePadLeftTrigger(int Number)
{
	return p_kl_input_->GetGamePadLeftTrigger(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲームパッド：右トリガー取得
//	@param	int		Number	：ゲームパッド番号
//	@retval	float			：トリガー情報
---------------------------------------------------------------------------------------------*/
float KoudoLib::GetGamePadRightTrigger(int Number)
{
	return p_kl_input_->GetGamePadRightTrigger(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	テクスチャデータ作成
//	@param	wchar_t*			pFilename	：ファイル名
//	@param	LPKLTextureData*	pTextureData：テクスチャデータ格納先ポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateTextureData(wchar_t* pFilename, LPKLTextureData* ppTextureData)
{
	return p_kl_texture_->CreateTextureData(p_kl_direct3d_->GetDevice(), pFilename, ppTextureData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	テクスチャデータ解放
//	@param	LPKLTextureData pTextureData：解放したいテクスチャデータポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseTextureData(LPKLTextureData pTextureData)
{
	return p_kl_texture_->ReleaseTextureData(pTextureData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	モデルデータ作成
//	@param	wchar_t*		pFilename	：ファイル名
//	@param	LPKLModelData*	ppModelData	：モデルデータ格納先ポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateModelData(wchar_t* pFilename, LPKLModelData* ppModelData)
{
	return p_kl_model_->CreateModelData(p_kl_direct3d_->GetDevice(), pFilename, ppModelData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	モデルデータ解放
//	@param	LPKLModelData pModelData：解放したいモデルデータポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseModelData(LPKLModelData pModelData)
{
	return p_kl_model_->ReleaseModelData(pModelData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	モデルデータ作成
//	@param	wchar_t*		pFilename	：ファイル名
//	@param	LPKLAudioData*	ppAudioData	：オーディオデータ格納先ポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateAudioData(wchar_t* pFilename, LPKLAudioData* ppAudioData)
{
	return p_kl_audio_->CreateAudioDataFromWave(pFilename, ppAudioData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	モデルデータ解放
//	@param	LPKLAudioData pModelData：解放したいオーディオデータポインタ
//	@retval	true	：成功
//	@retval	false	：失敗
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseAudioData(LPKLAudioData pAudioData)
{
	return p_kl_audio_->ReleaseAudioData(pAudioData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	スプライト描画
//	@param	LPKLTextureData pTextureData	：描画するテクスチャデータ
//	@param	Vector2			Position		：描画する座標
//	@param	RECT			Rect			：テクスチャ切り取り範囲
//	@param	Vector4			Color			：テクスチャカラー
//	@param	float			Rotation		：回転
//	@param	float			Scale			：拡大
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect, Vector4 Color,
							Vector2 Origin, float Rotation, float Scale)
{
	p_kl_sprite_->DrawSprite(pTextureData, Position, Rect, Color, Origin, Rotation, Scale);
}

/*---------------------------------------------------------------------------------------------
//	@brief	フォント描画
//	@param	wchar_t*	pString		：文字列
//	@param	Vector2		Position	：描画する座標
//	@param	XMVECTOR	Color		：文字の色
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color)
{
	p_kl_sprite_->DrawFont(pString, Position, Color);
}

/*---------------------------------------------------------------------------------------------
//	@brief	ワールド行列作成
//	@param	Vector3 Position	：座標
//	@param	Vector3 Rotation	：回転
//	@param	Vector3 Scale		：拡縮
//	@retval	Matrix				：ワールド行列
---------------------------------------------------------------------------------------------*/
Matrix KoudoLib::CreateWorldMatrix(Vector3 Position, Vector3 Rotation, Vector3 Scale)
{
	Matrix	world = XMMatrixIdentity();

	world *= XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	world *= XMMatrixRotationX(XMConvertToRadians(Rotation.x));
	world *= XMMatrixRotationY(XMConvertToRadians(Rotation.y));
	world *= XMMatrixRotationZ(XMConvertToRadians(Rotation.z));
	world *= XMMatrixTranslation(Position.x, Position.y, Position.z);

	return world;
}

/*---------------------------------------------------------------------------------------------
//	@brief	ワールド行列作成
//	@param	LPKLModelData	pModel		：モデルデータ
//	@param	Matrix			WorldMatrix	：ワールド行列
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawModel(LPKLModelData pModel, Matrix WorldMatrix)
 {
	 if (pModel) {
		 pModel->p_model->Draw(p_kl_direct3d_->GetDeviceContext(), *(p_kl_direct3d_->GetCommonStates()),
								 WorldMatrix, camera_view_matrix_, camera_projection_matrix_);
	 }
 }

