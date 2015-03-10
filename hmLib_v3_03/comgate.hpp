#ifndef HMLIB_COM_GATE_INC
#define HMLIB_COM_GATE_INC 106
#
/*===comgate===
COM�|�[�g�����RS232c�ʐM���T�|�[�g

comgate:v1_06:130324/hmIto
	size_type��std::streamsize�ɕύX�ɂȂ����̂ɑΉ�
		get�֐��̓����ϐ���size_type����unsigned int�ɕύX
		put�֐��̓�����static_cast�𓱓�
comgate:v1_05:130310/hmIto
	full�֐��������Ȃ��ɏC��
*/
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_03/lib/Debug/comgate.lib")
#	else
#		pragma comment(lib,"hmLib_v3_03/lib/Release/comgate.lib")
#	endif
#endif
#ifndef HMLIB_GATE_INC
#	include "gate.hpp"
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
			unsigned int ans;
			if(port->listen(str_,ans)!=0)return 0;
			return ans;
		}
		//���M�҃f�[�^�̗L��
		virtual bool full(){return false;}
		//���M�\���
		virtual bool can_put(){return !full();}
		//����byte���M
		virtual size_type put(const char* str_,const size_type& size_){
			if(port->putN(const_cast<char*>(str_),static_cast<unsigned int>(size_))!=0)return 0;
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
