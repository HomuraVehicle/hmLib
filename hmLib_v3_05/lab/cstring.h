#ifndef HMLIB_CSTRING_INC
#define HMLIB_CSTRING_INC 200
#
/*
===cstring===
�����������string�N���X�̋^���\����

cstring:v2_00/131217 hmIto
	�j��I�ύX
		construct��static/dynamic�̍���p�~�Bmalloc/free�ŊǗ�����construct�ƃ|�C���^��^����placement_construct�ɕύX
		�^����hmLib_Prefix��ǉ��B�������AHMLIB_CSTRING_NOPREFIX�Ńv���t�B�b�N�X�����o�[�W�������g����B
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
#ifndef HMLIB_TYPE_INC
#	include <hmLib_v3_05/lab/type.h>
#endif
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_05/lab/lib/Debug/cstring.lib")
#	else
#		pragma comment(lib,"hmLib_v3_05/lab/lib/Release/cstring.lib")
#	endif
#endif
typedef hmLib_uint16 hmLib_cstring_size_t;
typedef unsigned char* hmLib_cstring_iterator;
typedef struct {
	hmLib_vFp_p Destructor;
	unsigned char* Begin;
	unsigned char* End;
}hmLib_cstring;
#ifdef __cplusplus
namespace hmLib{
extern "C"{
typedef hmLib_cstring cstring;
typedef hmLib_cstring_size_t cstring_size_t;
typedef hmLib_cstring_iterator cstring_iterator;
#endif

void cstring_format(hmLib_cstring* str);
void cstring_construct(hmLib_cstring* str, hmLib_cstring_size_t size);
void cstring_placement_construct(hmLib_cstring* str, hmLib_cstring_size_t size, hmLib_pointer ptr, hmLib_vFp_v destructor);
hmLib_boolian cstring_is_construct(hmLib_cstring* str);
void cstring_destruct(hmLib_cstring* str);
void cstring_move(hmLib_cstring* from, hmLib_cstring* to);
void cstring_swap(hmLib_cstring* str1, hmLib_cstring* str2);
unsigned char* cstring_ptr(const hmLib_cstring* str);
hmLib_cstring_size_t cstring_size(const hmLib_cstring* str);
hmLib_cstring_iterator cstring_begin(const hmLib_cstring* str);
hmLib_cstring_iterator cstring_end(const hmLib_cstring* str);
hmLib_cstring_iterator cstring_next(const hmLib_cstring* str, hmLib_cstring_iterator itr);
hmLib_cstring_iterator cstring_prev(const hmLib_cstring* str, hmLib_cstring_iterator itr);
void cstring_putc(hmLib_cstring* str, hmLib_cstring_size_t pos, unsigned char c);
void cstring_puts(hmLib_cstring* str, hmLib_cstring_size_t pos, const unsigned char* p, hmLib_cstring_size_t size);
unsigned char cstring_getc(hmLib_cstring* str, hmLib_cstring_size_t pos);
unsigned char* cstring_gets(hmLib_cstring* str, hmLib_cstring_size_t pos);
#ifdef __cplusplus
}	//extern "C"
}	//namespace hmLib
#endif
#ifdef HMLIB_CSTRING_NOPREFIX
typedef hmLib_cstring cstring;
typedef hmLib_cstring_size_t cstring_size_t;
typedef hmLib_cstring_iterator cstring_iterator;
#endif
#
#endif
