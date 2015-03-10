#ifndef HMLIB_CDEQUE_INC
#define HMLIB_CDEQUE_INC 103
#
/*
===hmCLib/cdeque===
�L���[�@�\�̒�

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
		�����̔z����g����cdeque�̃o�b�t�@���쐬/���
	dynamic_construct/destruct�ǉ�
		malloc���g����cdeque�̃o�b�t�@���쐬/���
	create/release�֐���dynamic_construct/destruct�Ɉˑ�����悤�ύX
		create/release�֐��́Acdeque���M��malloc�ɂ��Čg���B
*/
//#undef __cplusplus
#ifndef HMLIB_BYTEBASETYPE_INC
#	include <hmLib_v3_05/bytebase_type.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_05/lib/Debug/cdeque.lib")
#	else
#		pragma comment(lib,"hmLib_v3_05/lib/Release/cdeque.lib")
#	endif
#endif
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
//typedef hmLib_boolian	hmLib_boolian;
typedef void*			cdeque_iterator;
typedef hmLib_uint16	cdeque_size_t;
typedef struct{
	hmLib_boolian DynamicFlag;
	cdeque_size_t ElemSize;
	void* Begin;
	void* End;
	void* BufBegin;
	void* BufEnd;
}cdeque;
//�������̏�����
void cdeque_format(cdeque* ptr);
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cdeque_is_construct(cdeque* ptr);
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cdeque_construct_static(cdeque* pDque,void* Begin,void* End,cdeque_size_t ElemSize);
//���I�m�ۂɂ���ăo�b�t�@�m��
void cdeque_construct_dynamic(cdeque* pDque,cdeque_size_t Size,cdeque_size_t ElemSize);
//�o�b�t�@��� �ÓI/���I�͎������f
void cdeque_destruct(cdeque* pDque);
//cdeque���쐬(construct_dynamic���g�p)
cdeque* cdeque_create(cdeque_size_t Size,cdeque_size_t ElemSize);
//cdeque��j��
void cdeque_release(cdeque* pDque);
//move
void cdeque_move(cdeque* from, cdeque* to);
//copy
void cdeque_swap(cdeque* ptr1,cdeque* ptr2);
//�o�b�t�@�̐擪���擾
void* cdeque_frontptr(cdeque* pDque);
//�o�b�t�@�̐擪���擾
void* cdeque_backptr(cdeque* pDque);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cdeque_push_front(cdeque* pDque,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cdeque_pop_front(cdeque* pDque);
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cdeque_push_back(cdeque* pDque,const void* Ptr);
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cdeque_pop_back(cdeque* pDque);
//�o�b�t�@�ɓ����Ă���T�C�Y
cdeque_size_t cdeque_size(cdeque* pDque);
//�o�b�t�@�Ɏc��������T�C�Y
cdeque_size_t cdeque_rest(cdeque* pDque);
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cdeque_empty(cdeque* pDque);
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cdeque_full(cdeque* pDque);
//�o�b�t�@��begin�֐�
cdeque_iterator cdeque_begin(cdeque* pDque);
//�o�b�t�@��end�֐�
cdeque_iterator cdeque_end(cdeque* pDque);
//cdeque_iterator�̎���iterator��^����
cdeque_iterator cdeque_next(cdeque* pDque,cdeque_iterator itr);
//cdeque_iterator�̑O��iterator��^����
cdeque_iterator cdeque_prev(cdeque* pDque,cdeque_iterator itr);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
