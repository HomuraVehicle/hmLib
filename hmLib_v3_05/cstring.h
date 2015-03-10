#ifndef HMLIB_CSTRING_INC
#define HMLIB_CSTRING_INC 103
#
/*
===cstring===
�����������string�N���X�̋^���\����

cstring:v1_03/130204 hmIto
	�ꕔ�֐��̖߂�l�̌^���̃o�O���C��
		hmLib_bool��hmLib_boolian�����
	swap�֐��̃o�O���C��
		���̂�->�A�N�Z�X���Z�q���g���Ă���
cstring:v1_02/130105 hmIto
	format�֐���ǉ�
		�ϐ����������ł��� destruct�ŕK�v�ȏ������s��Ȃ�
	is_construct�֐���ǉ�
		construct����Ă��邩�ǂ����𔻒�ł���
		format����Ă��邱�Ƃ�����
	move�֐���ǉ�
		����̃|�C���^�����������̃|�C���^�ɃI�u�W�F�N�g���̂��ړ�����
	swap�֐���ǉ�
		��̃|�C���^�̒��g�����ւ���
cstring:v1_01/121128 hmIto
	next/prev�֐���ǉ�
	C++�ɑΉ�
	dynamic/static���t���O�Ŋo���Ă����悤�ɕύX
		destruct�̓t���O�Ɋ�Â��Ĕ��f
cstring:v1_00/121013 hmIto
	cstring���쐬
*/
#ifndef HMLIB_BYTEBASE_TYPE_INC
#	include <hmLib_v3_05/bytebase_type.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_05/lib/Debug/cstring.lib")
#	else
#		pragma comment(lib,"hmLib_v3_05/lib/Release/cstring.lib")
#	endif
#endif
#ifdef __cplusplus
namespace hmLib{
extern "C"{
#endif
typedef hmLib_uint16 cstring_size_t;
typedef unsigned char* cstring_iterator;
typedef struct{
	hmLib_boolian DynamicFlag;
	unsigned char* Begin;
	unsigned char* End;
}cstring;
void cstring_format(cstring* str);
hmLib_boolian cstring_is_construct(cstring* str);
cstring* cstring_create(cstring_size_t size);
void cstring_release(cstring* str);
void cstring_construct_dynamic(cstring* str,cstring_size_t size);
void cstring_construct_static(cstring* str,unsigned char* Begin,unsigned char* End);
void cstring_destruct(cstring* str);
void cstring_move(cstring* from, cstring* to);
void cstring_swap(cstring* str1, cstring* str2);
unsigned char* cstring_ptr(const cstring* str);
cstring_size_t cstring_size(const cstring* str);
cstring_iterator cstring_begin(const cstring* str);
cstring_iterator cstring_end(const cstring* str);
cstring_iterator cstring_next(const cstring* str,cstring_iterator itr);
cstring_iterator cstring_prev(const cstring* str,cstring_iterator itr);
void cstring_putc(cstring* str,cstring_size_t pos,unsigned char c);
void cstring_puts(cstring* str,cstring_size_t pos,const unsigned char* p,cstring_size_t size);
unsigned char cstring_getc(cstring* str,cstring_size_t pos);
unsigned char* cstring_gets(cstring* str, cstring_size_t pos);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#
#endif
