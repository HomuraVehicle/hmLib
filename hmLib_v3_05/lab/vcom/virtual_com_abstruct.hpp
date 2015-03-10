#ifndef HMLIB_VCOM_VIRTUALCOMABSTRUCT_INC
#define HMLIB_VCOM_VIRTUALCOMABSTRUCT_INC 100
#
/*===virtual_com===
�X���b�h���g���ĉ��z�I��com�ʐM���Č�����N���X�Q
*/
#include<deque>
#include"virtual_comgate_abstruct.hpp"
namespace hmLib{
	namespace vcom{
		//���zcom
		class virtual_com_abstruct{
		public:
			virtual ~virtual_com_abstruct(){}
		public: //virtual_com_abstruct
			//virtual_comgate��ڑ�����
			virtual void connect(virtual_comgate_abstruct* ptr)=0;
			//virtual_comgate��ؒf����
			virtual void disconnect(virtual_comgate_abstruct* ptr)=0;
			//virtual_comgate���ڑ�����Ă��邩���m�F����
			virtual bool is_connect(virtual_comgate_abstruct* ptr=nullptr)=0;
		};
	}
}
#
#endif
