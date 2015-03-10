#ifndef HMLIB_CSTACK_INC
#define HMLIB_CSTACK_INC 200
#
/*
===hmLib/cstack===
�X�^�b�N�@�\���
cstack:v2_00/140214 hmIto
	�j��I�ύX
	construct��static/dynamic�̍���p�~�Bmalloc/free�ŊǗ�����construct�ƃ|�C���^��^����placement_construct�ɕύX
	�^����hmLib_Prefix��ǉ��B�������AHMLIB_CDEQUE_NOPREFIX�Ńv���t�B�b�N�X�����o�[�W�������g����B
cstack:v1_03/130204
	�ꕔ�֐��̖߂�l�̌^���̃o�O���C��
		hmLib_bool��hmLib_boolian�ɒ���
cstack:v1_02/130105 hmIto
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
#	include <hmLib_v3_06/cdeque.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#if !(defined(HMLIB_NOLIB) || defined(HMLIB_CSTACK_NOLIB))
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_06/lib/Debug/cstack.lib")
#	else
#		pragma comment(lib,"hmLib_v3_06/lib/Release/cstack.lib")
#	endif
#endif
typedef hmLib_cdeque_iterator hmLib_cstack_iterator;
typedef hmLib_cdeque_size_t	hmLib_cstack_size_t;
typedef hmLib_cdeque hmLib_cstack;
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
//�������̏�����
void cstack_format(hmLib_cstack* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cstack_is_construct(hmLib_cstack* ptr);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct(hmLib_cstack* pStk, hmLib_cstack_size_t Size, hmLib_cstack_size_t ElemSize);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cstack_placement_construct(hmLib_cstack* pStk, hmLib_cstack_size_t Size, hmLib_cstack_size_t ElemSize, hmLib_pointer Ptr, hmLib_vFp_p Destructor);
//�o�b�t�@��� �ÓI/���I�͎������f
void cstack_destruct(hmLib_cstack* pStk);
//move
void cstack_move(hmLib_cstack* from, hmLib_cstack* to);
//copy
void cstack_swap(hmLib_cstack* ptr1,hmLib_cstack* ptr2);
//�o�b�t�@�̐擪���擾
void* cstack_getptr(hmLib_cstack* pStk);
//�o�b�t�@�ɓ����Ă���T�C�Y
hmLib_cstack_size_t cstack_size(hmLib_cstack* pStk);
//�o�b�t�@�Ɏc��������T�C�Y
hmLib_cstack_size_t cstack_rest(hmLib_cstack* pStk);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cstack_empty(hmLib_cstack* pStk);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cstack_full(hmLib_cstack* pStk);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cstack_push(hmLib_cstack* pStk,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cstack_pop(hmLib_cstack* pStk);
//�o�b�t�@��begin�֐�
hmLib_cstack_iterator cstack_begin(hmLib_cstack* pStk);
//�o�b�t�@��end�֐�
hmLib_cstack_iterator cstack_end(hmLib_cstack* pStk);
//hmLib_cstack_iterator�̎���iterator��^����
hmLib_cstack_iterator cstack_next(hmLib_cstack* pStk,hmLib_cstack_iterator itr);
//hmLib_cstack_iterator�̑O��iterator��^����
hmLib_cstack_iterator cstack_prev(hmLib_cstack* pStk,hmLib_cstack_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#if defined(HMLIB_CSTACK_NOPREFIX) || defined(HMLIB_NOPREFIX)
typedef hmLib_cstack cstack;
typedef hmLib_cstack_size_t cstack_size_t;
typedef hmLib_cstack_iterator cstack_iterator;
#endif
#
#endif
