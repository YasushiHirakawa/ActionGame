/****************************************************************************************************
//
//		KLSprite.h
//
//		@brief	KoudoLib スプライト描画管理
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#include "KLSprite.h"


//---------------------------------------------------------------------------------------------
//	Method
//---------------------------------------------------------------------------------------------
/*---------------------------------------------------------------------------------------------
//	@brief	コンストラクタ
---------------------------------------------------------------------------------------------*/
KLSprite::KLSprite()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	デストラクタ
---------------------------------------------------------------------------------------------*/
KLSprite::~KLSprite()
{
}

/*---------------------------------------------------------------------------------------------
//	@brief	初期化
//	@param	ID3D11Device*			pDevice			：デバイス
//	@param	ID3D11DeviceContext*	pDeviceContext	：デバイスコンテキスト
//	@retval true	：成功
//	@retval false	：失敗
---------------------------------------------------------------------------------------------*/
bool KLSprite::Init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	bool ret = true;

	do {

		// スプライトバッチの初期化
		p_sprite_batch_ = new SpriteBatch(pDeviceContext);
		if (p_sprite_batch_ == NULL) {
			ret = false;
			break;
		}

		// スプライトフォントの初期化
		p_sprite_font_ = new SpriteFont(pDevice, L"../KoudoLib/Resource/italic.spritefont");
		if (p_sprite_batch_ == NULL) {
			ret = false;
			break;
		}

	} while (0);


	return ret;
}

/*---------------------------------------------------------------------------------------------
//	@brief	破棄
---------------------------------------------------------------------------------------------*/
void KLSprite::Destroy()
{
	SAFE_DELETE(p_sprite_batch_);
	SAFE_DELETE(p_sprite_font_);
}

/*---------------------------------------------------------------------------------------------
//	@brief	描画開始
//	@param	CommonStates* pStates	：コモンステータス
---------------------------------------------------------------------------------------------*/
void KLSprite::BeginSprite(CommonStates* pStates)
{
	p_sprite_batch_->Begin(SpriteSortMode_Deferred, pStates->NonPremultiplied());
}

/*---------------------------------------------------------------------------------------------
//	@brief	描画終了
---------------------------------------------------------------------------------------------*/
void KLSprite::EndSprite()
{
	p_sprite_batch_->End();
}

/*---------------------------------------------------------------------------------------------
//	@brief	スプライト描画
//	@param	LPKLTextureData pTextureData	：描画するテクスチャデータ
//	@param	Vector2			Position		：描画する座標
//	@param	RECT			Rect			：テクスチャ切り取り範囲
//	@param	Vector4			Color			：テクスチャカラー
//	@param	Vector2			Origin			：テクスチャの中心座標
//	@param	float			Rotation		：回転
//	@param	float			Scale			：拡大
---------------------------------------------------------------------------------------------*/
void KLSprite::DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect, Vector4 Color,
							Vector2 Origin, float Rotation, float Scale)
{
	p_sprite_batch_->Draw(pTextureData->p_texture, Position, &Rect, Color, Rotation, Origin, Scale);
}

/*---------------------------------------------------------------------------------------------
//	@brief	文字列描画
---------------------------------------------------------------------------------------------*/
void KLSprite::DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color)
{
	p_sprite_font_->DrawString(p_sprite_batch_, pString, Position, Color);
}


