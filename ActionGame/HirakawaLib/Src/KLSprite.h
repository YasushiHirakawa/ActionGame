/****************************************************************************************************
//
//		KLSprite.h
//
//		@brief	KoudoLib スプライト描画管理
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KLSPRITE_H__
#define __KLSPRITE_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "KLCommon.h"
#include "KLDirect3D.h"
#include "KLTexture.h"


//---------------------------------------------------------------------------------------------
//	define
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KLSprite
{
public:
	KLSprite();
	~KLSprite();

	bool Init(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);	// 初期化
	void Destroy();								// 破棄

	void BeginSprite(CommonStates* pStates);	// 描画開始
	void EndSprite();							// 描画終了

	// スプライト描画
	void DrawSprite(LPKLTextureData pTextureData, Vector2 Position, RECT Rect, 
					Vector4 Color = Vector4(1.0F, 1.0F, 1.0F, 1.0F), 
					Vector2 Origin = Vector2(0.0F, 0.0F),
					float Rotation = 0.0F, float Scale = 1.0F);

	// 文字列描画
	void DrawFont(wchar_t* pString, Vector2 Position, XMVECTOR Color = Colors::White);

private:
	SpriteBatch*	p_sprite_batch_;		// スプライトバッチ
	SpriteFont*		p_sprite_font_;			// スプライトフォント
};


#endif //__KLSPRITE_H__