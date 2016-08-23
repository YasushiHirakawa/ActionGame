/****************************************************************************************************
//
//		KLSprite.h
//
//		@brief	KoudoLib �X�v���C�g�`��Ǘ�
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#include "KLSprite.h"


//---------------------------------------------------------------------------------------------
//	Method
//---------------------------------------------------------------------------------------------
/*---------------------------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
---------------------------------------------------------------------------------------------*/
KLSprite::KLSprite()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
---------------------------------------------------------------------------------------------*/
KLSprite::~KLSprite()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	������
//	@param	ID3D11Device*			pDevice			�F�f�o�C�X
//	@param	ID3D11DeviceContext*	pDeviceContext	�F�f�o�C�X�R���e�L�X�g
//	@retval true	�F����
//	@retval false	�F���s
---------------------------------------------------------------------------------------------*/
bool KLSprite::Init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	bool ret = true;

	do {

		// �X�v���C�g�o�b�`�̏�����
		p_sprite_batch_ = new SpriteBatch(pDeviceContext);
		if (p_sprite_batch_ == NULL) {
			ret = false;
			break;
		}

		// �X�v���C�g�t�H���g�̏�����
		p_sprite_font_ = new SpriteFont(pDevice, L"../KoudoLib/Resource/italic.spritefont");
		if (p_sprite_batch_ == NULL) {
			ret = false;
			break;
		}

	} while (0);


	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	�j��
---------------------------------------------------------------------------------------------*/
void KLSprite::Destroy()
{
	SAFE_DELETE(p_sprite_batch_);
	SAFE_DELETE(p_sprite_font_);
}

/*---------------------------------------------------------------------------------------------
//	@brief	�`��J�n
//	@param	CommonStates* pStates	�F�R�����X�e�[�^�X
---------------------------------------------------------------------------------------------*/
void KLSprite::BeginSprite(CommonStates* pStates)
{
	p_sprite_batch_->Begin(SpriteSortMode_Deferred, pStates->NonPremultiplied());
}

/*---------------------------------------------------------------------------------------------
//	@brief	�`��I��
---------------------------------------------------------------------------------------------*/
void KLSprite::EndSprite()
{
	p_sprite_batch_->End();
}

/*---------------------------------------------------------------------------------------------
//	@brief	�X�v���C�g�`��
//	@param	LPKLTextureData pTextureData	�F�`�悷��e�N�X�`���f�[�^
//	@param	Vector2			Position		�F�`�悷����W
//	@param	RECT			Rect			�F�e�N�X�`���؂���͈�
//	@param	Vector4			Color			�F�e�N�X�`���J���[
//	@param	Vector2			Origin			�F�e�N�X�`���̒��S���W
//	@param	float			Rotation		�F��]
//	@param	float			Scale			�F�g��
---------------------------------------------------------------------------------------------*/
void KLSprite::DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect, Vector4 Color,
							Vector2 Origin, float Rotation, float Scale)
{
	p_sprite_batch_->Draw(pTextureData->p_texture, Position, &Rect, Color, Rotation, Origin, Scale);
}

/*---------------------------------------------------------------------------------------------
//	@brief	������`��
---------------------------------------------------------------------------------------------*/
void KLSprite::DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color)
{
	p_sprite_font_->DrawString(p_sprite_batch_, pString, Position, Color);
}


