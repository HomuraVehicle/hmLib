#ifndef HMLIB_EXCEPTIONS_ACCESSEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_ACCESSEXCEPTIONS_INC 100
#
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif
namespace hmLib{
	namespace exceptions{
		//�A�N�Z�X���悤�Ƃ��Ă���I�u�W�F�N�g���̂Ƃ��ɓ�������
		class invalid_access:public virtual exception{
			typedef exception excp_type;
		public:
			explicit invalid_access(const std::string& Message_):excp_type(Message_.c_str()){}
			explicit invalid_access(const char* Message_):excp_type(Message_){}
		};
		//�z��v�f�O�ɃA�N�Z�X���悤�Ƃ����Ƃ��ɓ�������
		class out_of_range_access:public invalid_access{
			typedef exception excp_type;
			typedef invalid_access base_type;
		public:
			explicit out_of_range_access(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit out_of_range_access(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//nullptr�ɃA�N�Z�X���悤�Ƃ����Ƃ��ɓ�������
		class nullptr_dereferemce:public invalid_access{
			typedef exception excp_type;
			typedef invalid_access base_type;
		public:
			explicit nullptr_dereferemce(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit nullptr_dereferemce(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//�s���ȎQ�ƂɃA�N�Z�X���悤�Ƃ��Ă��鎞
		class invalid_reference:public invalid_access{
			typedef exception excp_type;
			typedef invalid_access base_type;
		public:
			explicit invalid_reference(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit invalid_reference(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
	}
}
#
#endif
