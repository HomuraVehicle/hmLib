#ifndef HMLIB_EXCEPTIONS_IOEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_IOEXCEPTIONS_INC 100
#
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif
namespace hmLib{
	namespace exceptions{
		//�o�b�t�@��overflow�����ꍇ
		class io_exception:public virtual exception{
			typedef exception base_type;
		public:
			explicit io_exception(const std::string& Message_):excp_type(Message_.c_str()){}
			explicit io_exception(const char* Message_):excp_type(Message_){}
		};
		//�o�b�t�@��overflow�����ꍇ
		class io_overflow:public io_exception{
			typedef exception excp_type;
			typedef invalid_status base_type;
		public:
			explicit io_overflow(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit io_overflow(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//�o�b�t�@��eof�ɒB�����ꍇ
		class io_end_of_file:public io_exception{
			typedef exception excp_type;
			typedef invalid_status base_type;
		public:
			explicit io_end_of_file(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit io_end_of_file(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//stream���J����Ă��Ȃ��ꍇ
		class io_not_opened:public io_exception{
			typedef exception excp_type;
			typedef invalid_request base_type;
		public:
			explicit io_not_opened(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit io_not_opened(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//stream���J����Ă���ꍇ
		class io_opened:public io_exception{
			typedef exception excp_type;
			typedef invalid_request base_type;
		public:
			explicit io_opened(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit io_opened(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
	}
}
#
#endif
