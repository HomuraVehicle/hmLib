#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#define HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC 104
#
/*
===inquiries::inquiry_abstruct===
inquiry�@�\�̊��N���X
connection�ɂ��Ă������ŊǗ����Ă���
v1_04/140503 hmIto
	inquiry�n���move����ƁAdisconnect��connection����ł��Ȃ��Ȃ�����C��
	shared_ptr���g���āAflag���Ǘ�����悤�ɕύX
v1_03/130421 hmIto
	connected/unconnected_exception�ǉ�
v1_02/130410 hmIto
	���[�u������Z�q��swap�֐��̈�����ptr�ł͂Ȃ�nullptr�Ƃ��Ă��������C��
v1_01/130329 hmIto
	���[�u�R���X�g���N�^/������Z�q���ӂ̒v���I�ȃo�O���C��
v1_00/130328 hmIto
	inquiry���番��
*/
#ifndef HMLIB_EXCEPTIONS_INC
#	include<hmLib_v3_06/exceptions.hpp>
#endif
#ifndef HMLIB_MEMORY_CLONECOUNTER_INC
#	include<hmLib_v3_06/lab/memory/clone_counter.hpp>
#endif
namespace hmLib{
	namespace inquiries{
		struct exception_identifier {};
		typedef exceptions::exception_pattern<exception_identifier> inquiry_exception;
		typedef exceptions::io::not_opened<inquiry_exception> unconnected_exception;
		typedef exceptions::io::opened<inquiry_exception> connected_exception;

		//connection�V�X�e����񋟂���@�\
		class inquiry_abstruct{
			typedef std::shared_ptr<bool> shared_connecting_flag;
		public:
			class connection{
			private:
				shared_connecting_flag TergetFlag;
			private:
				connection(const connection& My_);
				const connection& operator=(const connection& My_);
			public:
				connection() :TergetFlag() {}
				explicit connection(const shared_connecting_flag& ConnectingFlag_) :TergetFlag(ConnectingFlag_) {}
				connection(connection&& My_) :TergetFlag() {
					std::swap(TergetFlag, My_.TergetFlag);
				}
				const connection& operator=(connection&& My_){
					hmLib_assert(static_cast<bool>(TergetFlag), connected_exception, "connection already have a pointer");
					std::swap(TergetFlag, My_.TergetFlag);
					return *this;
				}
				~connection(){}
				bool is_connect()const { return static_cast<bool>(TergetFlag) && *TergetFlag; }
				void disconnect() { if(static_cast<bool>(TergetFlag))*TergetFlag=false; }
				friend class inquiry_abstruct;
			};
		private:
			shared_connecting_flag ConnectFlag;
		protected:
			connection create_connection(void){
				hmLib_assert(!is_connect(),connected_exception,"inquiry_abstruct have already connected");
				//�Q�Ƃ��Ă�l���܂�����΁A�V���ɍ쐬
				if(!ConnectFlag || !ConnectFlag.unique())ConnectFlag.reset(new bool(true));
				return connection(ConnectFlag);
			}
		public:
			void disconnect(void){
				hmLib_assert(is_connect(),unconnected_exception,"inquiry_abstruct have no connection");
				*ConnectFlag=false;
			}
			bool is_connect(void)const { 
				if(!ConnectFlag)return false;
				return *ConnectFlag; 
			}
		public:
			inquiry_abstruct() :ConnectFlag() {}
			//�R�s�[�֎~
			inquiry_abstruct(const inquiry_abstruct& My_)=delete;
			const inquiry_abstruct& operator=(const inquiry_abstruct& My_)=delete;
			//���[�u����
			inquiry_abstruct(inquiry_abstruct&& My_) :ConnectFlag(std::move(My_.ConnectFlag)) {}
			const inquiry_abstruct& operator=(inquiry_abstruct&& My_) {
				hmLib_assert(!is_connect(),connected_exception,"inquiry_abstruct have already connected");
				std::swap(ConnectFlag, My_.ConnectFlag);
				return *this;
			}
			virtual ~inquiry_abstruct(){if(is_connect())disconnect();}
		};
		typedef inquiry_abstruct::connection connection;
	}
}
#
#endif
