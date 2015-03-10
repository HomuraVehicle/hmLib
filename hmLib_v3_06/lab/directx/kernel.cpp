#ifndef HMLIB_DXLIB_KERNEL_CPP_INC
#define HMLIB_DXLIB_KERNEL_CPP_INC 100
#
#ifndef HMLIB_DXLIB_KERNEL_INC
#	include"kernel.hpp"
#endif
#ifndef HMLIB_DXLIB_EXCEPTIONS_INC
#	include"exceptions.hpp"
#endif
#include<DxLib.h>
namespace hmLib{
	namespace dxlib{
		kernel::kernel(bool CanRunMultiDxLib_, bool IsRunAlways_, bool IsOutputLog_, bool IsCalcLowPrecise_)
			:CanRunMultiDxLib(CanRunMultiDxLib_)
			, IsRunAlways(IsRunAlways_)
			, IsOutputLog(IsOutputLog_)
			, IsCalcLowPrecise(IsCalcLowPrecise_){

			if(exist())hmLib_throw(exceptions::dxlib_exception, "DxLib have already been initialized.");

			//��d�N����e�F����
			SetDoubleStartValidFlag(static_cast<int>(CanRunMultiDxLib));

			//Active�łȂ��Ă����삷��
			SetAlwaysRunFlag(static_cast<int>(IsRunAlways));

			//���O�o�͂𖳌��ɂ���
			SetOutApplicationLogValidFlag(static_cast<int>(IsOutputLog));

			//double��float���x���܂ŗ��Ƃ��ĉ��Z���Ȃ�
			SetUseFPUPreserveFlag(static_cast<int>(IsCalcLowPrecise));

			//DxLib�N��
			if(DxLib_Init() == -1)hmLib_throw(exceptions::dxlib_exception, "Failed to initialize DxLib.");
		}
		kernel::~kernel(){
			//DxLib�I��
			DxLib_End();
		}
		bool kernel::operator()(void){
			// Windows �V�X�e�����炭�������������
			return (ProcessMessage() != 0);
		}
		bool kernel::exist(){ return DxLib_IsInit(); }
	}
}
#
#endif
