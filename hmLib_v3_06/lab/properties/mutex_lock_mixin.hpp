#ifndef HMLIB_PROPERTIES_MUTEXLOCKMIXIN_INC 
#define HMLIB_PROPERTIES_MUTEXLOCKMIXIN_INC 100
#
#ifndef HMLIB_MUTEXPROXY_INC
#	include<hmLib_v3_06/mutex_proxy.hpp>
#endif
namespace hmLib {
	namespace properties {
		class mutex_lock_mixin {
		private:
			bool locked;
			mutex_proxy mxprx;
		protected:
			mutex_lock_mixin() :locked(false), mxprx() {}
			//�R�s�[�֎~
			mutex_lock_mixin(const mutex_lock_mixin& My_)=delete;
			const mutex_lock_mixin& operator=(const mutex_lock_mixin& My_)=delete;
			//���[�uOK
			mutex_lock_mixin(mutex_lock_mixin&& My_) :locked(false), mxprx(My_) {
				std::swap(locked, My_.locked);
				std::swap(mxprx, My_.mxprx);
			}
			const mutex_lock_mixin& operator=(mutex_lock_mixin&& My_) {
				if(this!=&My_) {
					std::swap(locked, My_.locked);
					std::swap(mxprx, My_.mxprx);
				}
				return *this;
			}
		public:
			void lock() {
				if(mxprx.is_proxy())mxprx.lock();
				locked=true;
			}
			void unlock() {
				if(mxprx.is_proxy())mxprx.unlock();
				locked=false;
			}
			bool try_lock() {
				if(!mxprx.is_proxy() || mxprx.try_lock())locked=true;
				return locked;
			}
		protected:
			void set_mutex (mutex_proxy&& mMx_) {
				mxprx=std::move(mMx_);
			}
		};
	}
}
#
#endif
