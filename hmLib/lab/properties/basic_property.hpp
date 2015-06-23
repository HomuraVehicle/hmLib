#ifndef HMLIB_PROPERTIES_BASICPROPERTY_INC
#define HMLIB_PROPERTIES_BASICPROPERTY_INC 101
#
/*
�ϐ��ւ̃A�N�Z�X����\�ł���Ȃ���A�ϐ��̂悤�Ɉ�����Aproperty�ϐ����`
�Q�Ɛ�̎����Ǘ��͂��Ă��Ȃ��̂ŁA�����Ƃ��āA����X�R�[�v�̕ϐ��̂ݎQ�Ɖ\
�ʃX�R�[�v�̕ϐ��𗘗p����ۂ́Aweak_property�𗘗p����

=== properties::basic_property ===
v1_00/140616 hmIto
�d�l����
*/
#include <functional>
#include <type_traits>
#include "utility.hpp"
#include "exceptions.hpp"
#include "property_connection.hpp"
namespace hmLib {
	namespace properties {
		template<typename T>
		class basic_property{
		public:
			typedef typename std::remove_reference<T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T(void)> getter_func;
			typedef std::function<const T(const T)> setter_func;
		protected:
			basic_property() {}
		protected:
			getter_func getter;
			setter_func setter;
		public://accessor
			const T operator()(void) const { return getter(); }
			operator const T() const { return getter(); }
			const T operator()(const T Value_) { return setter(Value_); }
			const T operator=(const T Value_) { return setter(Value_); }
		};
		template<typename T>
		class basic_property <const T> {
		public:
			typedef typename std::remove_reference<const T>::type value_type;
			typedef typename std::add_lvalue_reference<value_type>::type reference_type;
			typedef std::function<const T(void)> getter_func;
		protected:
			basic_property() {}
		protected:
			getter_func getter;
		public://accessor
			const T operator()(void) const { return getter(); }
			operator const T() const { return getter(); }
		};
	}
}
#
#endif
