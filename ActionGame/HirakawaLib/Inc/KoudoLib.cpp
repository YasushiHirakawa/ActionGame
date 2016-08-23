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
KLDirect3D*		KoudoLib::p_kl_direct3d_;			// Direct3D�Ǘ�
KLFrameRate*	KoudoLib::p_kl_framer_rate_;		// �t���[�����[�g�Ǘ�
KLSprite*		KoudoLib::p_kl_sprite_;				// �X�v���C�g�f�[�^�Ǘ�
KLTexture*		KoudoLib::p_kl_texture_;			// �e�N�X�`���f�[�^�Ǘ�
KLModel*		KoudoLib::p_kl_model_;				// ���f���f�[�^�Ǘ�
KLInput*		KoudoLib::p_kl_input_;				// ���͊Ǘ�
KLAudio*		KoudoLib::p_kl_audio_;				// �I�[�f�B�I�Ǘ�

Matrix			KoudoLib::camera_view_matrix_;			// �J�����̃r���[�s��
Matrix			KoudoLib::camera_projection_matrix_;	// �J�����̎ˉe�s��


//---------------------------------------------------------------------------------------------
//	Method
//---------------------------------------------------------------------------------------------
/*---------------------------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
---------------------------------------------------------------------------------------------*/
KoudoLib::KoudoLib()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
---------------------------------------------------------------------------------------------*/
KoudoLib::~KoudoLib()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	������
//	@param	HWND hWnd	�F�E�B���h�E�n���h��
//	@retval	true		�F����
//	@retval	false		�F���s
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

		// �t���[�����[�g
		p_kl_framer_rate_ = new KLFrameRate;
		if (p_kl_framer_rate_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_framer_rate_->Init() == false) {
			ret = false;
			break;
		}

		// �X�v���C�g�Ǘ�
		p_kl_sprite_ = new KLSprite;
		if (p_kl_sprite_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_sprite_->Init(p_kl_direct3d_->GetDevice(), p_kl_direct3d_->GetDeviceContext()) == false) {
			ret = false;
			break;
		}

		// �e�N�X�`���f�[�^�Ǘ�
		p_kl_texture_ = new KLTexture;
		if (p_kl_texture_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_texture_->Init() == false) {
			ret = false;
			break;
		}

		// ���f���f�[�^�Ǘ�
		p_kl_model_ = new KLModel;
		if (p_kl_model_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_model_->Init(p_kl_direct3d_->GetDevice()) == false) {
			ret = false;
			break;
		}

		// ���͊Ǘ�
		p_kl_input_ = new KLInput;
		if (p_kl_input_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_input_->Init() == false) {
			ret = false;
			break;
		}

		// �I�[�f�B�I�Ǘ�
		p_kl_audio_ = new KLAudio;
		if (p_kl_audio_ == NULL) {
			ret = false;
			break;
		}
		if (p_kl_audio_->Init() == false) {
			ret = false;
			break;
		}

		// �E�B���h�E�n���h���̕ۑ�
		KLCommon::SetWindowHandle(hWnd);


		BeginSprite();
		EndSprite();

	} while (0);


	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	�j��
