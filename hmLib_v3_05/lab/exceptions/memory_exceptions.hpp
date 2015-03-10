#ifndef HMLIB_EXCEPTIONS_MEMORYEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_MEMORYEXCEPTIONS_INC 100
#
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif

namespace hmLib{
	namespace exceptions{
		//�������[�G���[
		class memory_exception:public virtual exception{
			typedef exception excp_type;
		public:
			explicit memory_exception(const std::string& Message_):excp_type(Message_.c_str()){}
			explicit memory_exception(const char* Message_):excp_type(Message_){}
		};
		//���������蓖�ĂɎ��s�����ꍇ
		class fail_allocation:public memory_exception{
			typedef exception excp_type;
			typedef bad_exception base_type;
		public:
			explicit fail_allocation(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit fail_allocation(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//����������Ɏ��s�����ꍇ
		class fail_deallocation:public memory_exception{
			typedef exception excp_type;
			typedef bad_exception base_type;
		public:
			explicit fail_deallocation(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit fail_deallocation(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//���I�L���X�g�Ɏ��s�����ꍇ
		class incorrect_downcast_request:public memory_exception{
			typedef exception excp_type;
			typedef bad_exception base_type;
		public:
			explicit incorrect_downcast_request(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit incorrect_downcast_request(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
	}
}
#
#endif
