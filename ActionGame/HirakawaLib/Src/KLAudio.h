/****************************************************************************************************
//
//		KLAudio.h
//
//		@brief	KoudoLib �T�E���h�Ǘ�
//		@author	Yasushi Hirakawa
//		@date	2016/08/23
//
****************************************************************************************************/

#ifndef __KLAUDIO_H__
#define __KLAUDIO_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "KLCommon.h"

//---------------------------------------------------------------------------------------------
//	struct
//--------------------------------------------------------------------------------------------- 
// �I�[�f�B�I�f�[�^�\����
typedef struct KLAudioData
{
	std::unique_ptr<SoundEffectInstance>	p_audio_instance;		// �I�[�f�B�I�C���X�^���X�f�[�^
	wchar_t									p_file_name[kStrMax];	// ���f���t�@�C����

	KLAudioData()
	{
		p_audio_instance = NULL;
		p_file_name[0]	= '\0';
	}

	// �Đ�
	void Play(bool Loop = false) { p_audio_instance->Play(Loop); }
	// ��~
	inline void Stop() { p_audio_instance->Stop(); }
	// �ꎞ��~
	inline void Pause() { p_audio_instance->Pause(); }
	// �{�����[���ݒ�
	inline void SetVolume(float Volume) { p_audio_instance->SetVolume(Volume); }
	// �s�b�`�ݒ�
	inline void SetPitch(float Pitch) { p_audio_instance->SetPitch(Pitch); }
	// �p���ݒ�
	inline void SetPan(float Pan) { p_audio_instance->SetPan(Pan); }

} *LPKLAudioData;

// �I�[�f�B�I�f�[�^���X�g�\����
typedef struct KLAudioDataList
{
	KLAudioData*			p_audio_data;	// �I�[�f�B�I�f�[�^
	SoundEffect*			p_audio_origin;	// �I�[�f�B�I�̌��f�[�^
	KLAudioDataList*		p_next;			// ���X�g�̎��f�[�^
	int						ref_counter;	// �Q�ƃJ�E���^

	KLAudioDataList()
	{
		p_audio_data	= NULL;
		p_audio_origin	= NULL;
		p_next			= NULL;
		ref_counter		= 1;
	}
} *LPKLAudioDataList;

//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class KLAudio
{
public:
	KLAudio();
	~KLAudio();

	bool Init();				// ������
	void Destroy();				// �j��
	void Update();				// �X�V

	// �I�[�f�B�I�f�[�^�ǂݍ���
	bool	CreateAudioDataFromWave(const wchar_t* pFilename, LPKLAudioData* ppAudioData);

	// �I�[�f�B�I�f�[�^���
	bool	ReleaseAudioData(LPKLAudioData pAudioData);

private:
	AudioEngine*		p_audio_engine_;		// �I�[�f�B�I�G���W��
	LPKLAudioDataList	p_audio_data_list_top_;	// �I�[�f�B�I�f�[�^���X�g�擪
};


#endif //__KLAUDIO_H__