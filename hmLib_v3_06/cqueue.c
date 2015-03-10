#ifndef HMLIB_CQUEUE_C_INC
#define HMLIB_CQUEUE_C_INC 200
#
#ifndef HMLIB_CQUEUE_INC
#	include <hmLib_v3_06/cqueue.h>
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
void cqueue_format(hmLib_cqueue* ptr){
	cdeque_format(ptr);
}
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cqueue_is_construct(hmLib_cqueue* ptr){
	return cdeque_is_construct(ptr);
}
//���I�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct(hmLib_cqueue* pStk, hmLib_cqueue_size_t Size, hmLib_cqueue_size_t ElemSize) {
	cdeque_construct(pStk, Size, ElemSize);
}
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cqueue_placement_construct(hmLib_cqueue* pStk, hmLib_cqueue_size_t Size, hmLib_cqueue_size_t ElemSize, hmLib_pointer Ptr, hmLib_vFp_p Destructor) {
	cdeque_placement_construct(pStk, Size, ElemSize, Ptr, Destructor);
}
//�o�b�t�@��� �ÓI/���I�͎������f
void cqueue_destruct(hmLib_cqueue* pStk){
	cdeque_destruct(pStk);
}
//move
void cqueue_move(hmLib_cqueue* from, hmLib_cqueue* to){
	cdeque_move(from,to);
}
//copy
void cqueue_swap(hmLib_cqueue* ptr1,hmLib_cqueue* ptr2){
	cdeque_swap(ptr1,ptr2);
}
//�o�b�t�@�̐擪���擾
void* cqueue_getptr(hmLib_cqueue* pStk){
	return cdeque_frontptr(pStk);
}
//�o�b�t�@�ɓ����Ă���T�C�Y
hmLib_cqueue_size_t cqueue_size(hmLib_cqueue* pStk){
	return cdeque_size(pStk);
}
//�o�b�t�@�Ɏc��������T�C�Y
hmLib_cqueue_size_t cqueue_rest(hmLib_cqueue* pStk){
	return cdeque_rest(pStk);
}
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cqueue_empty(hmLib_cqueue* pStk){
	return cdeque_empty(pStk);
}
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cqueue_full(hmLib_cqueue* pStk){
	return cdeque_full(pStk);
}
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cqueue_push(hmLib_cqueue* pStk,const void* Ptr){
	return cdeque_push_back(pStk,Ptr);
}
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cqueue_pop(hmLib_cqueue* pStk){
	return cdeque_pop_front(pStk);
}
//�o�b�t�@��begin�֐�
hmLib_cqueue_iterator cqueue_begin(hmLib_cqueue* pStk){
	return cdeque_begin(pStk);
}
//�o�b�t�@��end�֐�
hmLib_cqueue_iterator cqueue_end(hmLib_cqueue* pStk){
	return cdeque_end(pStk);
}
//hmLib_cqueue_iterator�̎���iterator��^����
hmLib_cqueue_iterator cqueue_next(hmLib_cqueue* pStk,hmLib_cqueue_iterator itr){
	return cdeque_next(pStk,itr);
}
//hmLib_cqueue_iterator�̑O��iterator��^����
hmLib_cqueue_iterator cqueue_prev(hmLib_cqueue* pStk,hmLib_cqueue_iterator itr){
	return cdeque_prev(pStk,itr);
}
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
