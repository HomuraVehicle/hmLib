#ifndef HMLIB_CQUEUE_C_INC
#define HMLIB_CQUEUE_C_INC 103
#
#ifndef HMLIB_CQUEUE_INC
#	include <hmLib_v3_05/cqueue.h>
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
void cqueue_format(cqueue* ptr){
	cdeque_format(ptr);
}
//���łɏ��������ꂽ���ǂ����̊m�F
hmLib_boolian cqueue_is_construct(cqueue* ptr){
	return cdeque_is_construct(ptr);
}
//�ÓI�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct_static(cqueue* pQue,void* Begin,void* End,cqueue_size_t ElemSize){
	cdeque_construct_static(pQue,Begin,End,ElemSize);
}
//���I�m�ۂɂ���ăo�b�t�@�m��
void cqueue_construct_dynamic(cqueue* pQue,cqueue_size_t Size,cqueue_size_t ElemSize){
	cdeque_construct_dynamic(pQue,Size,ElemSize);
}
//�o�b�t�@��� �ÓI/���I�͎������f
void cqueue_destruct(cqueue* pQue){
	cdeque_destruct(pQue);
}
//cqueue���쐬(construct_dynamic���g�p)
cqueue* cqueue_create(cqueue_size_t Size,cqueue_size_t ElemSize){
	return cdeque_create(Size,ElemSize);
}
//cqueue��j��
void cqueue_release(cqueue* pQue){
	cdeque_release(pQue);
}
//move
void cqueue_move(cqueue* from, cqueue* to){
	cdeque_move(from,to);
}
//copy
void cqueue_swap(cqueue* ptr1,cqueue* ptr2){
	cdeque_swap(ptr1,ptr2);
}
//�o�b�t�@�̐擪���擾
void* cqueue_getptr(cqueue* pQue){
	return cdeque_frontptr(pQue);
}
//�o�b�t�@�ɓ����Ă���T�C�Y
cqueue_size_t cqueue_size(cqueue* pQue){
	return cdeque_size(pQue);
}
//�o�b�t�@�Ɏc��������T�C�Y
cqueue_size_t cqueue_rest(cqueue* pQue){
	return cdeque_rest(pQue);
}
//�o�b�t�@���󂩂ǂ����m�F
hmLib_boolian cqueue_empty(cqueue* pQue){
	return cdeque_empty(pQue);
}
//�o�b�t�@�������ς����ǂ����m�F
hmLib_boolian cqueue_full(cqueue* pQue){
	return cdeque_full(pQue);
}
//�o�b�t�@�Ƀf�[�^��}��
hmLib_boolian cqueue_push(cqueue* pQue,const void* Ptr){
	return cdeque_push_back(pQue,Ptr);
}
//�o�b�t�@�̃f�[�^���폜
hmLib_boolian cqueue_pop(cqueue* pQue){
	return cdeque_pop_front(pQue);
}
//�o�b�t�@��begin�֐�
cqueue_iterator cqueue_begin(cqueue* pQue){
	return cdeque_begin(pQue);
}
//�o�b�t�@��end�֐�
cqueue_iterator cqueue_end(cqueue* pQue){
	return cdeque_end(pQue);
}
//cqueue_iterator�̎���iterator��^����
cqueue_iterator cqueue_next(cqueue* pQue,cqueue_iterator itr){
	return cdeque_next(pQue,itr);
}
//cqueue_iterator�̑O��iterator��^����
cqueue_iterator cqueue_prev(cqueue* pQue,cqueue_iterator itr){
	return cdeque_prev(pQue,itr);
}
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
