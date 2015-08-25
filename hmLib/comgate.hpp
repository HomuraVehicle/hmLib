#ifndef HMLIB_COMGATE_INC
#define HMLIB_COMGATE_INC 201
#
/*===comgate===
COM�|�[�g�����RS232c�ʐM���T�|�[�g

v2_00/131222 amby
	������^comgate	
	���������������get/put��p�~���A�P��������ɓ���
	�������Agets/puts�Ō����̖��Ŏg�������ꍇ�̎�i�͎c��
	�V���ɁAflowing/flush/is_open��ǉ�
	flowing: !empty()�ɑΉ�
	flush: �����Ȃ�
	
comgate v1_09/131222 amby
	Flow����̐ݒ肪�ł���悤�ɁAopen�֐���ύX
comgate v1_08/130622 hmIto
	can_get/can_put�֐���empty/full���Q�Ƃ��Ȃ��悤�ɕύX
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
#if !(defined(HMLIB_NOLIB) || defined(HMLIB_COMGATE_NOLIB))
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib/lib/Debug/comgate.lib")
#	else
#		pragma comment(lib,"hmLib/lib/Release/comgate.lib")
#	endif
#endif
#ifndef HMLIB_GATE_INC
#	include <hmLib/gate.hpp>
#endif
#include "hmLib/comgate/winRS/winrs.h"

namespace hmLib{
	class comgate:public virtual gate{
	private:
		WinRS* port;
		int portnum;
		int bps;
	public://gate
		// �Q�[�g���J���Ă��邩�̊m�F
		virtual bool is_open() override{ return port != 0; }
		
		//��M�\��΂��̊m�F
		virtual bool can_getc()override{
			std::string str = hmLib_exceptions_to_str(__LINE__);

			hmLib_assert(is_open(), gate_not_opened_exception, "comgate have not been opened yet.");
			return (port->loc() != 0 && is_open());
		}
		// ��M���p�����Ă��邩�̊m�F
		virtual bool flowing()override{
			hmLib_assert(is_open(), gate_not_opened_exception, "comgate have not been opened yet.");
			return (port->loc() != 0);
		}
		//1byte��M
		virtual char getc()override{
			hmLib_assert(is_open(), gate_not_opened_exception, "comgate have not been opened yet.");
			return port->getc1();
		}


		//���M�\��Ԃ��̊m�F
		virtual bool can_putc()override{
			hmLib_assert(is_open(),gate_not_opened_exception,"comgate have not been opened yet.");
			return is_open();
		}
		//���M�𖳗������B�B�R�}���h�Ȃ�
		virtual void flush()override{
			hmLib_assert(is_open(),gate_not_opened_exception,"comgate have not been opened yet.");
			return;
		}
		//1byte���M
		virtual void  putc(char c)override{
			hmLib_assert(is_open(),gate_not_opened_exception,"comgate have not been opened yet.");
			port->putc1(c);
			return;
		}

	public:
		comgate():port(0){return;}
		comgate(int _portnum,int _bps):port(0){open(_portnum,_bps);}
		comgate(int _portnum, int _bps, bool use_flowControl_) :port(0){ open(_portnum, _bps, use_flowControl_);}
		virtual ~comgate(){if(is_open())close();}
	private:
	public:
		bool open(int _portnum,int _bps, bool use_flowControl_ = false){
			hmLib_assert(!is_open(),gate_opened_exception,"comgate have already been opened.");
			portnum =_portnum;
			bps=_bps;
			port = new WinRS(portnum, bps, ifLine::crlf, "8N1", use_flowControl_);

			if(!(*port))close();

			return !(is_open());
		}

		bool close(){
			hmLib_assert(is_open(),gate_not_opened_exception,"comgate have not been opened yet.");

			delete port;
			port=0;

			return false;
		}
	};
}
#endif
