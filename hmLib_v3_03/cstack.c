#ifndef HMLIB_CSTACK_C_INC
#define HMLIB_CSTACK_C_INC 103
#
#ifndef HMLIB_CSTACK_INC
#	include "cstack.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif
#include <stdlib.h>
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
//�������̏�����
void cstack_format(cstack* ptr){
	cdeque_format(ptr);
}
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cstack_is_construct(cstack* ptr){
	return cdeque_is_construct(ptr);
}
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct_static(cstack* pStk,void* Begin,void* End,cstack_size_t ElemSize){
	cdeque_construct_static(pStk,Begin,End,ElemSize);
}
//���I�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct_dynamic(cstack* pStk,cstack_size_t Size,cstack_size_t ElemSize){
	cdeque_construct_dynamic(pStk,Size,ElemSize);
}
//�o�b�t�@��� �ÓI/���I�͎������f
void cstack_destruct(cstack* pStk){
	cdeque_destruct(pStk);
}
//cstack���쐬(construct_dynamic���g�p)
cstack* cstack_create(cstack_size_t Size,cstack_size_t ElemSize){
	return cdeque_create(Size,ElemSize);
}
//cstack��j��
void cstack_release(cstack* pStk){
	cdeque_release(pStk);
}
//move
void cstack_move(cstack* from, cstack* to){
	cdeque_move(from,to);
}
//copy
void cstack_swap(cstack* ptr1,cstack* ptr2){
	cdeque_swap(ptr1,ptr2);
}
//�o�b�t�@�̐擪���擾
void* cstack_getptr(cstack* pStk){
	return cdeque_backptr(pStk);
}
//�o�b�t�@�ɓ����Ă���T�C�Y
cstack_size_t cstack_size(cstack* pStk){
	return cdeque_size(pStk);
}
//�o�b�t�@�Ɏc��������T�C�Y
cstack_size_t cstack_rest(cstack* pStk){
	return cdeque_rest(pStk);
}
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cstack_empty(cstack* pStk){
	return cdeque_empty(pStk);
}
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cstack_full(cstack* pStk){
	return cdeque_full(pStk);
}
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cstack_push(cstack* pStk,const void* Ptr){
	return cdeque_push_back(pStk,Ptr);
}
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cstack_pop(cstack* pStk){
	return cdeque_pop_back(pStk);
}
//�o�b�t�@��begin�֐�
cstack_iterator cstack_begin(cstack* pStk){
	return cdeque_begin(pStk);
}
//�o�b�t�@��end�֐�
cstack_iterator cstack_end(cstack* pStk){
	return cdeque_end(pStk);
}
//cstack_iterator�̎���iterator��^����
cstack_iterator cstack_next(cstack* pStk,cstack_iterator itr){
	return cdeque_next(pStk,itr);
}
//cstack_iterator�̑O��iterator��^����
cstack_iterator cstack_prev(cstack* pStk,cstack_iterator itr){
	return cdeque_prev(pStk,itr);
}
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
