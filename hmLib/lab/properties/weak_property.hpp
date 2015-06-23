#ifndef HMLIB_PROPERTIES_WEAKPROPERTY_INC
#define HMLIB_PROPERTIES_WEAKPROPERTY_INC 101
#
/*
property���Q�Ƃ��ăA�N�Z�X����Aweak_property�N���X

=== properties::weak_property ===
v1_01/140621 hmIto
	�ꉞ�A��������
v1_00/140616 hmIto
	property���Q�Ƃ���N���X�Ƃ��čĒ�`
=== inquiries::inquiry ===
v2_00/130415 hmito
	const�Q�Ƃ�߂�l�Ƃ���֐���ێ�����I�u�W�F�N�g�Ƃ��čĒ�`
v1_02/130412 hmIto
	try_lock�֐��̌Ăяo���ŌĂяo�������Ԉ���Ă��������C��
	try_lock��mutex��ێ����Ă��Ȃ��ꍇ�Ƀ��b�N�Ɏ��s���Ă���悤�Ɍ����Ă��������C��
v1_01/130329 hmIto
	�R�s�[�R���X�g���N�^/������Z�q�𖾎��I��private��
	�O���[�o���֐���connect�֐���ǉ�
 v1_00/130328 hmIto
	inquiry���番��
*/
#include<memory>
#include<functional>
#include"property.hpp"
#include"mutex_lock_mixin.hpp"
#include"property_connection.hpp"
namespace hmLib{
	namespace properties {
		template<typename T>
		class weak_property :public mutex_lock_mixin, public connection_client_mixin {
		public:
			typedef typename std::remove_reference<T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T(void)> getter_func;
			typedef std::function<const T(const T)> setter_func;
		protected:
			getter_func getter;
			setter_func setter;
		public:
			template<typename U>
			void connect(property<U>& Property_) {
				static_assert(!std::is_const<std::remove_reference<U>::type>::value, "weak_property<T> cannot open property<const T>");
				client_connect(Property_);
				getter =[&]()->const T{return Property_();};
				setter =[&](const T Val_)->const T{return Property_(Val_); };
			}
			template<typename U,typename mutex_>
			void connect(property<U>& Property_, mutex_& Mutex_) {
				static_assert(!std::is_const<std::remove_reference<U>::type>::value, "weak_property<T> cannot open property<const T>");
				client_connect(Property_);
				getter =[&]()->const T{return Property_(); };
				setter =[&](const T Val_)->const T{return Property_(Val_);};
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
			template<typename U>
			void forced_connect(property<U>& Property_) {
				static_assert(!std::is_const<std::remove_reference<U>::type>::value, "weak_property<T> cannot open property<const T>");
				client_connect(Property_);
				getter =[&]()->const T{return static_cast<const T>(Property_());};
				setter =[&](const T Val_)->const T{return static_cast<const T>(Property_(static_cast<U>(Val_))); };
			}
			template<typename U, typename mutex_>
			void forced_connect(property<U>& Property_, mutex_& Mutex_) {
				static_assert(!std::is_const<std::remove_reference<U>::type>::value, "weak_property<T> cannot open property<const T>");
				client_connect(Property_);
				getter =[&]()->const T{return static_cast<const T>(Property_()); };
				setter =[&](const T Val_)->const T{return static_cast<const T>(Property_(static_cast<U>(Val_)));};
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
		public://accessor
			const T operator()(void) const { 
				hmLib_assert(is_connect(), exceptions::not_connected,"weak_property have not opened property.");
				return getter(); 
			}
			operator const T() const { 
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
			const T operator()(const T Value_) {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return setter(Value_);
			}
			const T operator=(const T Value_) {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return setter(Value_);
			}
		};
		template<typename T>
		class weak_property<T&> :public mutex_lock_mixin, public connection_client_mixin {
		public:
			typedef typename std::remove_reference<T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T&(void)> getter_func;
			typedef std::function<const T&(const T&)> setter_func;
		protected:
			getter_func getter;
			setter_func setter;
		public:
			void connect(property<T&>& Property_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_(); };
				setter =[&](const T& Val_)->const T&{return Property_(Val_);};
			}
			template<typename mutex_>
			void connect(property<T&>& Property_, mutex_& Mutex_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_();};
				setter =[&](const T Val_)->const T{return Property_(Val_); };
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
		public://accessor
			const T& operator()(void) const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
			operator const T&() const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
			const T& operator()(const T& Value_) {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return setter(Value_);
			}
			const T& operator=(const T& Value_) {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return setter(Value_);
			}
		};
		template<typename T>
		class weak_property<const T> :public mutex_lock_mixin, public connection_client_mixin {
		public:
			typedef typename std::remove_reference<const T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T(void)> getter_func;
		protected:
			getter_func getter;
		public:
			template<typename U>
			void connect(property<U>& Property_) {
				client_connect(Property_);
				getter =[&]()->const T{return Property_(); };
			}
			template<typename U, typename mutex_>
			void connect(property<U>& Property_, mutex_& Mutex_) {
				client_connect(Property_);
				getter =[&]()->const T{return Property_();};
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
			template<typename U>
			void forced_connect(property<U>& Property_) {
				client_connect(Property_);
				getter =[&]()->const T{return static_cast<const T>(Property_());};
			}
			template<typename U, typename mutex_>
			void forced_connect(property<U>& Property_, mutex_& Mutex_) {
				client_connect(Property_);
				getter =[&]()->const T{return static_cast<const T>(Property_());};
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
		public://accessor
			const T operator()(void) const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
			operator const T() const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
		};
		template<typename T>
		class weak_property<const T&> :public mutex_lock_mixin, public connection_client_mixin{
		public:
			typedef typename std::remove_reference<const T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T&(void)> getter_func;
		protected:
			getter_func getter;
		public:
			void connect(property<T&>& Property_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_();};
			}
			void connect(property<const T&>& Property_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_(); };
			}
			template<typename mutex_>
			void connect(property<T&>& Property_, mutex_& Mutex_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_();};
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
			template<typename mutex_>
			void connect(property<const T&>& Property_, mutex_& Mutex_) {
				client_connect(Property_);
				getter =[&]()->const T&{return Property_(); };
				set_mutex(std::move(mutex_proxy(Mutex_)));
			}
		public://accessor
			const T& operator()(void) const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
			operator const T&() const {
				hmLib_assert(is_connect(), exceptions::not_connected, "weak_property have not opened property.");
				return getter();
			}
		};
	}
}
#
#endif
