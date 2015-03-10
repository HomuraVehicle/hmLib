#ifndef HMLIB_GATE_INC
#define HMLIB_GATE_INC 201
#
/*===gate===
��M���M���ȈՂōs���N���X

=== gate ===
v2_01/131222 amby
	����ɁAgate�̉��z�֐��Ƃ��� is_open()��ǉ�
	gate���g���ۂ�is_open���m�F����͎̂g�p�҂̋`���ƂȂ�B

v2_00/131222 hmIto
	������^gate
		���������������get/put��p�~���A�P��������ɓ���
			�������Agets/puts�Ō����̖��Ŏg�������ꍇ�̎�i�͎c��
		�V���ɁAflowing/flush��ǉ�
			flowing:��M���p�����Ă��邩�ǂ����B�P���ȏꍇ�͏�ɐ^�B
			flush:���M�𔽉f����B�P���ȏꍇ�͉������Ȃ��B
			flush���邩�ǂ�����flowing�Ŕ��f�ł���B
			����ȋ�؂蓙��flowing/flush�Ŕ��ʂł���B
v1_05/130421 hmIto
	exceptions�ɑΉ�
v1_04/130329 hmIto
	�ꕔstreambuf_interface�̏������z�֐����p������Ă��Ȃ������v���I�Ȗ����C��
v1_03/130328 hmIto
	streambuf_interface���p������`�ɏC��
v1_02/130324 hmIto
	iostream��include
	basic_gatestreambuf�̏������Ƀ|�C���^�ł͂Ȃ��Q�Ƃ�n���Ă����v���I�Ȗ����C��
*/
#include<iostream>
#ifndef HMLIB_STREAMBUINTERFACE_INC
#	include <hmLib_v3_06/streambuf_interface.hpp>
#endif
#ifndef HMLIB_EXCEPTIONS_INC
#	include <hmLib_v3_06/exceptions.hpp>
#endif
namespace hmLib{
	struct gate_exception_identifier {};
	typedef exceptions::exception_pattern<gate_exception_identifier> gate_exception;
	typedef exceptions::io::not_opened<gate_exception> gate_not_opened_exception;
	typedef exceptions::io::opened<gate_exception> gate_opened_exception;

