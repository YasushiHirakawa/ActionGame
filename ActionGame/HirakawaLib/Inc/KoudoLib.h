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

	static bool		Init(HWND hWnd);		// ������
	static void		Destroy();				// �j��
	static bool		Update();				// �X�V


	// �J�������� ------------------------------------------------------------------
	// �r���[�s��̐ݒ�
	static Matrix SetCameraViewMatrix(Vector3 Position, Vector3 Lookat, Vector3 Up = Vector3(0.0F, 1.0F, 0.0F));
	// �ˉe�s��̐ݒ�
	static Matrix SetCameraProjectionMatrix(unsigned int Width, unsigned int Height, float Near = 1.0F, float Far = 1000.0F);


	// ���͖��� --------------------------------------------------------------------
	// �E�B���h�E�̓��̓R�[���o�b�N���󂯎��
	static void SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam);
	// �L�[�{�[�h�F�{�^���������ꂽ���H(�������ςȂ��L��)
	static bool IsPressKeyboard(Keyboard::Keys Key);
	// �L�[�{�[�h�F�{�^���������ꂽ���H(�������ςȂ�����)
	static bool IsPushKeyboard(Keyboard::Keys Key);
	// �L�[�{�[�h�F�{�^���������ꂽ��
	static bool IsReleaseKeyboard(Keyboard::Keys Key);
	// �}�E�X�F�{�^���������ꂽ���H(�������ςȂ��L��)
	static bool IsPressMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F�{�^���������ꂽ���H(�������ςȂ�����)
	static bool IsPushMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F�{�^���������ꂽ��
	static bool IsReleaseMouse(KLMOUSE_BUTTONS Button);
	// �}�E�X�F���W�擾
	static MOUSE_POSITION GetMousePosition();
	// �}�E�X�F�X�N���[���z�C�[���擾
	static int GetMouseScrollWheel();
	// �Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ��L��)
	static bool IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ�����)
	static bool IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F�{�^���������ꂽ��
	static bool IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button);
	// �Q�[���p�b�h�F���X�e�B�b�N�擾
	static Vector2 GetGamePadLeftStick(int Number);
	// �Q�[���p�b�h�F�E�X�e�B�b�N�擾
	static Vector2 GetGamePadRightStick(int Number);
	// �Q�[���p�b�h�F���g���K�[�擾
	static float GetGamePadLeftTrigger(int Number);
	// �Q�[���p�b�h�F�E�g���K�[�擾
	static float GetGamePadRightTrigger(int Number);


	// ���\�[�X�f�[�^�̍쐬�E��� -----------------------------------------------------
	// �e�N�X�`���f�[�^�쐬�E���
	static bool CreateTextureData(wchar_t* pFilename, LPKLTextureData* ppTextureData);
	static bool ReleaseTextureData(LPKLTextureData pTextureData);
	// ���f���f�[�^�쐬�E���
	static bool CreateModelData(wchar_t* pFilename, LPKLModelData* ppModelData);
	static bool ReleaseModelData(LPKLModelData pModelData);
	// �I�[�f�B�I�f�[�^�쐬�E���
	static bool CreateAudioData(wchar_t* pFilename, LPKLAudioData* ppAudioData);
	static bool ReleaseAudioData(LPKLAudioData pAudioData);

	// �`��̊J�n�E�I�� --------------------------------------------------------------
	// �`��J�n�E�I��
	inline static void	BeginScene() { p_kl_direct3d_->BeginScene(); p_kl_model_->Update(); }
	inline static void	EndScene() { p_kl_direct3d_->EndScene(); }
	// �X�v���C�g�`��J�n�E�I��
	inline static void	BeginSprite() { p_kl_sprite_->BeginSprite(p_kl_direct3d_->GetCommonStates()); }
	inline static void	EndSprite() { p_kl_sprite_->EndSprite(); }


	// �`�施�� --------------------------------------------------------------------
	// �X�v���C�g�`��
	static void	DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect,
							Vector4 Color = Vector4(1.0F, 1.0F, 1.0F, 1.0F), 
							Vector2 Origin = Vector2(0.0F, 0.0F),
							float Rotation = 0.0F, float Scale = 1.0F);
	// �t�H���g�`��
	static void	DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color = Colors::White);
	// ���[���h�s��쐬
	static Matrix CreateWorldMatrix(Vector3 Position, Vector3 Rotation, Vector3 Scale);
	// ���f���`��
	static void DrawModel(LPKLModelData pModel, Matrix WorldMatrix);
	// ���C�g���̎擾�E�ݒ�
	inline static KLLightInfo GetLightInfo() { return p_kl_model_->GetLightInfo(); }
	inline static void SetLightInfo(KLLightInfo LightInfo) { p_kl_model_->SetLightInfo(LightInfo); }
	// �t�H�O���̎擾�E�ݒ�
	inline static KLFogInfo GetFogInfo() { return p_kl_model_->GetFogInfo(); }
	inline static void SetFogInfo(KLFogInfo FogInfo) { p_kl_model_->SetFogInfo(FogInfo); }


private:
	static KLDirect3D*		p_kl_direct3d_;			// Direct3D�Ǘ�
	static KLFrameRate*		p_kl_framer_rate_;		// �t���[�����[�g�Ǘ�
	static KLSprite*		p_kl_sprite_;			// �X�v���C�g�Ǘ�
	static KLTexture*		p_kl_texture_;			// �e�N�X�`���f�[�^�Ǘ�
	static KLModel*			p_kl_model_;			// ���f���f�[�^�Ǘ�
	static KLInput*			p_kl_input_;			// ���͊Ǘ�
	static KLAudio*			p_kl_audio_;			// �I�[�f�B�I�Ǘ�

	static Matrix			camera_view_matrix_;		// �J�����̃r���[�s��
	static Matrix			camera_projection_matrix_;	// �J�����̎ˉe�s��
};


#endif //__KOUDOLIB_H__