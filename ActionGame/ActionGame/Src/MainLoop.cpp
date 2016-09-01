/****************************************************************************************************
//
//		MainLoop.cpp
//
//		@brief	メインループ制御
//		@author	Yasushi Hirakawa
//		@date	2015/11/24
//
****************************************************************************************************/

#include "MainLoop.h"

//---------------------------------------------------------------------------------------------
//	Method
//---------------------------------------------------------------------------------------------
/*---------------------------------------------------------------------------------------------
//	@brief	コンストラクタ
---------------------------------------------------------------------------------------------*/
MainLoop::MainLoop()
{
	// 関数ポインタの登録
	MainLoopFunc[MAINLOOP_INIT]		= &MainLoop::MainLoopInit;
	MainLoopFunc[MAINLOOP_WORK]		= &MainLoop::MainLoopWork;
	MainLoopFunc[MAINLOOP_DESTROY]	= &MainLoop::MainLoopDestroy;

	// 関数ポインタ呼び出しインデックスの初期化
	main_loop_state_ = MAINLOOP_INIT;
}

/*---------------------------------------------------------------------------------------------
//	@brief	デストラクタ
---------------------------------------------------------------------------------------------*/
MainLoop::~MainLoop()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	更新
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::Update()
{
	return (this->*MainLoopFunc[main_loop_state_])();
}

/*---------------------------------------------------------------------------------------------
//	@brief	破棄
---------------------------------------------------------------------------------------------*/
void MainLoop::Destroy()
{
	MainLoopDestroy();
}

/*---------------------------------------------------------------------------------------------
//	@brief	メインループ　初期化
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::MainLoopInit()
{
	int ret = GameInit();

	DrawInit();

	if (ret != 0) {
		main_loop_state_ = MAINLOOP_WORK;
	}

	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	メインループ　作業
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::MainLoopWork()
{
	int ret = GameWork();

	DrawWork();

	if (ret == 0) {
		main_loop_state_ = MAINLOOP_DESTROY;
		ret = 1;
	}

	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	メインループ　破棄
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::MainLoopDestroy()
{
	return GameDestroy();
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲーム　初期化
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::GameInit()
{
	HirakawaLib::CreateTextureData(L"Resource/windowslogo.dds", &p_texture_data_);
	HirakawaLib::CreateTextureData(L"Resource/gameloader.png", &p_texture_data_alpha_);
	//HirakawaLib::CreateAudioData(L"Resource/bgm_01.wav", &p_audio_data_);

	//p_audio_data_->Play();

	_wchdir(L"Resource");
	HirakawaLib::CreateModelData(L"tiny.sdkmesh", &p_model_data_);
	_wchdir(L"../");

	HirakawaLib::SetCameraViewMatrix(Vector3(0.0f, 3.0f, -900.0f), Vector3(0.0f, 0.0f, 0.0f));
	HirakawaLib::SetCameraProjectionMatrix(kWindowWidth, kWindowWidth, 1.0f, 1000.0f);

	position_ = Vector3(0.0f, 0.0f, 0.0f);


	HLLightInfo light_info = HirakawaLib::GetLightInfo();
	light_info.enable = true;
	light_info.diffuse_color = Vector3(0.0f, 0.0f, 0.0f);
	HirakawaLib::SetLightInfo(light_info);

	return 1;
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲーム　作業
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::GameWork()
{
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_L_STICK_RIGHT)) {
		position_.x += 10.0f;
		//p_audio_data_->Play();
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_L_STICK_LEFT)) {
		position_.x -= 10.0f;
		//p_audio_data_->Stop();
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_L_STICK_UP)) {
		position_.y += 10.0f;
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_L_STICK_DOWN)) {
		position_.y -= 10.0f;
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_R_STICK_RIGHT)) {
		position_.x += 10.0f;
		//p_audio_data_->Play();
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_R_STICK_LEFT)) {
		position_.x -= 10.0f;
		//p_audio_data_->Stop();
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_R_STICK_UP)) {
		position_.y += 10.0f;
	}
	if (HirakawaLib::IsPushGamePad(0, HLGAMEPAD_R_STICK_DOWN)) {
		position_.y -= 10.0f;
	}

	stick_ = HirakawaLib::GetGamePadRightStick(0);
	trigger_ = HirakawaLib::GetGamePadRightTrigger(0);

	mouse_pos_ = HirakawaLib::GetMousePosition();
	wheel_ = HirakawaLib::GetMouseScrollWheel();

	HLLightInfo light_info = HirakawaLib::GetLightInfo();
	light_info.diffuse_color += Vector3(0.005f, 0.005f, 0.005f);
	if (light_info.diffuse_color.x > 1.0f) {
		light_info.diffuse_color = Vector3(0.0f, 0.0f, 0.0f);
	}
	HirakawaLib::SetLightInfo(light_info);


	return 1;
}

/*---------------------------------------------------------------------------------------------
//	@brief	ゲーム　破棄
//	@retval	１		：ループ継続
//	@retval	０		：ループ終了
---------------------------------------------------------------------------------------------*/
int MainLoop::GameDestroy()
{
	HirakawaLib::ReleaseTextureData(p_texture_data_);
	HirakawaLib::ReleaseTextureData(p_texture_data_alpha_);
	HirakawaLib::ReleaseModelData(p_model_data_);
	//HirakawaLib::ReleaseAudioData(p_audio_data_);

	return 0;
}

/*---------------------------------------------------------------------------------------------
//	@brief	描画　初期化
---------------------------------------------------------------------------------------------*/
void MainLoop::DrawInit()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	描画　作業
---------------------------------------------------------------------------------------------*/
void MainLoop::DrawWork()
{
	// 描画開始
	HirakawaLib::BeginScene();

	Matrix world = HirakawaLib::CreateWorldMatrix(position_, Vector3(270.0f, 180.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	HirakawaLib::DrawModel(p_model_data_, world);

	// スプライト描画開始
	HirakawaLib::BeginSprite();

	RECT rect;
	Vector4 color = { 1.0f, 1.0f, 1.0f, 0.5f };
	rect.left = rect.top = 0L;
	rect.right = rect.bottom = 256L;
	HirakawaLib::DrawSprite(p_texture_data_, Vector2(100.0f, 400.0f), rect, color);

	rect.left = rect.top = 512L;
	rect.right = rect.bottom = 1024L;
	HirakawaLib::DrawSprite(p_texture_data_alpha_, Vector2(50.0f, 300.0f), rect);

	WCHAR	str[kStrMax];
	swprintf_s(str, (L"%s %f %f"), L"Stick  ", stick_.x, stick_.y);
	HirakawaLib::DrawFont(str, Vector2(0.0f, 0.0f));
	swprintf_s(str, (L"%s %f"), L"trigger  ", trigger_);
	HirakawaLib::DrawFont(str, Vector2(0.0f, 50.0f));
	swprintf_s(str, (L"%s %d %d"), L"MousePos  ", mouse_pos_.x, mouse_pos_.y);
	HirakawaLib::DrawFont(str, Vector2(0.0f, 100.0f));
	swprintf_s(str, (L"%s %d"), L"MouseWheel  ", wheel_);
	HirakawaLib::DrawFont(str, Vector2(0.0f, 150.0f));

	// スプライト描画終了
	HirakawaLib::EndSprite();

	// 描画終了
	HirakawaLib::EndScene();
}



