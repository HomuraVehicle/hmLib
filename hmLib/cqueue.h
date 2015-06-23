#ifndef HMLIB_CQUEUE_INC
#define HMLIB_CQUEUE_INC 200
#
/*
===hmLib/cqueue===
�X�^�b�N�@�\���
cqueue:v2_00/140214 hmIto
	�j��I�ύX
	construct��static/dynamic�̍���p�~�Bmalloc/free�ŊǗ�����construct�ƃ|�C���^��^����placement_construct�ɕύX
	�^����hmLib_Prefix��ǉ��B�������AHMLIB_CDEQUE_NOPREFIX�Ńv���t�B�b�N�X�����o�[�W�������g����B
cqueue:v1_03/130204
	�ꕔ�֐��̖߂�l�̌^���̃o�O���C��
		hmLib_bool��hmLib_boolian�ɒ���
cqueue:v1_02/130105 hmIto
	format�֐���ǉ�
		�ϐ����������ł��� destruct�ŕK�v�ȏ������s��Ȃ�
	is_construct�֐���ǉ�
		construct����Ă��邩�ǂ����𔻒�ł���
		format����Ă��邱�Ƃ�����
	move�֐���ǉ�
		����̃|�C���^�����������̃|�C���^�ɃI�u�W�F�N�g���̂��ړ�����
	swap�֐���ǉ�
		��̃|�C���^�̒��g�����ւ���
*/
//#undef __cplusplus
#ifndef HMLIB_CDEQUE_INC
#	include <hmLib/cdeque.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#if !(defined(HMLIB_NOLIB) || defined(HMLIB_CQUEUE_NOLIB))
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib/lib/Debug/cqueue.lib")
#	else
#		pragma comment(lib,"hmLib/lib/Release/cqueue.lib")
#	endif
#endif
typedef hmLib_cdeque_iterator hmLib_cqueue_iterator;
typedef hmLib_cdeque_size_t	hmLib_cqueue_size_t;
typedef hmLib_cdeque hmLib_cqueue;
#ifdef __cplusplus
namespace hmLib{
	typedef hmLib_cqueue_iterator cqueue_iterator;
	typedef hmLib_cqueue_size_t cqueue_size_t;
	typedef hmLib_cqueue cqueue;
extern "C"{
#endif
//�������̏�����
void cqueue_format(hmLib_cqueue* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cqueue_is_construct(hmLib_cqueue* ptr);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct(hmLib_cqueue* pStk, hmLib_cqueue_size_t Size, hmLib_cqueue_size_t ElemSize);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cqueue_placement_construct(hmLib_cqueue* pStk, hmLib_cqueue_size_t Size, hmLib_cqueue_size_t ElemSize, hmLib_pointer Ptr, hmLib_vFp_p Destructor);
//�o�b�t�@��� �ÓI/���I�͎������f
void cqueue_destruct(hmLib_cqueue* pStk);
//move
void cqueue_move(hmLib_cqueue* from, hmLib_cqueue* to);
//copy
void cqueue_swap(hmLib_cqueue* ptr1,hmLib_cqueue* ptr2);
//�o�b�t�@�̐擪���擾
void* cqueue_getptr(hmLib_cqueue* pStk);
//�o�b�t�@�ɓ����Ă���T�C�Y
hmLib_cqueue_size_t cqueue_size(hmLib_cqueue* pStk);
//�o�b�t�@�Ɏc��������T�C�Y
hmLib_cqueue_size_t cqueue_rest(hmLib_cqueue* pStk);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cqueue_empty(hmLib_cqueue* pStk);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cqueue_full(hmLib_cqueue* pStk);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cqueue_push(hmLib_cqueue* pStk,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cqueue_pop(hmLib_cqueue* pStk);
//�o�b�t�@��begin�֐�
hmLib_cqueue_iterator cqueue_begin(hmLib_cqueue* pStk);
//�o�b�t�@��end�֐�
hmLib_cqueue_iterator cqueue_end(hmLib_cqueue* pStk);
//hmLib_cqueue_iterator�̎���iterator��^����
hmLib_cqueue_iterator cqueue_next(hmLib_cqueue* pStk,hmLib_cqueue_iterator itr);
//hmLib_cqueue_iterator�̑O��iterator��^����
hmLib_cqueue_iterator cqueue_prev(hmLib_cqueue* pStk,hmLib_cqueue_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#if defined(HMLIB_CQUEUE_NOPREFIX) || defined(HMLIB_NOPREFIX)
typedef hmLib_cqueue cqueue;
typedef hmLib_cqueue_size_t cqueue_size_t;
typedef hmLib_cqueue_iterator cqueue_iterator;
#endif
#
#endif
