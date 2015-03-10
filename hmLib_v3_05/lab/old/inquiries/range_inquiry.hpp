#ifndef HMLIB_INQUIRIES_RANGEINQUIRY_INC
#define HMLIB_INQUIRIES_RANGEINQUIRY_INC 102
#
/*===inquiries::range_inquiry===
�R���e�i�^�C�v�̕ϐ��ɑ΂��āAiterator��begin/end�֐��ɂ���ĊԐړI�Ɏ擾����N���X�A
inquiries::range_inquiry��񋟁B

inquiries::range_inquiry v1_02/130412 hmIto
	try_lock�֐��̌Ăяo���ŌĂяo�������Ԉ���Ă��������C��
	try_lock��mutex��ێ����Ă��Ȃ��ꍇ�Ƀ��b�N�Ɏ��s���Ă���悤�Ɍ����Ă��������C��
inquiries::range_inquiry:v1_01/130329 hmIto
	�R�s�[�R���X�g���N�^/������Z�q�𖾎��I��private��
	�O���[�o���֐���connect�֐���ǉ�
inquiries::range_inquiry:v1_00/130328 hmIto
	inquiry���番��
*/
#include<memory>
#include<functional>
#ifndef HMLIB_MUTEXPROXY_INC
#	include<hmLib_v3_05/mutex_proxy.hpp>
#endif
#ifndef HMLIB_EXCEPTION_INC
#	include<hmLib_v3_05/exception.hpp>
#endif
#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#	include"inquiry_abstruct.hpp"
#endif
namespace hmLib{
	namespace inquiries{
		//iterator�ւ̎Q��inquiry
		template<typename iterator_>
		class range_inquiry:public inquiry_abstruct{
			typedef range_inquiry<iterator_> my_type;
		private:
			std::function<iterator_(void)> FnBegin;
			std::function<iterator_(void)> FnEnd;
			bool locked;
			std::unique_ptr<mutex_proxy> pmx;
		public:
			range_inquiry():locked(false),FnBegin(),FnEnd(),pmx(nullptr){}
			range_inquiry(my_type&& My_):locked(false),FnBegin(),FnEnd(),pmx(nullptr){
				std::swap(locked,My_.locked);
				std::swap(FnBegin,My_.FnBegin);
				std::swap(FnEnd,My_.FnEnd);
				std::swap(pmx,My_.pmx);
			}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(!is_connect(),"range_inquiry have already connected");
				std::swap(locked,My_.locked);
				std::swap(FnBegin,My_.FnBegin);
				std::swap(FnEnd,My_.FnEnd);
				std::swap(pmx,My_.pmx);
				return *this;
			}
		private:
			range_inquiry(const my_type& My_);
			const my_type& operator=(const my_type& My_);
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
				if(!pmx || pmx->try_lock())locked=true;
				return locked;
			}
		};
		template<typename Iterator,typename Func>
		inquiries::connection connect(range_inquiry<Iterator>& Inq_,const Func& Fnc_){
			return Inq_.connect(Fnc_);
		}
		template<typename Iterator,typename Func,typename Mutex>
		inquiries::connection connect(range_inquiry<Iterator>& Inq_,const Func& Fnc_,Mutex& Mx_){
			return Inq_.connect(Fnc_,Mx_);
		}
	}
}
#
#endif
