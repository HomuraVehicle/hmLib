#ifndef HMLIB_INQUIRIES_INQUIRY_INC
#define HMLIB_INQUIRIES_INQUIRY_INC 200
#
/*===inquiries::inquiry===
inquiry�N���X
	������I�u�W�F�N�g�Ɛڑ����邱�Ƃ��ł���B
	operator()(void)�ŁA�ڑ������I�u�W�F�N�g��const�Ŏ擾���邱�Ƃ��ł���B
	lock/unlock/try_lock�֐��ŁA�I�u�W�F�N�g���ꎞ�I�ɃX���b�h�r���I�ɗ��p���邱�Ƃ��ł���B

inquiries::inquiry_v2_00/130415 hmito
	const�Q�Ƃ�߂�l�Ƃ���֐���ێ�����I�u�W�F�N�g�Ƃ��čĒ�`
inquiries::inquiry v1_02/130412 hmIto
	try_lock�֐��̌Ăяo���ŌĂяo�������Ԉ���Ă��������C��
	try_lock��mutex��ێ����Ă��Ȃ��ꍇ�Ƀ��b�N�Ɏ��s���Ă���悤�Ɍ����Ă��������C��
inquiries::inquiry v1_01/130329 hmIto
	�R�s�[�R���X�g���N�^/������Z�q�𖾎��I��private��
	�O���[�o���֐���connect�֐���ǉ�
inquiries::inquiry v1_00/130328 hmIto
	inquiry���番��
*/
#include<memory>
#include<functional>
#ifndef HMLIB_MUTEXPROXY_INC
#	include<hmLib_v3_06/mutex_proxy.hpp>
#endif
#ifndef HMLIB_EXCEPTIONS_INC
#	include<hmLib_v3_06/exceptions.hpp>
#endif
#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#	include"inquiry_abstruct.hpp"
#endif
namespace hmLib{
	namespace inquiries{
		//�ϐ��ւ̎Q��inquiry
		template<typename T>
		class inquiry:public inquiry_abstruct{
		private:
			typedef inquiry<T> my_type;
	   public:
			typedef std::function<const T(void)> func_type;
		private:
			func_type func;
			bool locked;
			mutex_proxy mxprx;
		public:
			inquiry():locked(false),mxprx(){}
			inquiry(my_type&& My_) :locked(false), mxprx(){
				std::swap(locked,My_.locked);
				std::swap(mxprx,My_.mxprx);
				inquiry_abstruct::operator=(std::move(My_));
			}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(!is_connect(), connected_exception, "inquiry have already connected");
				if(this==&My_)return *this;
				std::swap(locked, My_.locked);
				std::swap(mxprx, My_.mxprx);
				inquiry_abstruct::operator=(std::move(My_));
				return *this;
			}
		private:
			inquiry(const my_type& My_);
			const my_type& operator=(const my_type& My_);
		public:
			connection connect(const func_type& func_){
				hmLib_assert(!is_connect(),connected_exception,"inquiry have already connected");
				func=func_;
				return create_connection();
			}
			template<typename Mutex_>
			connection connect(const func_type& func_,Mutex_& mx_){
				hmLib_assert(!is_connect(),connected_exception,"inquiry have already connected");
				func=func_;
				mxprx=std::move(mutex_proxy(mx_));
				return create_connection();
			}
			const T operator()(void)const{
				hmLib_assert(is_connect(),unconnected_exception,"inquiry have not connected yet");
				return func();
			}
			void lock(){
				hmLib_assert(is_connect(),unconnected_exception,"inquiry have not connected yet");
				if(mxprx.is_proxy())mxprx.lock();
				locked=true;
			}
			void unlock(){
				hmLib_assert(is_connect(),unconnected_exception,"inquiry have not connected yet");
				if(mxprx.is_proxy())mxprx.unlock();
				locked=false;
			}
			bool try_lock(){
				hmLib_assert(is_connect(),unconnected_exception,"inquiry have not connected yet");
				if(!mxprx.is_proxy() || mxprx.try_lock())locked=true;
				return locked;
			}
		};
		template<typename T>
		inquiries::connection connect(inquiry<T>& Inq_,typename inquiry<T>::func_type&& Func_){
			return Inq_.connect(std::move(Func_));
		}
		template<typename T,typename Mutex>
		inquiries::connection connect(inquiry<T>& Inq_,typename inquiry<T>::func_type&& Func_,Mutex& Mx_){
			return Inq_.connect(std::move(Func_),Mx_);
		}
		template<typename T>
		std::function<const T&(void)> make_ref(const T& value_){return [&](void)->const T&{return value_;};}
		template<typename T>
		inquiries::connection connect(inquiry<T>& Inq_,const T& Val_){
			return Inq_.connect(make_ref(Val_));
		}
		template<typename T,typename Mutex>
		inquiries::connection connect(inquiry<T>& Inq_,const T& Val_,Mutex& Mx_){
			return Inq_.connect(make_ref(Val_),Mx_);
		}
	}
}
#
#endif
