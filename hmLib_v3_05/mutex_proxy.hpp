#ifndef HMLIB_MUTEXPROXY_INC
#define HMLIB_MUTEXPROXY_INC 102
#
/*===mutex_proxy===
�ėpMutex���󂯎���đ㗝�I�ɋ@�\����

mutex_proxy v1_02/130420 hmIto
	�󃊃t�@�����X�����e����悤�ɏC��
mutex_proxy v1_01/130412 hmIto
	try_lock��try_locki�ƂȂ��Ă����v���I�Ȗ����C��
mutex_proxy:v1_00/130308 hmIto
	�ėpmutex�Q�ƃN���X�Amutex_proxy��ǉ�
*/
#include<functional>
#include<hmLib_v3_05/exceptions.hpp>
namespace hmLib{
	class mutex_proxy{
	private:
		bool Active;
		std::function<void(void)> FnLock;
		std::function<void(void)> FnUnlock;
		std::function<bool(void)> FnTryLock;
	private:
		mutex_proxy(const mutex_proxy& My_);
		const mutex_proxy& operator=(const mutex_proxy& My_);
	public:
		mutex_proxy():Active(false){}
		mutex_proxy(mutex_proxy&& My_):Active(false){
			std::swap(Active,My_.Active);
			std::swap(FnLock,My_.FnLock);
			std::swap(FnUnlock,My_.FnUnlock);
			std::swap(FnTryLock,My_.FnTryLock);
		}
		const mutex_proxy& operator=(mutex_proxy&& My_){
			std::swap(Active,My_.Active);
			std::swap(FnLock,My_.FnLock);
			std::swap(FnUnlock,My_.FnUnlock);
			std::swap(FnTryLock,My_.FnTryLock);
			return *this;
		}
		template<typename mutex_>
		mutex_proxy(mutex_& Mx_)
			:Active(true)
			,FnLock(std::bind(std::mem_fn(&mutex_::lock),std::ref(Mx_)))
			,FnUnlock(std::bind(std::mem_fn(&mutex_::unlock),std::ref(Mx_)))
			,FnTryLock(std::bind(std::mem_fn(&mutex_::try_lock),std::ref(Mx_))){
		}
	public:
		bool is_proxy()const{return Active;}
	public:
		void lock(){
			hmLib_assert(Active,exceptions::invalid_access,"mutex_proxy have no reference");
			FnLock();
		}
		void unlock(){
			hmLib_assert(Active,exceptions::invalid_access,"mutex_proxy have no reference");
			FnUnlock();
		}
		bool try_lock(){
			hmLib_assert(Active,exceptions::invalid_access,"mutex_proxy have no reference");
			return FnTryLock();
		}
	};
}
#
#endif