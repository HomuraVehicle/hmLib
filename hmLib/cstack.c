#ifndef HMLIB_CSTACK_C_INC
#define HMLIB_CSTACK_C_INC 200
#
#ifndef HMLIB_CSTACK_INC
#	include <hmLib_v3_06/cstack.h>
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
void cstack_format(hmLib_cstack* ptr){
	cdeque_format(ptr);
}
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cstack_is_construct(hmLib_cstack* ptr){
	return cdeque_is_construct(ptr);
}
//���I�m�ۂɂ���ăo�b�t�@�m��
void cstack_construct(hmLib_cstack* pStk, hmLib_cstack_size_t Size, hmLib_cstack_size_t ElemSize) {
	cdeque_construct(pStk, Size, ElemSize);
}
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cstack_placement_construct(hmLib_cstack* pStk, hmLib_cstack_size_t Size, hmLib_cstack_size_t ElemSize, hmLib_pointer Ptr, hmLib_vFp_p Destructor) {
	cdeque_placement_construct(pStk, Size, ElemSize, Ptr, Destructor);
}
//�o�b�t�@��� �ÓI/���I�͎������f
void cstack_destruct(hmLib_cstack* pStk){
	cdeque_destruct(pStk);
}
//move
void cstack_move(hmLib_cstack* from, hmLib_cstack* to){
	cdeque_move(from,to);
}
//copy
void cstack_swap(hmLib_cstack* ptr1,hmLib_cstack* ptr2){
	cdeque_swap(ptr1,ptr2);
}
//�o�b�t�@�̐擪���擾
void* cstack_getptr(hmLib_cstack* pStk){
	return cdeque_backptr(pStk);
}
//�o�b�t�@�ɓ����Ă���T�C�Y
hmLib_cstack_size_t cstack_size(hmLib_cstack* pStk){
	return cdeque_size(pStk);
}
//�o�b�t�@�Ɏc��������T�C�Y
hmLib_cstack_size_t cstack_rest(hmLib_cstack* pStk){
	return cdeque_rest(pStk);
}
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cstack_empty(hmLib_cstack* pStk){
	return cdeque_empty(pStk);
}
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cstack_full(hmLib_cstack* pStk){
	return cdeque_full(pStk);
}
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cstack_push(hmLib_cstack* pStk,const void* Ptr){
	return cdeque_push_back(pStk,Ptr);
}
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cstack_pop(hmLib_cstack* pStk){
	return cdeque_pop_back(pStk);
}
//�o�b�t�@��begin�֐�
hmLib_cstack_iterator cstack_begin(hmLib_cstack* pStk){
	return cdeque_begin(pStk);
}
//�o�b�t�@��end�֐�
hmLib_cstack_iterator cstack_end(hmLib_cstack* pStk){
	return cdeque_end(pStk);
}
//hmLib_cstack_iterator�̎���iterator��^����
hmLib_cstack_iterator cstack_next(hmLib_cstack* pStk,hmLib_cstack_iterator itr){
	return cdeque_next(pStk,itr);
}
//hmLib_cstack_iterator�̑O��iterator��^����
hmLib_cstack_iterator cstack_prev(hmLib_cstack* pStk,hmLib_cstack_iterator itr){
	return cdeque_prev(pStk,itr);
}
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
