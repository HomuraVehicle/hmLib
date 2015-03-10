#ifndef HMLIB_INQUIRIES_UNIQUECONNECTIONS_INC
#define HMLIB_INQUIRIES_UNIQUECONNECTIONS_INC 100
#
/*===inquiries::unique_connections===
inquiry�N���X�̐ڑ����Ǘ����Adestructor��diconnect���ĂԁB

inquiries::unique_connections v1_00/130328 hmIto
	inquiry���番��
*/
#include<vector>
#ifndef HMLIB_EXCEPTION_INC
#	include<hmLib_v3_06/exception.hpp>
#endif
#ifndef HMLIB_INQUIRIES_INQUIRYABSTRUCT_INC
#	include"inquiry_abstruct.hpp"
#endif
namespace hmLib{
	namespace inquiries{
		//connection�Ǘ��p�N���X
		class unique_connections{
		private:
			typedef unique_connections my_type;
		private:
			std::vector<connection> Connections;
		public:
			unique_connections(){}
			unique_connections(my_type&& My_){Connections.swap(My_.Connections);}
			const my_type& operator=(my_type&& My_){
				hmLib_assert(Connections.size()==0,"Connections already have a connection");
				Connections.swap(My_.Connections);
				return *this;
			}
			~unique_connections(){
				for(auto itr=std::begin(Connections);itr!=std::end(Connections);++itr)itr->disconnect();
			}
		private:
			unique_connections(const my_type&);
			const my_type& operator=(const my_type& My_);
		public:
			void operator()(connection&& Connection_){Connections.push_back(std::move(Connection_));}
			void disconnect(){
				for(auto itr=std::begin(Connections);itr!=std::end(Connections);++itr)itr->disconnect();
				Connections.clear();
			}
		};
	}
}
#
#endif
