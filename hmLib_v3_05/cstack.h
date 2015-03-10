#ifndef HMLIB_CSTACK_INC
#define HMLIB_CSTACK_INC 103
#
/*
===hmCLib/cstack===
�X�^�b�N�@�\���

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
#	include <hmLib_v3_05/cdeque.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_05/lib/Debug/cstack.lib")
#	else
#		pragma comment(lib,"hmLib_v3_05/lib/Release/cstack.lib")
#	endif
#endif
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
typedef cdeque_iterator cstack_iterator;
typedef cdeque_size_t	cstack_size_t;
typedef cdeque cstack;
//�������̏�����
void cstack_format(cstack* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cstack_is_construct(cstack* ptr);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct_static(cstack* pStk,void* Begin,void* End,cstack_size_t ElemSize);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct_dynamic(cstack* pStk,cstack_size_t Size,cstack_size_t ElemSize);
//�o�b�t�@��� �ÓI/���I�͎������f
void cstack_destruct(cstack* pStk);
//cstack���쐬(construct_dynamic���g�p)
cstack* cstack_create(cstack_size_t Size,cstack_size_t ElemSize);
//cstack��j��
void cstack_release(cstack* pStk);
//move
void cstack_move(cstack* from, cstack* to);
//copy
void cstack_swap(cstack* ptr1,cstack* ptr2);
//�o�b�t�@�̐擪���擾
void* cstack_getptr(cstack* pStk);
//�o�b�t�@�ɓ����Ă���T�C�Y
cstack_size_t cstack_size(cstack* pStk);
//�o�b�t�@�Ɏc��������T�C�Y
cstack_size_t cstack_rest(cstack* pStk);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cstack_empty(cstack* pStk);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cstack_full(cstack* pStk);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cstack_push(cstack* pStk,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cstack_pop(cstack* pStk);
//�o�b�t�@��begin�֐�
cstack_iterator cstack_begin(cstack* pStk);
//�o�b�t�@��end�֐�
cstack_iterator cstack_end(cstack* pStk);
//cstack_iterator�̎���iterator��^����
cstack_iterator cstack_next(cstack* pStk,cstack_iterator itr);
//cstack_iterator�̑O��iterator��^����
cstack_iterator cstack_prev(cstack* pStk,cstack_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
