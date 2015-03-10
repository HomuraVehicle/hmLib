#ifndef HMLIB_UPDATE_INC
#define HMLIB_UPDATE_INC	30303
#define HMLIB_UPDATE_STR	"v3_03_03"
#ifdef HMLIB_UPDATE
#	undef HMLIB_UPDATE
#endif
#define HMLIB_UPDATE HMLIB_UPDATE_INC
#
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#
#define _HMLIB_FN_VER_TO_NUM(VER) #VER
#define HMLIB_FN_VER_TO_NUM(VER) _HMLIB_FN_VER_TO_NUM(VER)
#
#if HMLIB_OUT > 0
#	pragma message("=== hmLib_update_"HMLIB_UPDATE_STR" ===")
#	ifndef HMLIB_VERSION
#		pragma message("hmLib_update : #error : hmLib_version��include����Ă��܂���B")
#	else
#		ifdef HMLIB_UPGRADE
#			pragma message("hmLib_update : update  "HMLIB_FN_VER_TO_NUM(HMLIB_UPDATE))
#			pragma message("hmLib_update : version "HMLIB_FN_VER_TO_NUM(HMLIB_VERSION))
#			pragma message("hmLib_update : upgrade "HMLIB_FN_VER_TO_NUM(HMLIB_UPGRADE))
#		else
#			pragma message("hmLib_update : update  "HMLIB_FN_VER_TO_NUM(HMLIB_UPDATE))
#			pragma message("hmLib_update : version "HMLIB_FN_VER_TO_NUM(HMLIB_VERSION))
#		endif
#
//hmLib_v3_00_00
#if HMLIB_VERSION<30000
#		if HMLIB_OUT>0 && HMLIB_VERSION<30000
#			pragma message("hmLib_update : #error   : ��Ή��o�[�W�����ł��BhmLib_v2��chg_hmLib�@�\�������p���������B")
#		endif
#endif
#
//hmLib_v3_01_01
#if HMLIB_VERSION<30101
#pragma message("hmLib_update : ===hmLib_v3_01===") 
/*
	algorithm.hpp v1_04
		�����_���I���A���[���b�g�I���Ŏw��͈͂��甲���o���A�ȉ���6�֐���ǉ��B
		//�����_���I��
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out);
		//�����_���I�� OutputIterator�͈̔͂𖄂߂�܂�
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator OutBegin,OutputIterator OutEnd);
		//�����_���I�� n��
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out,unsigned int n);
		//���[���b�g�I��
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out);
		//���[���b�g�I�� OutputIterator�͈̔͂𖄂߂�܂�
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator OutBegin,OutputIterator OutEnd);
		//���[���b�g�I�� n��
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out,unsigned int n);
*/
#		ifdef HMLIB_ALGORITHM_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30101<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] roulette_sample���Av1_05(v3_01_01)�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] roulette_sample���Av1_05(v3_01_01)�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	lab/bio/agent.hpp v1_00
		�K���x�A�`���Ȃǂ��ꗥ�Ő���ł���Aagent�N���X�Ƃ��̕t���@�\��V��
*/
#		ifdef HMLIB_AGENT_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30101<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [agent.hpp] hmLib/lab��v3_01_01�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [agent.hpp] hmLib/lab��v3_01_01�Œǉ�����܂����B")
#				endif
#			endif
#		endif
#endif
#
//hmLib_v3_01_02
#if HMLIB_VERSION<30102
/*
	algorithm.hpp v1_05
		�����_���I�����s���ȉ��̃N���X�Ɗ֐���ǉ��B
		//���[���b�g�I���N���X
		template<typename InputIterator,typename fnAssess>
		class roulette_sampler{
		public:
			roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_);
			OutputIterator operator()();
		};
		//���[���b�g�I���N���X�̃r���_�[
		template<typename InputIterator,typename fnAssess>
		roulette_sampler<InputIterator,fnAssess> build_roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_);
*/
#		ifdef HMLIB_ALGORITHM_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30102<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] random_sampler���Av1_05(v3_01_02)�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] random_sampler���Av1_05(v3_01_02)�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	lab/parameter.hpp v0_00
		class parameterizer�ɏ]���āA�ϐ��̓��o�͂���уN���X�������Ǘ��E�⏕����N���X�B
*/
#		ifdef HMLIB_PARAMETER_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30102<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [parameter.hpp] hmLib/lab��v3_01_02�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [parameter.hpp] hmLib/lab��v3_01_02�Œǉ�����܂����B")
#				endif
#			endif
#		endif
#endif
#
//hmLib_v3_01_03
#if HMLIB_VERSION<30103
/*
	algorithm.hpp v1_06
		class random_sampler�̒���
*/
#		ifdef HMLIB_ALGORITHM_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30101<=HMLIB_VERSION && 30103<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] random_sampler�̒v���I�ȃo�O���Av1_06(v3_01_03)�ŏC������Ă��܂��B")
#				elif HMLIB_OUT>1 && 30101<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #warning : [algorithm.hpp] random_sampler�ɒv���I�ȃo�O������܂��Bv1_06�ȏ�(v3_01_03�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			else
#				if HMLIB_OUT>1 && 30101<=HMLIB_VERSION
#					pragma message("hmLib_update : #warning : [algorithm.hpp] random_sampler�ɒv���I�ȃo�O������܂��Bv1_06�ȏ�(v3_01_03�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			endif
#		endif
/*
	lab/parameter.hpp v1_00
		���^�֐�����̃o�O����菜���B�g�p�\���
*/
#		ifdef HMLIB_PARAMETER_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30102<=HMLIB_VERSION && 30103<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [parameter.hpp] ���^�֐����ӂ̒v���I�ȃo�O���Av1_00(v3_01_03)�ŏC������Ă��܂��B")
#				elif HMLIB_OUT>1 && 30102<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #warning : [parameter.hpp] ���^�֐����ӂɒv���I�ȃo�O������܂��Bv1_00�ȏ�(v3_01_03�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			else
#				if HMLIB_OUT>1 && 30102<=HMLIB_VERSION
#					pragma message("hmLib_update : #warning : [parameter.hpp] ���^�֐����ӂɒv���I�ȃo�O������܂��Bv1_00�ȏ�(v3_01_03�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			endif
#		endif
#endif
#
#//hmLib_v3_01_04
#if HMLIB_VERSION<30104
/*
	algorithm.hpp v1_07
		class roulette_sampler�̏�������Begin��s���ɏ��������Ă����̂��C��
*/
#		ifdef HMLIB_ALGORITHM_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30101<=HMLIB_VERSION && 30104<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [algorithm.hpp] random_sampler�̒v���I�ȃo�O���Av1_07(v3_01_04)�ŏC������Ă��܂��B")
#				elif HMLIB_OUT>1 && 30101<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #warning : [algorithm.hpp] random_sampler�ɒv���I�ȃo�O������܂��Bv1_07�ȏ�(v3_01_04�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			else
#				if HMLIB_OUT>1 && 30101<=HMLIB_VERSION
#					pragma message("hmLib_update : #warning : [algorithm.hpp] random_sampler�ɒv���I�ȃo�O������܂��Bv1_07�ȏ�(v3_01_04�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			endif
#		endif
/*
	lab/config_vc.hpp v1_00
		VisualStudio���L�̃G���[�\��������������w�b�_�[
*/
#		ifdef HMLIB_CONFIG_VC_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30104<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [config_vc.hpp] hmLib/lab��v3_01_04�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [config_vc.hpp] hmLib/lab��v3_01_04�Œǉ�����܂����B")
#				endif
#			endif
#		endif
#endif
#
//hmLib_v3_02_00
#if HMLIB_VERSION<30199
#pragma message("hmLib_update : ===hmLib_v3_02===")
/*
	parameter.hpp v1_01
		�N���X���A������ύX
		hmLib/lab����hmLib�ֈړ�
*/
#		ifdef HMLIB_PARAMETER_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30102<=HMLIB_VERSION && 30199<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [parameter.hpp] �N���X���ƕK�v�Ȋ֐��̎�ނ��Av1_01(v3_02_00)�ŕύX����Ă��܂��B")
#				elif HMLIB_OUT>2 && 30102<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [parameter.hpp] �N���X���ƕK�v�Ȋ֐��̎�ނ��Av1_01(v3_02_00)�ŕύX����Ă��܂��B")
#				endif
#			else
#				if HMLIB_OUT>2 && 30102<=HMLIB_VERSION
#					pragma message("hmLib_update : #inform  : [parameter.hpp] �N���X���ƕK�v�Ȋ֐��̎�ނ��Av1_01(v3_02_00)�ŕύX����Ă��܂��B")
#				endif
#			endif
#		endif
/*
	agent.hpp �p�~
*/
#		ifdef HMLIB_AGENT_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30101<=HMLIB_VERSION 30199<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [agent.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂����B")
#				elif HMLIB_OUT>2 && 30101<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [agent.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2 && 30101<=HMLIB_VERSION
#					pragma message("hmLib_update : #inform  : [agent.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂��B")
#				endif
#			endif
#		endif
/*
	lociset.hpp �p�~
*/
#		ifdef HMLIB_LOCISET_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30000<=HMLIB_VERSION && 30199<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [lociset.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂����B")
#				elif HMLIB_OUT>2 && 30000<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [lociset.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2 && 30000<=HMLIB_VERSION
#					pragma message("hmLib_update : #inform  : [lociset.hpp] hmLib����v3_02_00/v3_01�Ŕp�~����܂��B")
#				endif
#			endif
#		endif
#endif
//hmLib_v3_02_01
#if HMLIB_VERSION<30201
/*
	filterbuf.hpp v1_01
		lab��v1_01��ǉ��B�֐�������ύX�B
*/
#		ifdef HMLIB_FILTERBUF_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30201<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform   : [filterbuf.hpp] lab��v1_01��v3_02_01�Œǉ�����܂����B�֐��������ύX����Ă��܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [filterbuf.hpp] lab��v1_01��v3_02_01�Œǉ�����܂����B�֐��������ύX����Ă��܂��B")
#				endif
#			endif
#		endif
/*
	exception.hpp v1_01
		lab��v1_01��ǉ��B�N���X������ύX�B
*/
#		ifdef HMLIB_EXCEPTION_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30201<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform   : [exception.hpp] lab��v1_01��v3_02_01�Œǉ�����܂����B�N���X�������ύX����Ă��܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [exception.hpp] lab��v1_01��v3_02_01�Œǉ�����܂����B�N���X�������ύX����Ă��܂��B")
#				endif
#			endif
#		endif
/*
	streambuf_interface.hpp v1_00
		lab��v1_00��ǉ��Bstreambuf_pattern.hpp�̌�p�B
*/
#		ifdef HMLIB_STREAMBUFINTERFACE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30201<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform   : [streambuf_interface.hpp] lab��v1_00��v3_02_01�Œǉ�����܂����Bstreambuf_pattern.hpp�̌�p�ł��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [streambuf_interface.hpp] lab��v1_00��v3_02_01�Œǉ�����܂����Bstreambuf_pattern.hpp�̌�p�ł��B")
#				endif
#			endif
#		endif
//hmLib_v3_02_02
/*
	byte_base.hpp v1_01
		standard_bytetype.hpp���p�~����Ă����̂ŁAhmLib_config���Q�Ƃ���`�ɏC���B
