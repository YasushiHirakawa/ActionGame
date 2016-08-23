/****************************************************************************************************
//
//		KLTexture.h
//
//		@brief	KoudoLib テクスチャ管理
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KLTEXTURE_H__
#define __KLTEXTURE_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "KLCommon.h"
#include "KLDirect3D.h"


//---------------------------------------------------------------------------------------------
//	define
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//	struct
//--------------------------------------------------------------------------------------------- 
// テクスチャデータ構造体
typedef struct KLTextureData
{
	ID3D11ShaderResourceView*	p_texture;				// テクスチャデータ
	wchar_t						p_file_name[kStrMax];	// モデルファイル名

	KLTextureData()
	{
		p_texture = NULL;
		p_file_name[0] = '\0';
	}
} *LPKLTextureData;

// テクスチャデータリスト構造体
typedef struct KLTextureDataList
{
	KLTextureData*			p_texture_data;	// テクスチャデータ
	KLTextureDataList*		p_next;			// リストの次データ
	int						ref_counter;	// 参照カウンタ

	KLTextureDataList()
	{
		p_texture_data	= NULL;
		p_next			= NULL;
		ref_counter		= 1;
	}
} *LPKLTextureDataList;


//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KLTexture
{
public:
	KLTexture();
	~KLTexture();

	bool Init();			// 初期化
	void Destroy();			// 破棄

	// テクスチャデータ作成
	bool CreateTextureData(ID3D11Device* pDevice, const wchar_t* pFilename, LPKLTextureData* ppTextureData);

	// テクスチャデータ解放
	bool ReleaseTextureData(LPKLTextureData pTextureData);

private:
	LPKLTextureDataList		p_texture_data_list_top_;	// テクスチャデータリストのトップ
};


#endif //__KLTEXTURE_H__