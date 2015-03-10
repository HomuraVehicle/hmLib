#ifndef HMLIB_CQUEUE_INC
#define HMLIB_CQUEUE_INC 103
#
/*
===hmCLib/cqueue===
���X�g�@�\���

cqueue:v1_03/130204 hmIto
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
#	include <hmLib_v3_04/cdeque.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_04/lib/Debug/cqueue.lib")
#	else
#		pragma comment(lib,"hmLib_v3_04/lib/Release/cqueue.lib")
#	endif
#endif
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
//typedef cdeque_boolian	hmLib_boolian;
typedef cdeque_iterator cqueue_iterator;
typedef cdeque_size_t	cqueue_size_t;
typedef cdeque cqueue;
//�������̏�����
void cqueue_format(cqueue* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cqueue_is_construct(cqueue* ptr);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct_static(cqueue* pQue,void* Begin,void* End,cqueue_size_t ElemSize);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct_dynamic(cqueue* pQue,cqueue_size_t Size,cqueue_size_t ElemSize);
//�o�b�t�@��� �ÓI/���I�͎������f
void cqueue_destruct(cqueue* pQue);
//cqueue���쐬(construct_dynamic���g�p)
cqueue* cqueue_create(cqueue_size_t Size,cqueue_size_t ElemSize);
//cqueue��j��
void cqueue_release(cqueue* pQue);
//move
void cqueue_move(cqueue* from, cqueue* to);
//copy
void cqueue_swap(cqueue* ptr1,cqueue* ptr2);
//�o�b�t�@�̐擪���擾
void* cqueue_getptr(cqueue* pQue);
//�o�b�t�@�ɓ����Ă���T�C�Y
cqueue_size_t cqueue_size(cqueue* pQue);
//�o�b�t�@�Ɏc��������T�C�Y
cqueue_size_t cqueue_rest(cqueue* pQue);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cqueue_empty(cqueue* pQue);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cqueue_full(cqueue* pQue);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cqueue_push(cqueue* pQue,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cqueue_pop(cqueue* pQue);
//�o�b�t�@��begin�֐�
cqueue_iterator cqueue_begin(cqueue* pQue);
//�o�b�t�@��end�֐�
cqueue_iterator cqueue_end(cqueue* pQue);
//cqueue_iterator�̎���iterator��^����
cqueue_iterator cqueue_next(cqueue* pQue,cqueue_iterator itr);
//cqueue_iterator�̑O��iterator��^����
cqueue_iterator cqueue_prev(cqueue* pQue,cqueue_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
