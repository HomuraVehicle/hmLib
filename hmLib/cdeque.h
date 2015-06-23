#ifndef HMLIB_CDEQUE_INC
#define HMLIB_CDEQUE_INC 200
#
/*
===hmCLib/hmLib_cdeque===
�L���[�@�\�̒�
cdeque:v2_00/140214 hmIto
	�j��I�ύX
	construct��static/dynamic�̍���p�~�Bmalloc/free�ŊǗ�����construct�ƃ|�C���^��^����placement_construct�ɕύX
	�^����hmLib_Prefix��ǉ��B�������AHMLIB_CDEQUE_NOPREFIX�Ńv���t�B�b�N�X�����o�[�W�������g����B
cdeque:v1_03/130204
	�ꕔ�֐��̖߂�l�̌^���̃o�O���C��
		hmLib_bool��hmLib_boolian�ɒ���
	swap�֐��̃o�O���C��
		���̂�->�A�N�Z�X���Z�q���g���Ă���
cdeque_v1_02/121128 hmIto
	format�֐���ǉ�
		�ϐ����������ł��� destruct�ŕK�v�ȏ������s��Ȃ�
	is_construct�֐���ǉ�
		construct����Ă��邩�ǂ����𔻒�ł���
		format����Ă��邱�Ƃ�����
	move�֐���ǉ�
		����̃|�C���^�����������̃|�C���^�ɃI�u�W�F�N�g���̂��ړ�����
	swap�֐���ǉ�
		��̃|�C���^�̒��g�����ւ���
cdeque_v1_01/121009 hmIto
	static_construct/destruct�ǉ�
		�����̔z����g����hmLib_cdeque�̃o�b�t�@���쐬/���
	dynamic_construct/destruct�ǉ�
		malloc���g����hmLib_cdeque�̃o�b�t�@���쐬/���
	create/release�֐���dynamic_construct/destruct�Ɉˑ�����悤�ύX
		create/release�֐��́AhmLib_cdeque���M��malloc�ɂ��Čg���B
*/
//#undef __cplusplus
#ifndef HMLIB_BYTEBASETYPE_INC
#	include <hmLib/type.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#if !(defined(HMLIB_NOLIB) || defined(HMLIB_CDEQUE_NOLIB))
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib/lib/Debug/cdeque.lib")
#	else
#		pragma comment(lib,"hmLib/lib/Release/cdeque.lib")
#	endif
#endif
typedef void*			hmLib_cdeque_iterator;
typedef hmLib_uint16	hmLib_cdeque_size_t;
typedef struct{
	hmLib_vFp_p Destructor;
	hmLib_cdeque_size_t ElemSize;
	void* Begin;
	void* End;
	void* BufBegin;
	void* BufEnd;
}hmLib_cdeque;
#ifdef __cplusplus
namespace hmLib{
extern "C"{
typedef hmLib_cdeque hmLib_cdeque;
typedef hmLib_cdeque_size_t hmLib_cdeque_size_t;
typedef hmLib_cdeque_iterator hmLib_cdeque_iterator;
#endif
//typedef hmLib_boolian	hmLib_boolian;

//�������̏�����
void cdeque_format(hmLib_cdeque* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cdeque_is_construct(hmLib_cdeque* ptr);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cdeque_construct(hmLib_cdeque* pDque, hmLib_cdeque_size_t Size, hmLib_cdeque_size_t ElemSize);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cdeque_placement_construct(hmLib_cdeque* pDque, hmLib_cdeque_size_t Size, hmLib_cdeque_size_t ElemSize, hmLib_pointer Ptr, hmLib_vFp_p Destructor);
//�o�b�t�@��� �ÓI/���I�͎������f
void cdeque_destruct(hmLib_cdeque* pDque);
//move
void cdeque_move(hmLib_cdeque* from, hmLib_cdeque* to);
//copy
void cdeque_swap(hmLib_cdeque* ptr1,hmLib_cdeque* ptr2);
//�o�b�t�@�̐擪���擾
void* cdeque_frontptr(hmLib_cdeque* pDque);
//�o�b�t�@�̐擪���擾
void* cdeque_backptr(hmLib_cdeque* pDque);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cdeque_push_front(hmLib_cdeque* pDque,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cdeque_pop_front(hmLib_cdeque* pDque);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cdeque_push_back(hmLib_cdeque* pDque,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cdeque_pop_back(hmLib_cdeque* pDque);
//�o�b�t�@�ɓ����Ă���T�C�Y
hmLib_cdeque_size_t cdeque_size(hmLib_cdeque* pDque);
//�o�b�t�@�Ɏc��������T�C�Y
hmLib_cdeque_size_t cdeque_rest(hmLib_cdeque* pDque);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cdeque_empty(hmLib_cdeque* pDque);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cdeque_full(hmLib_cdeque* pDque);
//�o�b�t�@��begin�֐�
hmLib_cdeque_iterator cdeque_begin(hmLib_cdeque* pDque);
//�o�b�t�@��end�֐�
hmLib_cdeque_iterator cdeque_end(hmLib_cdeque* pDque);
//hmLib_cdeque_iterator�̎���iterator��^����
hmLib_cdeque_iterator cdeque_next(hmLib_cdeque* pDque,hmLib_cdeque_iterator itr);
//hmLib_cdeque_iterator�̑O��iterator��^����
hmLib_cdeque_iterator cdeque_prev(hmLib_cdeque* pDque,hmLib_cdeque_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#if defined(HMLIB_CDEQUE_NOPREFIX) || defined(HMLIB_NOPREFIX)
typedef hmLib_cdeque cdeque;
typedef hmLib_cdeque_size_t cdeque_size_t;
typedef hmLib_cdeque_iterator cdeque_iterator;
#endif
#
#endif
