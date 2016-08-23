/****************************************************************************************************
//
//		KLModel.h
//
//		@brief	KoudoLib ���f���`��Ǘ�
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
const int	kMaxLights = IEffectLights::MaxDirectionalLights;	// ���C�g�̍ő吔

//---------------------------------------------------------------------------------------------
//	struct
//--------------------------------------------------------------------------------------------- 
// ���f���f�[�^�\����
typedef struct KLModelData
{
	std::unique_ptr<Model>	p_model;				// ���f���f�[�^
	wchar_t					p_file_name[kStrMax];	// ���f���t�@�C����

	KLModelData()
	{
		p_model			= NULL;
		p_file_name[0]	= '\0';
	}
} *LPKLModelData;

// ���f���f�[�^���X�g�\����
typedef struct KLModelDataList
{
	KLModelData*			p_model_data;	// ���f���f�[�^
	KLModelDataList*		p_next;			// ���X�g�̎��f�[�^
	int						ref_counter;	// �Q�ƃJ�E���^

	KLModelDataList()
	{
		p_model_data	= NULL;
		p_next			= NULL;
		ref_counter		= 1;
	}
} *LPKLModelDataList;

// ���C�g���
struct KLLightInfo
{
	bool		enable;				// �L���t���O
	Vector3		diffuse_color;		// �f�B�q���[�Y�J���[
	Vector3		ambient_color;		// �A���r�G���g�J���[
	Vector3		specular_color;		// �X�y�L�����[�J���[
	Vector3		direction;			// ����

	KLLightInfo()
	{
		enable			= false;
		diffuse_color	= Vector3(1.0F, 1.0F, 1.0F);
		ambient_color	= Vector3(0.25F, 0.25F, 0.25F);
		specular_color	= Vector3(0.0F, 0.0F, 0.0F);
		direction		= Vector3(0.0F, 0.0F, 1.0F);
	}
};

// �t�H�O���
struct KLFogInfo
{
	bool		enable;		// �L���t���O
	Vector3		color;		// �f�B�q���[�Y�J���[
	float		start;		// �J�n����
	float		end;		// �I������

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

	bool Init(ID3D11Device* pDevice);	// ������
	void Destroy();						// �j��
	void Update();						// �X�V

	// ���f���f�[�^�쐬
	bool CreateModelData(ID3D11Device* pDevice, const wchar_t* pFilename, LPKLModelData* ppModelData);
	// ���f���f�[�^���
	bool ReleaseModelData(LPKLModelData pModelData);

	// ���C�g���̎擾�E�ݒ�
	KLLightInfo GetLightInfo() { return light_info_; };
	void SetLightInfo(KLLightInfo LightInfo) { light_info_ = LightInfo; update_flag_ = true; }

	// �t�H�O���̎擾�E�ݒ�
	inline KLFogInfo GetFogInfo() { return fog_info_; }
	inline void SetFogInfo(KLFogInfo FogInfo) { fog_info_ = FogInfo; update_flag_ = true; }

private:
	EffectFactory*		p_effect_factory;			// �G�t�F�N�g�t�@�N�g���[
	LPKLModelDataList	p_model_data_list_top_;		// ���f���f�[�^���X�g�̃g�b�v
	KLLightInfo			light_info_;				// ���C�g���
	KLFogInfo			fog_info_;					// �t�H�O���
	bool				update_flag_;				// �X�V�t���O
};


#endif //__KLMODEL_H__