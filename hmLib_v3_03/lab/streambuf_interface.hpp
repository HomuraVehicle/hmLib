#ifndef HMLIB_STREAMBUFINTERFACE_INC
#define HMLIB_STREAMBUFINTERFACE_INC 101
/*===streambuf_interface===
streambuf_interface:v1_01/130104 hmIto
	nonbuf_streambuf_interface��buf_streambuf_interface��p�~
	streambuf_interface��ǉ�
	�֐����𓝈�I�ɐ���
		obuf/ibuf����p�C���^�[�t�F�[�X��obuf_/ibuf_�ɓ���
*/
#include <iostream>
#include <streambuf>
#pragma warning(disable : 4996)
/*===std::streambuf functions===
public:
	pos_type pubseekoff(off_type _Off, ios_base::seekdir _Way, ios_base::openmode _Mode = ios_base::in | ios_base::out);
	pos_type pubseekoff(off_type _Off, ios_base::seek_dir _Way, ios_base::open_mode _Mode);
		point�ʒu�𑊑Έʒu�Ő؂�ւ���
		������seekoff
	pos_type pubseekpos(pos_type _Pos, ios_base::openmode _Mode = ios_base::in | ios_base::out);
	pos_type pubseekpos(pos_type _Pos, ios_base::open_mode _Mode);
		point�ʒu���Έʒu�Ő؂�ւ���
		������seekpos
	_Myt* pubsetbuf(_Elem *_Buffer, streamsize _Count);
		�s��
		setbuf���Ăяo���Ă���
	locale pubimbue(const locale &_Newlocale);
		�s��
		imbue���Ăяo���Ă���
	locale getloc() const;
		�s��
		locale���擾����֐�?
	streamsize in_avail();
		ibuf���ɕ���������΂��̐��A�Ȃ����showmanyc()�̒l��Ԃ�
	int pubsync();
		obuf�̒��g���O���֔��f
		sync()���Ăяo��
	int_type sbumpc();
		1�����ǂݏo���Apoint��i�߂�
	int_type sgetc();
		1�����ǂݏo�����Apoint��i�߂Ȃ�
	streamsize sgetn(_Elem *_Ptr, streamsize _Count);
		n�����ǂݏo���Apoint��i�߂�
		xsgetn���Ăяo���Ă��邾���Ȃ̂ŁAoverflow���Ă��������Ȃ��͗l
	int_type snextc();
		���݂�point�̎���1������ǂݏo���Apoint��i�߂Ȃ�
	int_type sputbackc(_Elem _Ch);
		1������ǂݏo���O�ɖ߂�
	void stossc();
		�ǂݏo���p��point��i�߂�
	int_type sungetc();
		�ǂݏo���p��point��߂�?
	int_type sputc(_Elem _Ch);
		1������������
	streamsize sputn(const _Elem *_Ptr, streamsize _Count);
		n������������
		xsputn���Ăяo���Ă��邾���Ȃ̂ŁAoverflow���Ă��������Ȃ��͗l
	virtual void _Lock();
	virtual void _Unlock();
		thread�֘A
protected:
	int_type overflow(int_type = _Traits::eof());
		obuf�����ӂꂽ�Ƃ��ɌĂ΂��B
		obuf���ݒ肳��Ă��Ȃ��ꍇ�A��ɌĂ΂��B
	int_type pbackfail(int_type = _Traits::eof());
		ibuf�̐擪�Ɉꕶ���ǉ�����B
		���s�����ꍇ��eof��Ԃ��B
	streamsize showmanyc();
		ibuf�ւ̓��͕�������Ԃ�?
	int_type underflow();
		ibuf����ǂݏo�����Apoint�͓������Ȃ��B
	int_type uflow();
		ibuf����ǂݏo���Apoint�𓮂����B
	streamsize xsgetn(_Elem * _Ptr, streamsize _Count);
		ibuf����Count���������󂯎��Apoint�𓮂����B
	streamsize xsputn(const _Elem *_Ptr, streamsize _Count);
		obuf��Count���������������݁Apoint�𓮂����B
	pos_type seekoff(off_type, ios_base::seekdir, ios_base::openmode = ios_base::in | ios_base::out);
		obuf/ibuf��point��off�ŕύX����B
	pos_type seekpos(pos_type, ios_base::openmode = ios_base::in | ios_base::out);
		obuf/ibuf��point��pos�ŕύX����B
	_Myt *setbuf(_Elem *, streamsize);
		�O��agent����񋟂����o�b�t�@�𗘗p���� ������
	int sync();
		�O��agent�Ɠ���?
		flush�ɑ����B
	void imbue(const locale&);
		locale��ݒ�?
*/
namespace hmLib{
	template<class _Elem,class _Traits=std::char_traits<_Elem> >
	class basic_streambuf_interface:public virtual std::basic_streambuf<_Elem, _Traits>{
/*===for virtual functions===
	protected://streambuf_interface ibuf
		_Elem ibuf_overflow()override=0;
		streamsize ibuf_gets(_Elem* str,streamsize size)override=0;
		bool ibuf_unget(_Elem c)override=0;
		_Elem ibuf_peek()override=0;
	protected://streambuf_interface obuf
		bool obuf_overflow(_Elem c)override=0;
		streamsize obuf_puts(const _Elem* str,streamsize size)override=0;
		bool obuf_flush()override=0;
*/
	private://my typedef
		typedef basic_streambuf_interface<_Elem,_Traits> my_type;
		typedef std::basic_streambuf<_Elem,_Traits> my_streambuf;
	protected://common typedef
		typedef std::streamsize streamsize;
		typedef typename my_streambuf::pos_type pos_type;
		typedef typename my_streambuf::off_type off_type;
		typedef typename my_streambuf::int_type int_type;
	protected://common virtual functions
		virtual pos_type iobuf_seekpos(pos_type abspos,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)=0;
		virtual pos_type iobuf_seekoff(off_type relpos,std::ios_base::seekdir dir,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)=0;
	protected://ibuf virtual functions
		virtual _Elem ibuf_overflow()=0;
		virtual streamsize ibuf_gets(_Elem* str,streamsize size)=0;
		virtual bool ibuf_unget(_Elem c)=0;
		virtual _Elem ibuf_peek()=0;
	protected://obuf virtual functions
		virtual bool obuf_overflow(_Elem c)=0;
		virtual streamsize obuf_puts(const _Elem* str,streamsize size)=0;
		virtual bool obuf_flush()=0;
	protected://ibuf functions
		void ibuf_set(_Elem* pstrt,_Elem* pend){setg(pstrt,pstrt,pend);}
		_Elem* ibuf_begin(){return this->eback();}
		_Elem* ibuf_end(){return this->egptr();}
		_Elem* ibuf_getpos(){return this->gptr();}
		void ibuf_setpos(_Elem* ptr){this->gbump((int)(ptr-ibuf_pos()));}
		int ibuf_used(){return static_cast<int>(ibuf_pos()-ibuf_begin());}
		int ibuf_size(){return static_cast<int>(ibuf_end()-ibuf_begin());}
	protected://obuf functions
		void obuf_set(_Elem* pstrt,_Elem* pend){setp(pstrt,pend);}
		_Elem* obuf_begin(){return this->pbase();}
		_Elem* obuf_end(){return this->epptr();}
		_Elem* obuf_getpos(){return this->pptr();}
		void obuf_setpos(_Elem* ptr){this->pbump((int)(ptr-obuf_pos()));}
		int obuf_used(){return static_cast<int>(obuf_pos()-obuf_begin());}
		int obuf_size(){return static_cast<int>(obuf_end()-obuf_begin());}
	private://streambuf override functions
		streamsize xsputn(const _Elem* c_p,std::streamsize size)override{return puts(c_p,size);}
		streamsize xsgetn(_Elem* c_p,std::streamsize size)override{return gets(c_p,size);}
		pos_type seekpos(pos_type abspos_,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)override{return iobuf_seekpos(abspos_,which);}
		pos_type seekoff(off_type relpos_,std::ios_base::seekdir dir_,std::ios_base::openmode which_ = std::ios_base::in | std::ios_base::out)override{return iobuf_seekoff(relpos_,dir_,which_);}
		int_type overflow(int_type c_= _Traits::eof())override{return static_cast<int_type>(put_overflow(c_));}
		int_type uflow()override{return _Traits::to_int_type(get_overflow());}
		int_type underflow()override{return _Traits::to_int_type(peek());}
		int sync()override{return static_cast<int>(flush());}
		int_type pbackfail(int_type nCh)override{return _Traits::to_int_type(unget((_Elem)nCh));}
	};
	typedef basic_streambuf_interface<char,std::char_traits<char>> streambuf_interface;
/*	template<class _Elem,class _Traits=std::char_traits<_Elem> >
	class basic_nonbuf_streambuf_interface:public virtual std::basic_streambuf<_Elem,_Traits>{
	private:
		typedef basic_nonbuf_streambuf_interface<_Elem,_Traits> my_type;
		typedef std::basic_streambuf<_Elem,_Traits> my_streambuf;
	protected:
		typedef std::streamsize streamsize;
		typedef typename my_streambuf::pos_type pos_type;
		typedef typename my_streambuf::off_type off_type;
		typedef typename my_streambuf::int_type int_type;
	private:
		streamsize xsputn(const _Elem* c_p,std::streamsize size)override{
			puts(c_p,size);
			return size;
		}
		streamsize xsgetn(_Elem* c_p,std::streamsize size)override{
			return gets(c_p,size);
		}
		pos_type seekpos(pos_type abspos_,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)override{
			return seek(abspos_,which);
		}
		pos_type seekoff(off_type relpos_,std::ios_base::seekdir dir_,std::ios_base::openmode which_ = std::ios_base::in | std::ios_base::out)override{
			return seek(relpos_,dir_,which_);
		}
		int_type overflow(int_type c_= _Traits::eof())override{
			putc(c_);
			return 0;
		}
		int_type uflow()override{return getc();}
		int_type underflow()override{return peek();}
		int sync()override{
			flush();
			return 0;
		}
		int_type pbackfail(int_type nCh)override{
			unget((_Elem)nCh);
			return 0;
		}
	public://nonbuf_streambuf_interface
		virtual void putc(_Elem c)=0;
		virtual void puts(const _Elem* str,streamsize size){
			for(std::streamsize i=0;i<size;i++)putc(str[i]);
		}
		virtual void flush()=0;
		virtual _Elem getc()=0;
		virtual streamsize gets(_Elem* str,streamsize size){
			for(std::streamsize i=0;i<size;i++)str[i]=getc();
			return size;
		}
		virtual streamsize gets(_Elem* str,streamsize maxsize,_Elem end){
			for(std::streamsize i=0;i<maxsize;i++){
				str[i]=getc();
				if(str[i]==end)return i+1;
			}
			return maxsize;
		}
		virtual _Elem peek(){
			_Elem ans=getc();
			unget(ans);
			return ans;
		}
		virtual void unget(_Elem c)=0;
		virtual pos_type seek(pos_type abspos,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)=0;
		virtual pos_type seek(off_type relpos,std::ios_base::seekdir dir,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)=0;
	};
	template<class _Elem,class _Traits=std::char_traits<_Elem> >
	class basic_buf_streambuf_interface :public virtual std::basic_streambuf<_Elem,_Traits>{
	private:
		typedef basic_buf_streambuf_interface<_Elem,_Traits> my_type;
		typedef std::basic_streambuf<_Elem,_Traits> my_streambuf;
	protected:
		typedef std::streamsize streamsize;
		typedef typename my_streambuf::pos_type pos_type;
		typedef typename my_streambuf::off_type off_type;
		typedef typename my_streambuf::int_type int_type;
	private:
		int sync()override{
			flush();
			return 0;
		}
		pos_type seekpos(pos_type abspos_,std::ios_base::openmode which=std::ios_base::in|std::ios_base::out)override{
			return seek(abspos_);
		}
		pos_type seekoff(off_type relpos_,std::ios_base::seekdir dir_,std::ios_base::openmode which_ = std::ios_base::in | std::ios_base::out)override{
			return seek(relpos_,dir_);
		}
		int_type overflow(int_type c_= _Traits::eof())override{
			woverflow(static_cast<_Elem>(c_));
			return 0;
		}
		int_type underflow()override{
			return roverflow();
		}
	protected:
		void set_ibuf(_Elem* pstrt,_Elem* pend){
			setg(pstrt,pstrt,pend);
		}
		_Elem* ibuf_begin(){
			return this->eback();
		}
		_Elem* ibuf_end(){
			return this->egptr();
		}
		_Elem* ibuf_pos(){
			return this->gptr();
		}
		void set_ipos(_Elem* ptr){
			this->gbump((int)(ptr-ibuf_pos()));
		}
		int_type size_iuse(){return static_cast<int_type>(ibuf_pos()-ibuf_begin());}
		int_type size_ibuf(){return static_cast<int_type>(ibuf_end()-ibuf_begin());}
		void set_obuf(_Elem* pstrt,_Elem* pend){
			setg(pstrt,pstrt,pend);
			setp(pstrt,pend);
		}
		_Elem* obuf_begin(){
			return this->pbase();
		}
		_Elem* obuf_end(){
			return this->epptr();
		}
		_Elem* obuf_pos(){
			return this->pptr();
		}
		void set_opos(_Elem* ptr){
			this->pbump((int)(ptr-obuf_pos()));
		}
		int_type size_ouse(){return static_cast<int_type>(obuf_pos()-obuf_begin());}
		int_type size_obuf(){return static_cast<int_type>(obuf_end()-obuf_begin());}
	public://buf_streambuf_interface
		virtual void woverflow(_Elem c_)=0;
		virtual void flush()=0;
		virtual _Elem roverflow()=0;
		virtual std::streambuf::pos_type seek(off_type relpos,std::ios_base::seekdir dir)=0;
		virtual std::streambuf::pos_type seek(pos_type abspos)=0;
	};
	typedef basic_nonbuf_streambuf_interface<char, std::char_traits<char> > nonbuf_streambuf_interface;
	typedef basic_nonbuf_streambuf_interface<char, std::char_traits<char> > buf_streambuf_interface;
*/
}
#endif
