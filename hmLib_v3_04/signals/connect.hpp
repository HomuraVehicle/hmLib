#ifndef HMLIB_SIGNALS_CONNECT_INC
#define HMLIB_SIGNALS_CONNECT_INC 100
#
/*===signal::connect===
boost::signals2::signal��connection���Ǘ����Adestructor��disconnect����N���X

signals::unique_connections v1_00/130328 hmIto
	signals���O��ԃt�@�C���Ɉړ�
signal_unique_connections v1_00/130328 hmIto
	�쐬
*/
#include<boost/signals2/signal.hpp>
#ifndef HMLIB_EXCEPTION_INC
#	include<hmLib_v3_04/exception.hpp>
#endif
namespace hmLib{
	namespace signals{
		template<typename Sign,typename Slot>
		boost::signals2::connection connect(boost::signals2::signal<Sign>& Sig_,Slot& Slt_){
			return Sig_.connect(Slt_);
		}
	}
}
#
#endif
