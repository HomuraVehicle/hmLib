#ifndef HMLIB_INQUIRY_INC
#define HMLIB_INQUIRY_INC 100
#include<memory>
#include<mutex>
#include<functional>
#include<vector>
#include"mutex_proxy.hpp"
#include"../exception.hpp"

/*===inquiry===
�l��\���I�ɎQ�Ǝ擾���邽�߂̋��ʃC���^�[�t�F�[�X��񋟂���
	���S�̂��߁A�������inquiry�N���X�p�^�[���ł�const�Ȑ��䂵��������Ă��Ȃ��B
	�ڑ�����̒l��\���I�ɐ��䂷�邽�߂ɂ́Asignal/slot�p�^�[���̗��p�𐄏����Ă���B
	���p�x��signal/slot���M���������ړI�ł���΁Ainquiry_signal�̗��p�𐄏����Ă���B
	
�񋟃N���X
	inquiry�N���X
		������I�u�W�F�N�g�Ɛڑ����邱�Ƃ��ł���B
		operator()(void)�ŁA�ڑ������I�u�W�F�N�g��const�Ŏ擾���邱�Ƃ��ł���B
		lock/unlock/try_lock�֐��ŁA�I�u�W�F�N�g���ꎞ�I�ɃX���b�h�r���I�ɗ��p���邱�Ƃ��ł���B
	range_inquiry�N���X
		begin/end�֐��𗘗p�ł���I�u�W�F�N�g�Ɛڑ����邱�Ƃ��ł���B
		begin/end�֐��ŁAiterator_���擾�ł���B
		lock/unlock/try_lock�֐��ŁA�I�u�W�F�N�g���ꎞ�I�ɃX���b�h�r���I�ɗ��p���邱�Ƃ��ł���B
	unique_contacts�N���X
		�R���^�N�g�𕡐��ێ����Adestructor�Ăяo������disconnect���Ăяo���悤�ȃN���X�B
inquiry:v1_00/130328 hmIto
	inquiry�̒�`��ύX
		�\���^signal�Ƃ��Ă�inquiry����Aconst�Q�ƒl�擾�N���X�Ƃ��Ă�inquiry�֒�`�ύX�B
	inquiry�ǉ�
		operator()�Œl�Q�Ƌ@�\��񋟂���N���X
		mutex�C���^�[�t�F�[�X�������
	range_inquiry�ǉ�
		�w���iterator��begin/end��񋟂���N���X�B
		mutex�C���^�[�t�F�[�X�������
	unique_connections�ǉ�
		connection�N���X��ێ����Adestructor��disconnect���Ăяo���B
inquiry:v0_03/130324 hmIto
	inquiry��default_value��ǉ�
inquiry:v0_02/130224 hmIto
	inquiry_astruct::connection(inquiry_abstruct*)�̕ϐ������Ԉ���Ă����v���I�o�O���C��
inquiry:v0_01/130224 hmIto
	inquiry�ɂ��Ă͒񋟊J�n
	range_inquiry�́Aiterator_proxy�҂�
*/
namespace hmLib{
	namespace inquiries{
		//connection�V�X�e����񋟂���@�\
		class inquiry_abstruct{
		public:
			class connection{
			private:
				inquiry_abstruct* ptr;
			private:
				connection();
				connection(const connection& My_);
				const connection& operator=(const connection& My_);
			public:
				connection(inquiry_abstruct* ptr_):ptr(ptr_){}
				connection(connection&& My_):ptr(nullptr){
					std::swap(ptr,My_.ptr);
					ptr->ptr=this;
				}
				const connection& operator=(connection&& My_){
					hmLib_assert(ptr==nullptr,"connection already have a pointer");
					ptr=My_.ptr;
					My_.ptr=nullptr;
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
				IsConnect=My_.IsConnect;
				ptr=My_.ptr;
				My_.IsConnect=false;
				My_.ptr=nullptr;
			}
			virtual ~inquiry_abstruct(){if(is_connect())disconnect();}
		private:
			inquiry_abstruct(const inquiry_abstruct& My_);
			const inquiry_abstruct& operator=(const inquiry_abstruct& My_);
		};
		typedef inquiry_abstruct::connection connection;
		//�ϐ��ւ̎Q��inquiry
		template<typename T>
		class inquiry:public inquiry_abstruct{
		private:
			const T* ptr;
			bool locked;
			std::unique_ptr<mutex_proxy> pmx;
		public:
			connection connect(const T& t_){
				hmLib_assert(!is_connect(),"have connected yet");
				ptr=&t_;
				return create_connection();
			}
			template<typename Mutex_>
			connection connect(const T& t_,Mutex_& mx_){
				hmLib_assert(!is_connect(),"have connected yet");
				ptr=&t_;
				pmx.reset(new mutex_proxy(mx_));
				return create_connection();
			}
			const T& operator()(void)const{
				hmLib_assert(is_connect(),"have not connected yet");
				return *ptr;
			}
			void lock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx)	pmx->lock();
				locked=true;
			}
			void unlock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx)pmx->unlock();
				locked=false;
			}
			bool try_lock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx && pmx->try_lcok())locked=true;
				return locked;
			}
		};
		//�R���e�i�ւ̎Q��inquiry
		template<typename iterator_>
		class range_inquiry:public inquiry_abstruct{
		private:
			std::function<iterator_(void)> FnBegin;
			std::function<iterator_(void)> FnEnd;
			bool locked;
			std::unique_ptr<mutex_proxy> pmx;
		public:
			template<typename Containor_>
			connection connect(const Containor_& t_){
				hmLib_assert(!is_connect(),"have connected yet");
				FnBegin=[&](void)->iterator_{return std::begin(t_);};
				FnEnd=[&](void)->iterator_{return std::end(t_);};
				return create_connection();
			}
			template<typename Containor_,typename Mutex_>
			connection connect(const Containor_& t_,Mutex_& mx_){
				hmLib_assert(!is_connect(),"have connected yet");
				FnBegin=[&](void)->iterator_{return std::begin(t_);};
				FnEnd=[&](void)->iterator_{return std::end(t_);};
				pmx.reset(new mutex_proxy(mx_));
				return create_connection();
			}
			iterator_ begin()const{
				hmLib_assert(is_connect(),"have not connected yet");
				return FnBegin();
			}
			iterator_ end()const{
				hmLib_assert(is_connect(),"have not connected yet");
				return FnEnd();
			}
			void lock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx)	pmx->lock();
				locked=true;
			}
			void unlock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx)pmx->unlock();
				locked=false;
			}
			bool try_lock(){
				hmLib_assert(is_connect(),"have not connected yet");
				if(pmx && pmx->try_lcok())locked=true;
				return locked;
			}
		};
		//connection�Ǘ��p�N���X
		class unique_connections{
		private:
			typedef unique_connections my_type;
		private:
			std::vector<connection> Connections;
		public:
			unique_connections(){}
			unique_connections(my_type&& My_){Connections.swap(My_.Connections);}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(Connections.size()==0,"Connections already have a connection");
				Connections.swap(My_.Connections);
				return *this;
			}
			~unique_connections(){
				for(auto itr=std::begin(Connections);itr!=std::end(Connections);++itr)itr->disconnect();
			}
		private:
			unique_connections(const my_type&);
			const my_type& operator=(const my_type& My_);
		public:
			void operator()(connection&& Connection_){Connections.push_back(std::move(Connection_));}
			void disconnect(){
				for(auto itr=std::begin(Connections);itr!=std::end(Connections);++itr)itr->disconnect();
				Connections.clear();
			}
		};
	}
}
#
#endif