*/
#		ifdef HMLIB_BYTEBASETYPE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30201<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [bytebase_type.hpp] include�t�@�C���ɕs�����������̂�v1_01(v3_02_01)�ŏC������Ă��܂��B")
#				elif HMLIB_OUT>1
#					pragma message("hmLib_update : #warning : [bytebase_type.hpp] include�t�@�C���ɕs��������܂��Bv1_01�ȏ�(v3_02_01�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			else
#				if HMLIB_OUT>1
#					pragma message("hmLib_update : #warning : [bytebase_type.hpp] include�t�@�C���ɕs��������܂��Bv1_01�ȏ�(v3_02_01�ȏ�)�ɍX�V���Ă��������B")
#				endif
#			endif
#		endif
#endif
//hmLib_v3_03_00
#if HMLIB_VERSION<30300
#pragma message("hmLib_update : ===hmLib_v3_03===")
/*
	hmCLib�Ɠ���
*/
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : v3_03_00��hmCLib�Ɠ������܂����BC���ꂩ��ꕔ�̃w�b�_�t�@�C�������p�ł��܂��B")
#					pragma message("hmLib_update : #inform  : �g���q�̈Ӗ���C++�Ή��ł�hpp,C/C++�Ή��ł�h�ɁAv3_03_00�ŕύX����Ă��܂��B")
#					pragma message("hmLib_update : #inform  : v3_03_00����hmLib�̃p�X�̎w�肪�s�v�ɂȂ�܂����B���΃p�X��lib�t�@�C���͐ݒ肵�܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : v3_03_00��hmCLib�Ɠ������܂����BC���ꂩ��ꕔ�̃w�b�_�t�@�C�������p�ł��܂��B")
#					pragma message("hmLib_update : #inform  : �g���q�̈Ӗ���C++�Ή��ł�hpp,C/C++�Ή��ł�h�ɁAv3_03_00�ŕύX����Ă��܂��B")
#					pragma message("hmLib_update : #inform  : v3_03_00����hmLib�̃p�X�̎w�肪�s�v�ɂȂ�܂����B���΃p�X��lib�t�@�C���͐ݒ肵�܂��B")
#				endif
#			endif
/*
	byte_base.hpp v1_02
		�g���q��h�ɕύX�B
		C����Ƃ̋��ʉ����s���B
		hmLib_xxx�X�^�C���Ɍ^���𓝈�
*/
#		ifdef HMLIB_BYTEBASETYPE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [bytebase_type.h] �g���q��hpp����h�ɁAv1_02(v3_03_00)�ύX����܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [bytebase_type.h] �g���q��hpp����h�ɁAv1_02(v3_03_00)�ύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [bytebase_type.h] �g���q��hpp����h�ɁAv1_02(v3_03_00)�ύX����܂��B")
#				endif
#			endif
#		endif
/*
	random_v2_06
		�g���q��hpp�ɕύX�B
*/
#		ifdef HMLIB_RANDOM_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [random.hpp] �g���q��h����hpp�ɁAv2_06(v3_03_00)�ύX����܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [random.hpp] �g���q��h����hpp�ɁAv2_06(v3_03_00)�ύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [random.hpp] �g���q��h����hpp�ɁAv2_06(v3_03_00)�ύX����܂��B")
#				endif
#			endif
#		endif
/*
	align_v1_01
		�g���q��hpp�ɕύX�B
*/
#		ifdef HMLIB_ALIGN_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [allign.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [allign.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [allign.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				endif
#			endif
#		endif
/*
	csvstream_v1_01
		�g���q��hpp�ɕύX�B
*/
#		ifdef HMLIB_ALIGN_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [csvstream.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [csvstream.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [csvstream.hpp] �g���q��h����hpp�ɁAv1_01(v3_03_00)�ύX����܂��B")
#				endif
#			endif
#		endif
/*
	comgate_v1_04
		�g���q��hpp�ɕύX�B
*/
#		ifdef HMLIB_ALIGN_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [comgate.hpp] �g���q��h����hpp�ɁAv1_04(v3_03_00)�ύX����܂��B")
#				elif HMLIB_OUT>20
#					pragma message("hmLib_update : #inform  : [comgate.hpp] �g���q��h����hpp�ɁAv1_04(v3_03_00)�ύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [comgate.hpp] �g���q��h����hpp�ɁAv1_04(v3_03_00)�ύX����܂��B")
#				endif
#			endif
#		endif
/*
	cdeque_v1_00
		�Œ蒷�z���p����deque�B
*/
#		ifdef HMLIB_CDEQUE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [cdeque.hpp] v1_00��v3_03_00�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [cdeque.hpp] v1_00��v3_03_00�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	cqueue_v1_01
		�Œ蒷�z���p����queue�B�����I�ɂ�cdeque�̃��b�s���O�B
