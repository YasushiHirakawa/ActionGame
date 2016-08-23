/****************************************************************************************************
//
//		KLModel.h
//
//		@brief	KoudoLib モデル描画管理
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KLMODEL_H__
#define __KLMODEL_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "KLCommon.h"
#include "KLDirect3D.h"

//---------------------------------------------------------------------------------------------
//	const
//--------------------------------------------------------------------------------------------- 
const int	kMaxLights = IEffectLights::MaxDirectionalLights;	// ライトの最大数

//---------------------------------------------------------------------------------------------
//	struct
//--------------------------------------------------------------------------------------------- 
// モデルデータ構造体
typedef struct KLModelData
{
	std::unique_ptr<Model>	p_model;				// モデルデータ
	wchar_t					p_file_name[kStrMax];	// モデルファイル名

	KLModelData()
	{
		p_model			= NULL;
		p_file_name[0]	= '\0';
	}
} *LPKLModelData;

// モデルデータリスト構造体
typedef struct KLModelDataList
{
	KLModelData*			p_model_data;	// モデルデータ
	KLModelDataList*		p_next;			// リストの次データ
	int						ref_counter;	// 参照カウンタ

	KLModelDataList()
	{
		p_model_data	= NULL;
		p_next			= NULL;
		ref_counter		= 1;
	}
} *LPKLModelDataList;

// ライト情報
struct KLLightInfo
{
	bool		enable;				// 有効フラグ
	Vector3		diffuse_color;		// ディヒューズカラー
	Vector3		ambient_color;		// アンビエントカラー
	Vector3		specular_color;		// スペキュラーカラー
	Vector3		direction;			// 方向

	KLLightInfo()
	{
		enable			= false;
		diffuse_color	= Vector3(1.0F, 1.0F, 1.0F);
		ambient_color	= Vector3(0.25F, 0.25F, 0.25F);
		specular_color	= Vector3(0.0F, 0.0F, 0.0F);
		direction		= Vector3(0.0F, 0.0F, 1.0F);
	}
};

// フォグ情報
struct KLFogInfo
{
	bool		enable;		// 有効フラグ
	Vector3		color;		// ディヒューズカラー
	float		start;		// 開始距離
	float		end;		// 終了距離

	KLFogInfo()
	{
		enable	= false;
		color	= Vector3(1.0F, 1.0F, 1.0F);
		start	= 0;
		end		= 100;
	}
};

//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KLModel
{
public:
	KLModel();
	~KLModel();

	bool Init(ID3D11Device* pDevice);	// 初期化
	void Destroy();						// 破棄
	void Update();						// 更新

	// モデルデータ作成
	bool CreateModelData(ID3D11Device* pDevice, const wchar_t* pFilename, LPKLModelData* ppModelData);
	// モデルデータ解放
	bool ReleaseModelData(LPKLModelData pModelData);

	// ライト情報の取得・設定
	KLLightInfo GetLightInfo() { return light_info_; };
	void SetLightInfo(KLLightInfo LightInfo) { light_info_ = LightInfo; update_flag_ = true; }

	// フォグ情報の取得・設定
	inline KLFogInfo GetFogInfo() { return fog_info_; }
	inline void SetFogInfo(KLFogInfo FogInfo) { fog_info_ = FogInfo; update_flag_ = true; }

private:
	EffectFactory*		p_effect_factory;			// エフェクトファクトリー
	LPKLModelDataList	p_model_data_list_top_;		// モデルデータリストのトップ
	KLLightInfo			light_info_;				// ライト情報
	KLFogInfo			fog_info_;					// フォグ情報
	bool				update_flag_;				// 更新フラグ
};


#endif //__KLMODEL_H__