	template<typename _Elem, typename _Traits=std::char_traits<_Elem> >
	class basic_gate{
	public:
		typedef std::streamsize size_type;
	public://gate
		//gate���J���Ă��邩�ǂ����̊m�F
		virtual bool is_open() = 0;
		//��M�\��Ԃ��̊m�F
		virtual bool can_getc()=0;
		//�Pbyte��M
		virtual _Elem getc()=0;
		//����byte��M�@��M�����A�h���X�ƁA��M�������������@���ۂ̎�M���������߂�l
		virtual size_type gets(_Elem* str, const size_type& size) {
			for(size_type i=0; i<size; ++i) {
				if(!can_getc())break;
				str[i]=getc();
			}
			return size;
		}
		//��M���p�����Ă��邩���m�F����
		virtual bool flowing()=0;
		//���M�\��Ԃ��̊m�F
		virtual bool can_putc()=0;
		//�Pbyte���M
		virtual void putc(_Elem c)=0;
		//����byte���M�@���M�����A�h���X�ƁA���M�������������@���ۂ̑��M���������߂�l
		virtual size_type puts(const _Elem* str, const size_type& size) {
			for(size_type i=0; i<size; ++i) {
				if(!can_putc())break;
				putc(str[i]);
			}
			return size;
		}
		//���M��ł��؂�
		virtual void flush()=0;
	public:
		virtual ~basic_gate(){}
	};
	template<typename _Elem, typename _Traits=std::char_traits<_Elem> >
	class basic_gatestreambuf:public basic_streambuf_interface<_Elem,_Traits>{
	private:
		typedef basic_gate<_Elem,_Traits> my_gate;
	protected:
		my_gate* gate;
		_Elem buf;
		bool bufflag;
	public://�W���֐�
		basic_gatestreambuf():gate(/*C++0x_nullptr/*/NULL/**/),bufflag(false){return;}
		basic_gatestreambuf(my_gate* gate_):gate(gate_),bufflag(false){return;}
		~basic_gatestreambuf(){close();}
		bool is_open()const{return gate!=/*C++0x_nullptr/*/NULL/**/;}
		bool open(my_gate* gate_){
			close();
			gate=gate_;
			return false;
		}
		bool close(){
			gate=/*C++0x_nullptr/*/NULL/**/;
			bufflag=false;
			return false;
		}
	protected://common virtual functions
		pos_type iobuf_seekpos(pos_type abspos,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)override{
			hmLib_throw(exceptions::exception, "basic_gatestreambuf can't do seek");
			return 0;
		}
		pos_type iobuf_seekoff(off_type relpos,std::ios_base::seekdir dir,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)override{
			hmLib_throw(exceptions::exception, "basic_gatestreambuf can't do seek");
			return 0;
		}
	protected://streambuf_interface ibuf
		_Elem ibuf_overflow()override{
			if(bufflag){
				bufflag=false;
				return buf;
			}
			while(!gate->can_getc());
			return gate->getc();
		}
		streamsize ibuf_gets(_Elem* str,streamsize size)override{
			if(size==0)return 0;

			if(bufflag) {
				bufflag=false;
				str[0]=buf;
				return gate->gets(str+1, size-1)+1;
			}
			return gate->gets(str, size);
		}
		bool ibuf_unget(_Elem c)override{
			hmLib_assert(!bufflag, exceptions::exception, "unget cannot use successively.");
			buf=c;
			bufflag=true;
			return false;
		}
		_Elem ibuf_peek()override{
			_Elem ans=ibuf_overflow();
			ibuf_unget(ans);
			return ans;
		}
	protected://streambuf_interface obuf
		bool obuf_overflow(_Elem c)override{
			while(!gate->can_putc());
			gate->putc(c);
			return false;
		}
		streamsize obuf_puts(const _Elem* str,streamsize size)override{
			return gate->puts(str, size);
		}
		bool obuf_flush()override { gate->flush(); return false; }
	public://gate functions
		bool fail(){return (gate->can_get() || gate->can_put());}
		bool pfail(){return gate->can_put();}
		bool gfail(){return gate->can_get();}
		bool empty(){return gate->empty();}
		bool full(){return gate->full();}
		bool flowing() { return gate->flowing(); }
	};
	template<typename _Elem, typename _Traits=std::char_traits<_Elem> >
	class basic_igatestream:public std::basic_istream<_Elem,_Traits>{
	private:
		typedef basic_gate<_Elem,_Traits> my_gate;
		typedef basic_gatestreambuf<_Elem,_Traits> my_gatestreambuf;
	private:
		my_gatestreambuf* streambuf;
	public:
		basic_igatestream():std::basic_istream<_Elem,_Traits>(streambuf=new my_gatestreambuf()){return;}
		basic_igatestream(my_gate& gate_):std::basic_istream<_Elem,_Traits>(streambuf=new my_gatestreambuf(&gate_)){return;}
		~basic_igatestream(){
			close();
			delete streambuf;
		}
	public:
		void open(my_gate& gate_){streambuf->open(&gate_);}
		void close(){streambuf->close();}
		bool is_open(){return streambuf->is_open();}
		bool gfail(){return streambuf->gfail();}
		bool empty(){return streambuf->empty();}
		bool eof() { return flowing(); }
	};
	template<typename _Elem, typename _Traits=std::char_traits<_Elem> >
	class basic_ogatestream:public std::basic_ostream<_Elem,_Traits>{
	private:
		typedef basic_gate<_Elem,_Traits> my_gate;
		typedef basic_gatestreambuf<_Elem,_Traits> my_gatestreambuf;
	private:
		my_gatestreambuf* streambuf;
	public:
		basic_ogatestream():std::basic_ostream<_Elem,_Traits>(streambuf=new my_gatestreambuf()){return;}
		basic_ogatestream(my_gate& gate_):std::basic_ostream<_Elem,_Traits>(streambuf=new my_gatestreambuf(&gate_)){return;}
		~basic_ogatestream(){
			close();
			delete streambuf;
		}
		void open(my_gate& gate_){streambuf->open(&gate_);}
		void close(){streambuf->close();}
		bool is_open(){return streambuf->is_open();}
	public:
		bool pfail(){return streambuf->pfail();}
		bool full(){return streambuf->full();}
	};
	template<typename _Elem, typename _Traits=std::char_traits<_Elem> >
#pragma warning(push)
#pragma warning(disable:4250)
	class basic_gatestream:public std::basic_iostream<_Elem,_Traits>{
	private:
		typedef basic_gate<_Elem,_Traits> my_gate;
		typedef basic_gatestreambuf<_Elem,_Traits> my_gatestreambuf;
	private:
		my_gatestreambuf* streambuf;
	public:
		basic_gatestream():std::basic_iostream<_Elem,_Traits>(streambuf=new my_gatestreambuf()){return;}
		basic_gatestream(my_gate& gate_):std::basic_iostream<_Elem,_Traits>(streambuf=new my_gatestreambuf(&gate_)){return;}
		~basic_gatestream(){
			close();
			delete streambuf;
		}
		void open(my_gate& gate_){streambuf->open(&gate_);}
		void close(){streambuf->close();}
		bool is_open(){return streambuf->is_open();}
	public:
		bool pfail(){return streambuf->pfail();}
		bool full(){return streambuf->full();}
		bool gfail(){return streambuf->gfail();}
		bool empty(){return streambuf->empty();}
		bool eof() { return flowing(); }
	};
#pragma warning(pop)
	typedef basic_gate<char,std::char_traits<char> > gate;
	typedef basic_gatestreambuf<char,std::char_traits<char> > gatestreambuf;
	typedef basic_igatestream<char,std::char_traits<char> > igatestream;
	typedef basic_ogatestream<char,std::char_traits<char> > ogatestream;
	typedef basic_gatestream<char,std::char_traits<char> > gatestream;
}
#
#endif
