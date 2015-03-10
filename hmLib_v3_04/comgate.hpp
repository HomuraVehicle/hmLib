#ifndef HMLIB_COMGATE_INC
#define HMLIB_COMGATE_INC 107
#
/*===comgate===
COM�|�[�g�����RS232c�ʐM���T�|�[�g

comgate v1_07/130406 hmIto
	liste/talk�֐��ł͐���Ɏ擾�ł��Ȃ��ꍇ���������̂ŁAgetc1/putc1�ɕύX
comgate v1_06/130324 hmIto
	size_type��std::streamsize�ɕύX�ɂȂ����̂ɑΉ�
		get�֐��̓����ϐ���size_type����unsigned int�ɕύX
		put�֐��̓�����static_cast�𓱓�
comgate v1_05/130310 hmIto
	full�֐��������Ȃ��ɏC��
*/
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_04/lib/Debug/comgate.lib")
#	else
#		pragma comment(lib,"hmLib_v3_04/lib/Release/comgate.lib")
#	endif
#endif
#ifndef HMLIB_GATE_INC
#	include <hmLib_v3_04/gate.hpp>
#endif
#include "comgate/winRS/winrs.h"

namespace hmLib{
	class comgate:public virtual gate{
	private:
		WinRS* port;
		int portnum;
		int bps;
	public://gate
		//��M�҃f�[�^�̗L��
		virtual bool empty(){return (port->loc()==0);}
		//��M�\���
		virtual bool can_get(){return !empty();}
		//����byte��M
		virtual size_type get(char* str_,const size_type& size_){
			for(size_type cnt=0;cnt<size_;++cnt){
				*(str_++)=port->getc1();
			}
			return size_;
		}
		//���M�҃f�[�^�̗L��
		virtual bool full(){return false;}
		//���M�\���
		virtual bool can_put(){return !full();}
		//����byte���M
		virtual size_type put(const char* str_,const size_type& size_){
			for(size_type cnt=0;cnt<size_;++cnt){
				port->putc1(*(str_++));
			}
			return size_;
		}
	public:
		comgate():port(0){return;}
		comgate(int _portnum,int _bps):port(0){open(_portnum,_bps);}
		~comgate(){close();}
		bool open(int _portnum,int _bps){
			close();
			portnum =_portnum;
			bps=_bps;
			port = new WinRS(portnum,bps,ifLine::crlf,"8N1");

			if(!(*port))close();

			return !(is_open());
		}
		bool is_open()const{return port!=0;}
		bool close(){
			if(port){
				delete port;
				port=0;
			}
			return false;
		}
	};
}
#endif
