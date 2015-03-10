#ifndef HMLIB_EXCEPTIONS_ACCESSEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_ACCESSEXCEPTIONS_INC 100
#
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif
namespace hmLib{
	namespace exceptions{
		namespace access {
			//�A�N�Z�X���悤�Ƃ��Ă���I�u�W�F�N�g���̂Ƃ��ɓ�������
			template<typename base_type_=exception>
			class invalid_access :public base_type_ {
				typedef base_type_ base_type;
			public:
				explicit invalid_access(const std::string& Message_) :base_type(Message_.c_str()) {}
				explicit invalid_access(const char* Message_) :base_type(Message_) {}
			};
			//�z��v�f�O�ɃA�N�Z�X���悤�Ƃ����Ƃ��ɓ�������
			template<typename base_type_=exception>
			class out_of_range_access :public invalid_access<base_type_> {
				typedef invalid_access<base_type_> base_type;
			public:
				explicit out_of_range_access(const std::string& Message_) :base_type(Message_.c_str()) {}
				explicit out_of_range_access(const char* Message_) :base_type(Message_) {}
			};
			//nullptr�ɃA�N�Z�X���悤�Ƃ����Ƃ��ɓ�������
			template<typename base_type_=exception>
			class nullptr_dereference :public invalid_access<base_type_> {
				typedef invalid_access<base_type_> base_type;
			public:
				explicit nullptr_dereference(const std::string& Message_) :base_type(Message_.c_str()) {}
				explicit nullptr_dereference(const char* Message_) :base_type(Message_) {}
			};
			//�s���ȎQ�ƂɃA�N�Z�X���悤�Ƃ��Ă��鎞
			template<typename base_type_=exception>
			class invalid_reference :public invalid_access<base_type_> {
				typedef invalid_access<base_type_> base_type;
			public:
				explicit invalid_reference(const std::string& Message_) :base_type(Message_.c_str()) {}
				explicit invalid_reference(const char* Message_) :base_type(Message_) {}
			};
		}
	}
	namespace access_exceptions {
		typedef exceptions::access::invalid_access<> invalid_access;
		typedef exceptions::access::out_of_range_access<> out_of_range_access;
		typedef exceptions::access::nullptr_dereference<> nullptr_dereference;
		typedef exceptions::access::invalid_reference<> invalid_reference;
	}
}
#
#endif
