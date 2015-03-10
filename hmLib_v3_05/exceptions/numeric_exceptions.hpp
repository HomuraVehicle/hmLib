#ifndef HMLIB_EXCEPTIONS_NUMERICEXCEPTIONS_INC
#define HMLIB_EXCEPTIONS_NUMERICEXCEPTIONS_INC 100
#
#ifndef HMLIB_EXCEPTIONS_EXCEPTION_INC
#	include"exception.hpp"
#endif
#ifndef HMLIB_EXCEPTIONS_COREEXCEPTIONS_INC
#	include"core_exceptions.hpp"
#endif
namespace hmLib{
	namespace exceptions{
		//�ŏ��������̒l�͈̔͊O�ɒl������ꍇ
		class invalid_initialvalue:public invalid_status{
			typedef exception excp_type;
			typedef invalid_status base_type;
		public:
			explicit invalid_initialvalue(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit invalid_initialvalue(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//�v�Z�̌��ʁA�K��̒l�͈̔͊O�ɂȂ����ꍇ
		class out_of_valuerange:public invalid_status{
			typedef exception excp_type;
			typedef invalid_status base_type;
		public:
			explicit out_of_valuerange(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit out_of_valuerange(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//�s���ȎZ�p���Z��v�������ꍇ 0���Z��
		class incorrect_arithmetic_request:public invalid_request{
			typedef exception excp_type;
			typedef invalid_request base_type;
		public:
			explicit incorrect_arithmetic_request(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit incorrect_arithmetic_request(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
		//�s���ȎZ�p���Z���s��ꂽ�ꍇ 0���Z��
		class incorrect_arithmetic_occurrence:public invalid_status{
			typedef exception excp_type;
			typedef invalid_status base_type;
		public:
			explicit incorrect_arithmetic_occurrence(const std::string& Message_):excp_type(Message_.c_str()),base_type(Message_.c_str()){}
			explicit incorrect_arithmetic_occurrence(const char* Message_):excp_type(Message_),base_type(Message_){}
		};
	}
}
#
#endif
