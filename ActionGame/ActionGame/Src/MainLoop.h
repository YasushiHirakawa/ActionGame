/****************************************************************************************************
//
//		MainLoop.h
//
//		@brief	���C�����[�v����
//		@author	Yasushi Hirakawa
//		@date	2015/11/24
//
****************************************************************************************************/

#ifndef __MAINLOOP_H__
#define __MAINLOOP_H__


//---------------------------------------------------------------------------------------------
//	include
//---------------------------------------------------------------------------------------------
#include "HirakawaLib/Inc/HirakawaLib.h"

//---------------------------------------------------------------------------------------------
//	define
//---------------------------------------------------------------------------------------------
enum MAINLOOP_STATE
{
	MAINLOOP_INIT = 0,			// ������
	MAINLOOP_WORK,				// ���
	MAINLOOP_DESTROY,			// �j��
	MAX_MAINLOOP_STATE			// �ő�l
};

//---------------------------------------------------------------------------------------------
//	class
//---------------------------------------------------------------------------------------------
class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	int		Update();						// ���C���֐�
	void	Destroy();						// �j��

private:
	// ���C�����[�v�𐧌䂷��֐��|�C���^�̒�`
	int		(MainLoop::*MainLoopFunc[MAX_MAINLOOP_STATE])();

	// �֐��|�C���^�Ăяo���C���f�b�N�X
	MAINLOOP_STATE	main_loop_state_;

	// ���C�����[�v��Ɗ֐�
	int		MainLoopInit();			// ���C�����[�v ������
	int		MainLoopWork();			// ���C�����[�v ���
	int		MainLoopDestroy();		// ���C�����[�v �j��

	// �Q�[����Ɗ֐�
	int		GameInit();				// �Q�[�� ������
	int		GameWork();				// �Q�[�� ���
	int		GameDestroy();			// �Q�[�� �j��

	// �`���Ɗ֐�
	void	DrawInit();				// �`�� ������
	void	DrawWork();				// �`�� ���



	LPHLTextureData		p_texture_data_;
	LPHLTextureData		p_texture_data_alpha_;
	LPHLModelData		p_model_data_;
	//LPHLAudioData		p_audio_data_;

	Vector3				position_;

	Vector2				stick_;
	float				trigger_;
	MOUSE_POSITION		mouse_pos_;
	int					wheel_;
};


#endif //__MAINLOOP_H__