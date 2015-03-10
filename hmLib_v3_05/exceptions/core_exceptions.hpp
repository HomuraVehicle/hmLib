#ifndef HMLIB_EXCEPTIONS_COREEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_COREEXCEPTIONS_INC 100
#
#include<string>
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif
namespace hmLib{
	namespace exceptions{
		//���炩�̃��Z�b�g�������Ȃ��ƍċN�s�\�ȗ�O
		class bad_exception:public virtual exception{
			typedef exception base_type;
		public:
			explicit bad_exception(const std::string& Message_):base_type(Message_.c_str()){}
			explicit bad_exception(const char* Message_):base_type(Message_){}
		};
		//�v���������������ߎ��s�������A�I�u�W�F�N�g�͐���
		class invalid_request:public virtual exception{
			typedef exception base_type;
		public:
			explicit invalid_request(const std::string& Message_):base_type(Message_.c_str()){}
			explicit invalid_request(const char* Message_):base_type(Message_){}
		};
		//���ʂ������������ߎ��s�������A�I�u�W�F�N�g�͐���
		class invalid_status:public virtual exception{
			typedef exception base_type;
		public:
			explicit invalid_status(const std::string& Message_):base_type(Message_.c_str()){}
			explicit invalid_status(const char* Message_):base_type(Message_){}
		};
	}
}

#
#endif
