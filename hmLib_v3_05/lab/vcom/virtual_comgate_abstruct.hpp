#ifndef HMLIB_VCOM_VIRTUALCOMGATEABSTRUCT_INC
#define HMLIB_VCOM_VIRTUALCOMGATEABSTRUCT_INC 100
#
/*===virtual_comgate_absturct===
�X���b�h���g���ĉ��z�I��com�ʐM���Č�����N���X�Q
*/
#include<hmLib_v3_05/gate.hpp>
namespace hmLib{
	namespace vcom{
		//���zcom�pgate
		class virtual_comgate_abstruct:public gate{
		public:
			virtual ~virtual_comgate_abstruct(){}
		public: //virtaul_comgate_abstruct
			//com�Ƃ��đ��M����f�[�^���擾����
			virtual size_type com_send(char* ptr_, size_type size_)=0;
			//com�Ƃ��Ď�M������f�[�^��^����
			virtual size_type com_recv(const char* ptr_, size_type size_)=0;
		};
	}
}
#
#endif
