#ifndef HMLIB_VCOM_VIRTUALCOMGATE_INC
#define HMLIB_VCOM_VIRTUALCOMGATE_INC 100
#
/*===virtual_comgate===
�X���b�h���g���ĉ��z�I��com�ʐM���Č�����N���X�Q
*/
#include<deque>
#include<mutex>
#include"virtual_com_abstruct.hpp"
#include"virtual_comgate_abstruct.hpp"
namespace hmLib{
	namespace vcom{
		//���zcomgate
		class virtual_comgate:public virtual_comgate_abstruct{
			typedef std::mutex mutex;
			typedef std::lock_guard<mutex> lock;
		public:
			virtual ~virtual_comgate(){
				if(is_open())close();
			}
		private:
			std::mutex Mx;
			std::deque<char> ibuf;
			std::deque<char> obuf;
		private:
			virtual_com_abstruct* ptr;
		public:
			bool is_open()const{return ptr!=nullptr;}
			void open(virtual_com_abstruct& VCom_){
				hmLib_assert(!is_open(),gate_opened_exception,"virtua_com have already been opened.");
				ptr=&VCom_;
				ptr->connect(this);
			}
			void close(){
				hmLib_assert(is_open(),gate_opened_exception,"virtua_com have not been opened.");
				ptr->disconnect(this);
				ptr=nullptr;
			}
		public: //gate
			//��M�\��Ԃ��̊m�F
			bool can_get()override{return is_open();}
			//��M�\�f�[�^�̗L��
			bool empty()override{return ibuf.size()==0;}
			//����byte��M�@��M�����A�h���X�ƁA��M�������������@���ۂ̎�M���������߂�l
			size_type get(char* str_,const size_type& size_)override{
				lock Lock(Mx);
				for(size_type i=0;i<size_;++i){
					if(ibuf.size()==0)return i;
					str_[i]=ibuf.front();
					ibuf.pop_front();
				}
				return size_;	
			}
			//���M�\��Ԃ��̊m�F
			bool can_put()override{return is_open();}
			//���M�\�f�[�^�̗L��
			bool full()override{return false;}
			//����byte���M�@���M�����A�h���X�ƁA���M�������������@���ۂ̑��M���������߂�l
			size_type put(const char* str_,const size_type& size_)override{
				lock Lock(Mx);
				for(size_type i=0;i<size_;++i){
					obuf.push_back(str_[i]);
				}
				return size_;
			}
		public: //virtaul_comgate_abstruct
			//com�Ƃ��đ��M����f�[�^���擾����
			size_type com_send(char* ptr_, size_type size_){
				lock Lock(Mx);
				for(size_type i=0;i<size_;++i){
					if(obuf.size()==0)return i;
					ptr_[i]=obuf.front();
					obuf.pop_front();
				}
				return size_;
			}
			//com�Ƃ��Ď�M������f�[�^��^����
			size_type com_recv(const char* ptr_, size_type size_){
				lock Lock(Mx);
				for(size_type i=0;i<size_;++i){
					ibuf.push_back(ptr_[i]);
				}
				return size_;
			}
		};
	}
}
#
#endif
