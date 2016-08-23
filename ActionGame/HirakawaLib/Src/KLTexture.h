/****************************************************************************************************
//
//		KLTexture.h
//
//		@brief	KoudoLib �e�N�X�`���Ǘ�
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
// �e�N�X�`���f�[�^�\����
typedef struct KLTextureData
{
	ID3D11ShaderResourceView*	p_texture;				// �e�N�X�`���f�[�^
	wchar_t						p_file_name[kStrMax];	// ���f���t�@�C����

	KLTextureData()
	{
		p_texture = NULL;
		p_file_name[0] = '\0';
	}
} *LPKLTextureData;

// �e�N�X�`���f�[�^���X�g�\����
typedef struct KLTextureDataList
{
	KLTextureData*			p_texture_data;	// �e�N�X�`���f�[�^
	KLTextureDataList*		p_next;			// ���X�g�̎��f�[�^
	int						ref_counter;	// �Q�ƃJ�E���^

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

	bool Init();			// ������
	void Destroy();			// �j��

	// �e�N�X�`���f�[�^�쐬
	bool CreateTextureData(ID3D11Device* pDevice, const wchar_t* pFilename, LPKLTextureData* ppTextureData);

	// �e�N�X�`���f�[�^���
	bool ReleaseTextureData(LPKLTextureData pTextureData);

private:
	LPKLTextureDataList		p_texture_data_list_top_;	// �e�N�X�`���f�[�^���X�g�̃g�b�v
};


#endif //__KLTEXTURE_H__