*/
#		ifdef HMLIB_CQUEUE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [cqueue.hpp] v1_01��v3_03_00�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [cqueue.hpp] v1_01��v3_03_00�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	cstack_v1_00
		�Œ蒷�z���p����stack�B�����I�ɂ�cdeque�̃��b�s���O�B
*/
#		ifdef HMLIB_CSTACK_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [cstack.hpp] v1_00��v3_03_00�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [cstack.hpp] v1_00��v3_03_00�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	cstring_v1_01
		�Œ蒷�z���p����string�B
*/
#		ifdef HMLIB_CSTRING_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [cstring.hpp] v1_01��v3_03_00�Œǉ�����܂����B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform : [cstring.hpp] v1_01��v3_03_00�Œǉ�����܂����B")
#				endif
#			endif
#		endif
/*
	exception.hpp v1_01
		�N���X������normal�������o�[�W�����ɕύX�Blab����i�グ�B
*/
#		ifdef HMLIB_EXCEPTION_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [exception.hpp] �N���X������v1_01(v3_03_00)�ŕύX����Ă��܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [exception.hpp] �N���X������v1_01(v3_03_00)�ŕύX����Ă��܂��B")
#				endif
#			else
#				if HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [exception.hpp] �N���X������v1_01(v3_03_00)�ŕύX����Ă��܂��B")
#				endif
#			endif
#		endif
/*
	gate_v1_01
		exception_v1_01�ɍ��킹�ē����ł̎g�p�֐�����ύX�B
*/
#		ifdef HMLIB_GATE_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>3 && 30300<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #memo    : [gate.hpp] exception_v1_01��v1_01(v3_01_02)�őΉ����܂����B")
#				endif
#			else
#				if HMLIB_OUT>3
#					pragma message("hmLib_update : #memo    : [gate.hpp] exception_v1_01��v1_01(v3_01_02)�őΉ����܂����B")
#				endif
#			endif
#		endif
#endif
//hmLib_v3_03_01
#if HMLIB_VERSION<30301
/*
	config_vc_v1_01/121204 hmIto
		v3_02_01�ȍ~�A����Ĕp�~����Ă����̂𕜊�
		�g���q��hpp����h�ɕύX
		�C���N���[�h�K�[�h�}�N���̕s�v�ȃA���_�[�o�[������
*/
#		ifdef HMLIB_CONFIGVC_INC
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>0 && 30301<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #error   : [config_vc.h] �g���q��hpp����h�ɁAv1_01(v3_03_01)�ŕύX����܂��B")
#				elif HMLIB_OUT>2
#					pragma message("hmLib_update : #inform  : [config_vc.h] �g���q��hpp����h�ɁAv1_01(v3_03_01)�ŕύX����܂��B")
#				endif
#			else
#				if HMLIB_OUT>2 && HMLIB_VERSION<30301
#					pragma message("hmLib_update : #inform  : [config_vc.h] �g���q��hpp����h�ɁAv1_01(v3_03_01)�ŕύX����܂��B")
#				endif
#			endif
#			ifdef HMLIB_UPGRADE
#				if HMLIB_OUT>2 && 30301<=HMLIB_UPGRADE
#					pragma message("hmLib_update : #inform  : [config_vc.h] �C���N���[�h�K�[�h�̕s�����Av1_01(v3_03_01)�ŏC������܂��B")
#				elif HMLIB_OUT>1
#					pragma message("hmLib_update : #warning : [config_vc.h] �C���N���[�h�K�[�h�̕s�����Av1_01(v3_03_01)�ŏC������܂��B")
#				endif
#			else
#				if HMLIB_OUT>1
#					pragma message("hmLib_update : #warning : [config_vc.h] �C���N���[�h�K�[�h�̕s�����Av1_01(v3_03_01)�ŏC������܂��B")
#				endif
#			endif
#		endif
#endif
//hmLib_v3_01_02
#if HMLIB_VERSION<30102
/*
lab/filterbuf_v1_02/130101 hmIto
	iostream�ɑΉ�
*/
/*
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
*/
/*
cdeque_v1_02/130105 hmIto
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
/*
cqueue_v1_02/130105 hmIto
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
/*
cstack_v1_02/130105 hmIto
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
#endif
//hmLib_v3_01_03
#if HMLIB_VERSION<30103
/*
algorithm:v1_08/130109
	roulette_sampler�̍�����
		�����Ŕz��̌`�ŕێ����Ă������ƂŁA�J��Ԃ����̓����������
		std::lower_bound�𗘗p���鎖�ō�����
*/
#endif
//hmLib_vX
#		if HMLIB_OUT>0 && HMLIB_UPDATE<HMLIB_VERSION
#			pragma message("hmLib_update : #error   : ��Ή��o�[�W�����ł��BhmLib_update�̃o�[�W�������X�V���Ă��������B")
#		endif
#	endif
#
#endif
#
#endif
