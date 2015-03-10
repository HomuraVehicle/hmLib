#ifndef HMLIB_BUFGATE_INC
#define HMLIB_BUFGATE_INC 102
#
/*===bufgate===
�o�b�t�@�Ƀf�[�^���ꎞ�I�ɂ��߁Aoperator()�ő���M����gate�N���X�ł��B

bufgate v1_02/130329 hmIto
	�ꕔ�ϐ����̋L�q�~�X�ŃR���p�C���G���[���o�Ă��������C��
bufgate v1_01/130328 hmIto
	work�֐���operator()(unsigned int GetMaxNum,unsigned int PutMaxNum)�ɕύX���܂����B
*/
#ifndef HMLIB_GATE_INC
#	include <hmLib_v3_04/gate.hpp>
#endif
#ifndef HMLIB_CIRCULAR_INC
#	include <hmLib_v3_04/circular.hpp>
#endif
#include <deque>
#include <vector>
namespace hmLib{
	//�o�b�t�@Gate
	class bufgate:public gate{
	private:
		gate* pGate;
		std::deque<char> oBuf;
		std::deque<char> iBuf;
	public:
		bufgate():pGate(0){return;}
		~bufgate(){close();}
		bool open(gate& rGate_){
			//���łɊJ����Ă�����A�G���[��Ԃ�
			if(is_open())return true;

			pGate=&rGate_;

			return false;
		}
		bool close(){
			//���łɕ����Ă�����A�G���[��Ԃ�
			if(!is_open())return true;

			pGate=0;

			return false;
		}
		bool is_open()const{return pGate!=0;}
		void operator()(void){
			if(!pGate->empty()){
				while(!pGate->empty() && pGate->can_get()){
					itfGate::size_type size=1;
					char tmp;
					if(pGate->get(&tmp,size))break;
					iBuf.push_back(tmp);
				}
			}else if(!oBuf.empty()){
				while(!oBuf.empty() && pGate->can_put()){
					itfGate::size_type size=1;
					pGate->put(oBuf.front(),size);
					oBuf.pop_front();
				}
			}
		}
		void operator()(unsigned int GetMaxNum_,unsigned int PutMaxNum_){
			if(!pGate->empty()){
				while(!pGate->empty() && pGate->can_get() && GetMaxNum_){
					itfGate::size_type size=1;
					char tmp;
					if(pGate->get(&tmp,size))break;
					iBuf.push_back(tmp);
					--GetMaxNum_;
				}
			}else if(!oBuf.empty()){
				while(!oBuf.empty() && pGate->can_put() && PutMaxNum_){
					itfGate::size_type size=1;
					pGate->put(oBuf.front(),size);
					oBuf.pop_front();
					--PutMaxNum_;
				}
			}
		}
		unsigned int psize()const{return oBuf.size();}
		unsigned int gsize()const{return iBuf.size();}
		void pclear(){oBuf.clear();}
		void gclear(){iBuf.clear();}
	public://itfGate
		//��M�҃f�[�^
		virtual bool empty(){return iBuf.empty();}
		//��M�\
		virtual bool can_get(){return !empty();}
		//����byte��M
		virtual bool get(char* str_,size_type& size_){
			size_type max=size_;
			for(size_=0;size_<max;++size_){
				if(!can_get())return true;
				iBuf.front(*str_);
				iBuf.pop_front();
				++str_;
			}
			return false;
		}
		//���M�҃f�[�^
		virtual bool full(){return false;}
		//���M�\
		virtual bool can_put(){return !full();}
		//����byte���M
		virtual bool put(const char* str_,size_type& size_){
			size_type max=size_;
			for(size_=0;size_<max;++size_){
				if(!can_put())return true;
				oBuf.push_back(*str_);
				++str_;
			}
			return false;
		}
	};
	//�L���o�b�t�@Gate
	class limbufgate:public itfGate{
	private:
		itfGate* pGate;
		hmLib::bicircular<char> oBuf;
		hmLib::bicircular<char> iBuf;
	public:
		limbufgate():pGate(0){return;}
		~limbufgate(){close();}
		bool open(itfGate& rGate_,unsigned int oBufSize,unsigned int iBufSize){
			//���łɊJ����Ă�����A�G���[��Ԃ�
			if(is_open())return true;

			pGate=&rGate_;

			//Buf�m��
			oBuf.create(oBufSize);
			iBuf.create(iBufSize);

			return false;
		}
		bool close(){
			//���łɕ����Ă�����A�G���[��Ԃ�
			if(!is_open())return true;

			pGate=0;

			oBuf.release();
			iBuf.release();

			return false;
		}
		bool is_open()const{return pGate!=0;}
		void operator()(void){
			if(!pGate->empty()){
				while(!pGate->empty()){
					iBuf.push_back(pGate->getc());
				}
			}else if(!oBuf.empty()){
				while(!oBuf.empty()){
					pGate->putc(oBuf.front());
					oBuf.pop_front();
				}
			}
		}
		void operator()(unsigned int GetMaxNum_,unsigned int PutMaxNum_){
			if(!pGate->empty()){
				while(!pGate->empty() && GetMaxNum_){
					iBuf.push_back(pGate->getc());
					--GetMaxNum_;
				}
			}else if(!oBuf.empty()){
				while(!oBuf.empty() && PutMaxNum_){
					pGate->putc(oBuf.front());
					oBuf.pop_front();
					--PutMaxNum_;
				}
			}
		}
		unsigned int psize()const{return oBuf.size();}
		unsigned int gsize()const{return iBuf.size();}
		void pclear(){oBuf.clear();}
		void gclear(){iBuf.clear();}
	public://itfGate
		//��M�҃f�[�^
		virtual bool empty(){return iBuf.empty();}
		//��M�\
		virtual bool can_get(){return !empty();}
		//����byte��M
		virtual bool get(char* str_,size_type& size_){
			size_type max=size_;
			for(size_=0;size_<max;++size_){
				if(!can_get())return true;
				iBuf.front(*str_);
				iBuf.pop_front();
				++str_;
			}
			return false;
		}
		//���M�҃f�[�^
		virtual bool full(){return oBuf.full();}
		//���M�\
		virtual bool can_put(){return !full();}
		//����byte���M
		virtual bool put(const char* str_,size_type& size_){
			size_type max=size_;
			for(size_=0;size_<max;++size_){
				if(!can_put())return true;
				oBuf.push_back(*str_);
				++str_;
			}
			return false;
		}
	};
}
#
#endif