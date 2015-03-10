#ifndef HMLIB_INQUIRIES_SIGNALEDCONTACT_INC
#define HMLIB_INQUIRIES_SIGNALEDCONTACT_INC 101
#
/*===inquiries::signaled_contact===
signal�Ŏ󂯎�����l��ێ����āAinquiry�ł̗v���ɂ�������N���X

inquiries::signaled_contact v1_00/130421 hmIto
	signaled_contact�ǉ�
*/
#include<mutex>
#include<boost/signals2.hpp>
#ifndef HMLIB_EXCEPTIONS_INC
#	include<hmLib_v3_05/exceptions.hpp>
#endif
#ifndef HMLIB_SIGNALS_INC
#	include<hmLib_v3_05/signals.hpp>
#endif
#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#	include"inquiry_abstruct.hpp"
#endif
#ifndef HMLIB_INQUIRIES_UNIQUECONNECTIONS_INC
#	include"unique_connections.hpp"
#endif
namespace hmLib{
	namespace inquiries{
		template<typename T>
		class signaled_contact{
			typedef signaled_contact<T> my_type;
		private:
			T val;
			std::mutex Mutex;
		public:
			signaled_contact(T inival=T()):val(std::move(inival)){}
		private:
			signaled_contact(const my_type& My_);
			const my_type& operator=(const my_type& My_);
		private:
			signals::unique_connections SignalConnections;
			inquiries::unique_connections InquiryConnections;
		public:
			void slot(boost::signals2::signal<void(const T)>& Signal_){
				SignalConnections(signals::connect(Signal_,[&](const T val_)->void{
					std::lock_guard<std::mutex> Lock(this->Mutex);
					this->val=val_;
				}));
			}
			void conatct(inquiries::inquiry<T>& Inquiry_){
				InquiryConnections(inquiries::connect(Inquiry_,[&](void)->const T{return this->val;},Mutex));
			}
		};
	}
}
#
#endif
