#ifndef HMLIB_INQUIRIES_SIGNALINQUIRY_INC
#define HMLIB_INQUIRIES_SIGNALINQUIRY_INC 101
#
/*===inquiries::signal_inquiry===
operator()(void)�ŁA�擾�����l��Ԃ����ɁASignal�𔭐M����inquiry

inquiries::signal_inquiry v1_01/130329 hmIto
	inquiry�Œl�擾�������ʁA�O��̒l�ƕς��Ȃ��ꍇ��signal�𔭐M����Achanged_signal_inquiry��ǉ�
	�R�s�[�R���X�g���N�^/������Z�q�𖾎��I��private��
	�O���[�o���֐���connect�֐���ǉ�
inquiries::signal_inquiry v1_00/130328 hmIto
	�V�K�쐬
*/
#include<boost/signals2.hpp>
#ifndef HMLIB_EXCEPTION_INC
#	include<hmLib_v3_05/exception.hpp>
#endif
#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#	include"inquiry_abstruct.hpp"
#endif
namespace hmLib{
	namespace inquiries{
		template<typename T>
		class signal_inquiry:public inquiry_abstruct{
			typedef signal_inquiry<T> my_type;
			typedef std::function<const T(void)> func_type;
			typedef boost::signals2::signal<void(const T&)> signal;
		public:
			signal Signal;
		private:
			func_type func;
			bool locked;
			std::unique_ptr<mutex_proxy> pmx;
		public:
			signal_inquiry():func(),locked(false),pmx(){}
			signal_inquiry(my_type&& My_):func(),locked(false),pmx(){
				std::swap(func,My_.func);
				std::swap(locked,My_.locked);
				std::swap(pmx,My_.pmx);
			}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				std::swap(func,My_.func);
				std::swap(locked,My_.locked);
				std::swap(pmx,My_.pmx);
				return *this;
			}
		private:
			signal_inquiry(const my_type& My_);
			const my_type& operator=(const my_type& My_);
		public:
			connection connect(func_type&& func_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				func=func_;
				return create_connection();
			}
			template<typename Mutex_>
			connection connect(func_type&& func_,Mutex_& mx_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				func=func_;
				pmx.reset(new mutex_proxy(mx_));
				return create_connection();
			}
			void operator()(void)const{
				hmLib_assert(is_connect(),"signal_inquiry have not connected yet");
				if(pmx){
					std::lock_guard<mutex_proxy> Lock(*pmx);
					Signal(func_());
				}else{
					Signal(func_());
				}
			}
		};
		template<typename T>
		class changed_signal_inquiry:public inquiry_abstruct{
			typedef signal_inquiry<T> my_type;
			typedef std::function<const T(void)> func_type;
			typedef boost::signals2::signal<void(const T&)> signal;
		public:
			signal Signal;
		private:
			func_type func;
			bool locked;
			std::unique_ptr<mutex_proxy> pmx;
		public:
			signal_inquiry():func(),locked(false),pmx(){}
			signal_inquiry(my_type&& My_):func(),locked(false),pmx(){
				std::swap(func,My_.func);
				std::swap(locked,My_.locked);
				std::swap(pmx,My_.pmx);
			}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				std::swap(func,My_.func);
				std::swap(locked,My_.locked);
				std::swap(pmx,My_.pmx);
				return *this;
			}
		private:
			signal_inquiry(const my_type& My_);
			const my_type& operator=(const my_type& My_);
		public:
			connection connect(func_type&& func_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				func=func_;
				return create_connection();
			}
			template<typename Mutex_>
			connection connect(func_type&& func_,Mutex_& mx_){
				hmLib_assert(!is_connect(),"signal_inquiry have already connected");
				func=func_;
				pmx.reset(new mutex_proxy(mx_));
				return create_connection();
			}
			void operator()(void)const{
				hmLib_assert(is_connect(),"signal_inquiry have not connected yet");
				if(pmx){
					std::lock_guard<mutex_proxy> Lock(*pmx);
					Signal(func_());
				}else{
					Signal(func_());
				}
			}
		};
	}
}
#
#endif
