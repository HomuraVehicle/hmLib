#ifndef HMLIB_MUTEXPROXY_INC
#define HMLIB_MUTEXPROXY_INC 101
#
/*===mutex_proxy===
�ėpMutex���󂯎���đ㗝�I�ɋ@�\����

mutex_proxy v1_01/130412 hmIto
	try_lock��try_locki�ƂȂ��Ă����v���I�Ȗ����C��
mutex_proxy:v1_00/130308 hmIto
	�ėpmutex�Q�ƃN���X�Amutex_proxy��ǉ�
*/
#include<functional>
namespace hmLib{
	class mutex_proxy{
	private:
		std::function<void(void)> FnLock;
		std::function<void(void)> FnUnlock;
		std::function<bool(void)> FnTryLock;
	public:
		template<typename mutex_>
		mutex_proxy(mutex_& Mx_)
			:FnLock(std::bind(std::mem_fn(&mutex_::lock),std::ref(Mx_)))
			,FnUnlock(std::bind(std::mem_fn(&mutex_::unlock),std::ref(Mx_)))
			,FnTryLock(std::bind(std::mem_fn(&mutex_::try_lock),std::ref(Mx_))){
		}
	public:
		void lock(){FnLock();}
		void unlock(){FnUnlock();}
		bool try_lock(){return FnTryLock();}
	};
}
#
#endif
