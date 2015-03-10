#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#define HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC 102
#
/*===inquiries::inquiry_abstruct===
inquiry�@�\�̊��N���X
connection�ɂ��Ă������ŊǗ����Ă���

inquiries::inquiry_abstruct v1_02/130410 hmIto
	���[�u������Z�q��swap�֐��̈�����ptr�ł͂Ȃ�nullptr�Ƃ��Ă��������C��
inquiries::inquiry_abstruct v1_01/130329 hmIto
	���[�u�R���X�g���N�^/������Z�q���ӂ̒v���I�ȃo�O���C��
inquiries::inquiry_abstruct v1_00/130328 hmIto
	inquiry���番��
*/
#ifndef HMLIB_EXCEPTION_INC
#	include<hmLib_v3_06/exception.hpp>
#endif
namespace hmLib{
	namespace inquiries{
		//connection�V�X�e����񋟂���@�\
		class inquiry_abstruct{
		public:
			class connection{
			private:
				inquiry_abstruct* ptr;
			private:
				connection(const connection& My_);
				const connection& operator=(const connection& My_);
			public:
				connection():ptr(nullptr){}
				connection(inquiry_abstruct* ptr_):ptr(ptr_){}
				connection(connection&& My_):ptr(nullptr){
					std::swap(ptr,My_.ptr);
					ptr->ptr=this;
				}
				const connection& operator=(connection&& My_){
					hmLib_assert(ptr==nullptr,"connection already have a pointer");
					std::swap(ptr,My_.ptr);
					ptr->ptr=this;
					return *this;
				}
				~connection(){if(ptr)ptr->ptr=nullptr;}
				bool is_connect()const{return ptr!=nullptr;}
				void disconnect(){if(ptr)ptr->disconnect();}
				friend class inquiry_abstruct;
			};
		private:
			bool IsConnect;
			connection* ptr;
		protected:
			connection create_connection(void){
				hmLib_assert(!is_connect(),"inquiry_abstruct have already connected");
				IsConnect=true;
				return connection(this);
			}
		public:
			virtual void disconnect(void){
				hmLib_assert(is_connect(),"inquiry_abstruct have no connection");
				if(ptr)ptr->ptr=nullptr;
				ptr=nullptr;
				IsConnect=false;
			}
			bool is_connect(void)const{return IsConnect;}
		public:
			inquiry_abstruct():ptr(nullptr),IsConnect(false){}
			inquiry_abstruct(inquiry_abstruct&& My_):ptr(My_.ptr),IsConnect(My_.IsConnect){
				My_.ptr=nullptr;
				My_.IsConnect=false;
			}
			const inquiry_abstruct& operator=(inquiry_abstruct&& My_){
				hmLib_assert(!is_connect(),"inquiry_abstruct have already connected");
				std::swap(IsConnect,My_.IsConnect);
				std::swap(ptr,My_.ptr);
				if(ptr)ptr->ptr=this;
				return *this;
			}
			virtual ~inquiry_abstruct(){if(is_connect())disconnect();}
		private:
			inquiry_abstruct(const inquiry_abstruct& My_);
			const inquiry_abstruct& operator=(const inquiry_abstruct& My_);
		};
		typedef inquiry_abstruct::connection connection;
	}
}
#
#endif