---------------------------------------------------------------------------------------------*/
void KoudoLib::Destroy()
{
	p_kl_input_->Destroy();			// ����
	SAFE_DELETE(p_kl_input_);
	p_kl_model_->Destroy();			// ���f���f�[�^
	SAFE_DELETE(p_kl_model_);
	p_kl_texture_->Destroy();		// �e�N�X�`���f�[�^
	SAFE_DELETE(p_kl_texture_);
	p_kl_sprite_->Destroy();		// �X�v���C�g
	SAFE_DELETE(p_kl_sprite_);
	p_kl_framer_rate_->Destroy();	// �t���[�����[�g
	SAFE_DELETE(p_kl_framer_rate_);
	p_kl_direct3d_->Destroy();		// Direct3D
	SAFE_DELETE(p_kl_direct3d_);
	p_kl_audio_->Destroy();			// �I�[�f�B�I
	SAFE_DELETE(p_kl_audio_);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�X�V
//	@retval	true		�F����
//	@retval	false		�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::Update()
{
	bool ret = false;
	
	float fps = (float)p_kl_framer_rate_->GetFPS();

	// �`��t���O�������Ă�����Q�[��������
	if (p_kl_framer_rate_->GetDrawFlag()) {
#if _DEBUG
		// �t���[�����[�g�`��
		wchar_t	str[kStrMax];
		swprintf_s(str, (L"%s�F%.1f"), KLCommon::GetWindowName(), fps);
		SetWindowText(KLCommon::GetWindowHandle(), str);
#endif
		// ���͍X�V
		p_kl_input_->Update();

		// �I�[�f�B�I�X�V
		p_kl_audio_->Update();

		// ���f���X�V
		p_kl_model_->Update();
		
		// �߂�l��true�ɕύX
		ret = true;
	}

	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	�J�����̃r���[�s��̐ݒ�
//	@param	Vector3 Position	�F�J�������W
//	@param	Vector3 Lookat		�F�J�����������W
//	@param	Vector3 Up			�F�J�����̏�����̌���
//	@retval	Matrix				�F�J�����̃r���[�s��
---------------------------------------------------------------------------------------------*/
Matrix KoudoLib::SetCameraViewMatrix(Vector3 Position, Vector3 Lookat, Vector3 Up)
{
	camera_view_matrix_ = p_kl_direct3d_->SetCameraViewMatrix(Position, Lookat, Up);

	return camera_view_matrix_;
}

/*---------------------------------------------------------------------------------------------
//	@brief	�J�����̎ˉe�s��̐ݒ�
//	@param	unsigned int	Width	�F��ʃT�C�Y��
//	@param	unsigned int	Height	�F��ʃT�C�Y�c
//	@param	float			Near	�F�j�A�N���b�v����
//	@param	float			Far		�F�t�@�[�N���b�v����
//	@retval	Matrix					�F�J�����̎ˉe�s��
---------------------------------------------------------------------------------------------*/
Matrix KoudoLib::SetCameraProjectionMatrix(unsigned int Width, unsigned int Height, float Near, float Far)
{
	camera_projection_matrix_ = p_kl_direct3d_->SetCameraProjectionMatrix(Width, Height, Near, Far);

	return camera_projection_matrix_;
}

/*---------------------------------------------------------------------------------------------
//	@brief	�E�B���h�E�̓��̓R�[���o�b�N��ݒ肷��
//	@param	hWnd		�E�B���h�E�n���h��
//	@param	msg			���b�Z�[�W
//	@param	wParam		���b�Z�[�W�Ɋւ���ǉ����
//	@param	lParam		���b�Z�[�W�Ɋւ���ǉ����
---------------------------------------------------------------------------------------------*/
void KoudoLib::SetWindowInputCallback(HWND hWnd, unsigned int msg, unsigned int wParam, LONG lParam)
{
	p_kl_input_->SetWindowInputCallback(hWnd, msg, wParam, lParam);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�L�[�{�[�h�F�{�^���������ꂽ���H(�������ςȂ��L��)
//	@param	Keyboard::Keys Key		�F�L�[���
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsPressKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�L�[�{�[�h�F�{�^���������ꂽ���H(�������ςȂ�����)
//	@param	Keyboard::Keys Key		�F�L�[���
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsPushKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�L�[�{�[�h�F�{�^���������ꂽ��
//	@param	Keyboard::Keys Key		�F�L�[���
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseKeyboard(Keyboard::Keys Key)
{
	return p_kl_input_->IsReleaseKeyboard(Key);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�}�E�X�F�{�^���������ꂽ���H(�������ςȂ��L��)
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsPressMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�}�E�X�F�{�^���������ꂽ���H(�������ςȂ�����)
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsPushMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�}�E�X�F�{�^���������ꂽ��
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseMouse(KLMOUSE_BUTTONS Button)
{
	return p_kl_input_->IsReleaseMouse(Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�}�E�X�F���W�擾
//	@retval	MOUSE_POSITION	�F�}�E�X���W
---------------------------------------------------------------------------------------------*/
MOUSE_POSITION KoudoLib::GetMousePosition()
{
	return p_kl_input_->GetMousePosition();
}

/*---------------------------------------------------------------------------------------------
//	@brief	�}�E�X�F���W�擾
//	@retval	int		�F�z�C�[���̒l
---------------------------------------------------------------------------------------------*/
int KoudoLib::GetMouseScrollWheel()
{
	return p_kl_input_->GetMouseScrollWheel();
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ��L��)
//	@param	int				Number	�F�Q�[���p�b�h�ԍ�
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPressGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsPressGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F�{�^���������ꂽ���H(�������ςȂ�����)
//	@param	int				Number	�F�Q�[���p�b�h�ԍ�
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsPushGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsReleaseGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F�{�^���������ꂽ��
//	@param	int				Number	�F�Q�[���p�b�h�ԍ�
//	@param	KLMOUSE_BUTTONS Button	�F�{�^�����
//	@retval	bool					�F���͔��茋��
---------------------------------------------------------------------------------------------*/
bool KoudoLib::IsReleaseGamePad(int Number, KLGAMEPAD_BUTTONS Button)
{
	return p_kl_input_->IsPushGamePad(Number, Button);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F���X�e�B�b�N�擾
//	@param	int			Number	�F�Q�[���p�b�h�ԍ�
//	@retval	Vector2				�F�X�e�B�b�N���
---------------------------------------------------------------------------------------------*/
Vector2 KoudoLib::GetGamePadLeftStick(int Number)
{
	return p_kl_input_->GetGamePadLeftStick(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F�E�X�e�B�b�N�擾
//	@param	int			Number	�F�Q�[���p�b�h�ԍ�
//	@retval	Vector2				�F�X�e�B�b�N���
---------------------------------------------------------------------------------------------*/
Vector2 KoudoLib::GetGamePadRightStick(int Number)
{
	return p_kl_input_->GetGamePadRightStick(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F���g���K�[�擾
//	@param	int		Number	�F�Q�[���p�b�h�ԍ�
//	@retval	float			�F�g���K�[���
---------------------------------------------------------------------------------------------*/
float KoudoLib::GetGamePadLeftTrigger(int Number)
{
	return p_kl_input_->GetGamePadLeftTrigger(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�Q�[���p�b�h�F�E�g���K�[�擾
//	@param	int		Number	�F�Q�[���p�b�h�ԍ�
//	@retval	float			�F�g���K�[���
---------------------------------------------------------------------------------------------*/
float KoudoLib::GetGamePadRightTrigger(int Number)
{
	return p_kl_input_->GetGamePadRightTrigger(Number);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�e�N�X�`���f�[�^�쐬
//	@param	wchar_t*			pFilename	�F�t�@�C����
//	@param	LPKLTextureData*	pTextureData�F�e�N�X�`���f�[�^�i�[��|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateTextureData(wchar_t* pFilename, LPKLTextureData* ppTextureData)
{
	return p_kl_texture_->CreateTextureData(p_kl_direct3d_->GetDevice(), pFilename, ppTextureData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�e�N�X�`���f�[�^���
//	@param	LPKLTextureData pTextureData�F����������e�N�X�`���f�[�^�|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseTextureData(LPKLTextureData pTextureData)
{
	return p_kl_texture_->ReleaseTextureData(pTextureData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	���f���f�[�^�쐬
//	@param	wchar_t*		pFilename	�F�t�@�C����
//	@param	LPKLModelData*	ppModelData	�F���f���f�[�^�i�[��|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateModelData(wchar_t* pFilename, LPKLModelData* ppModelData)
{
	return p_kl_model_->CreateModelData(p_kl_direct3d_->GetDevice(), pFilename, ppModelData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	���f���f�[�^���
//	@param	LPKLModelData pModelData�F������������f���f�[�^�|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseModelData(LPKLModelData pModelData)
{
	return p_kl_model_->ReleaseModelData(pModelData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	���f���f�[�^�쐬
//	@param	wchar_t*		pFilename	�F�t�@�C����
//	@param	LPKLAudioData*	ppAudioData	�F�I�[�f�B�I�f�[�^�i�[��|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::CreateAudioData(wchar_t* pFilename, LPKLAudioData* ppAudioData)
{
	return p_kl_audio_->CreateAudioDataFromWave(pFilename, ppAudioData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	���f���f�[�^���
//	@param	LPKLAudioData pModelData�F����������I�[�f�B�I�f�[�^�|�C���^
//	@retval	true	�F����
//	@retval	false	�F���s
---------------------------------------------------------------------------------------------*/
bool KoudoLib::ReleaseAudioData(LPKLAudioData pAudioData)
{
	return p_kl_audio_->ReleaseAudioData(pAudioData);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�X�v���C�g�`��
//	@param	LPKLTextureData pTextureData	�F�`�悷��e�N�X�`���f�[�^
//	@param	Vector2			Position		�F�`�悷����W
//	@param	RECT			Rect			�F�e�N�X�`���؂���͈�
//	@param	Vector4			Color			�F�e�N�X�`���J���[
//	@param	float			Rotation		�F��]
//	@param	float			Scale			�F�g��
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect, Vector4 Color,
							Vector2 Origin, float Rotation, float Scale)
{
	p_kl_sprite_->DrawSprite(pTextureData, Position, Rect, Color, Origin, Rotation, Scale);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�t�H���g�`��
//	@param	wchar_t*	pString		�F������
//	@param	Vector2		Position	�F�`�悷����W
//	@param	XMVECTOR	Color		�F�����̐F
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color)
{
	p_kl_sprite_->DrawFont(pString, Position, Color);
}

/*---------------------------------------------------------------------------------------------
//	@brief	���[���h�s��쐬
//	@param	Vector3 Position	�F���W
//	@param	Vector3 Rotation	�F��]
//	@param	Vector3 Scale		�F�g�k
//	@retval	Matrix				�F���[���h�s��
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
//	@brief	���[���h�s��쐬
//	@param	LPKLModelData	pModel		�F���f���f�[�^
//	@param	Matrix			WorldMatrix	�F���[���h�s��
---------------------------------------------------------------------------------------------*/
void KoudoLib::DrawModel(LPKLModelData pModel, Matrix WorldMatrix)
 {
	 if (pModel) {
		 pModel->p_model->Draw(p_kl_direct3d_->GetDeviceContext(), *(p_kl_direct3d_->GetCommonStates()),
								 WorldMatrix, camera_view_matrix_, camera_projection_matrix_);
	 }
 }

