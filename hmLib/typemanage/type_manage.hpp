#ifndef HMLIB_TYPEMANAGE_TYPEMANAGE_INC
#define HMLIB_TYPEMANAGE_TYPEMANAGE_INC 100
#
#include<string>
#include<boost/lexical_cast.hpp>
namespace hmLib{
	namespace typemanage{
		template<typename my_type>
		struct default_type_manage:public my_type::type_manage{};
		template<>
		struct default_type_manage<bool>{
			//�N���X����Ԃ�
			std::string name()const{return "bool";}
			template<typename output_iterator>
			void name_list(output_iterator itr,const std::string& pre)const{
				(*itr++)=pre+name();
			}
			unsigned int size()const{
				return 1;
			}
		};
		template<>
		struct default_type_manage<unsigned int>{
			//�N���X����Ԃ�
			std::string name()const{return "unsigned int";}
			template<typename output_iterator>
			void name_list(output_iterator itr,const std::string& pre)const{
				(*itr++)=pre+name();
			}
			unsigned int size()const{
				return 1;
			}
		};
		template<>
		struct default_type_manage<int>{
			//�N���X����Ԃ�
			std::string name()const{return "int";}
			template<typename output_iterator>
			void name_list(output_iterator itr,const std::string& pre)const{
				(*itr++)=pre+name();
			}
			unsigned int size()const{
				return 1;
			}
		};
		template<>
		struct default_type_manage<double>{
			//�N���X����Ԃ�
			std::string name()const{return "double";}
			template<typename output_iterator>
			void name_list(output_iterator itr,const std::string& pre)const{
				(*itr++)=pre+name();
			}
			unsigned int size()const{
				return 1;
			}
		};
/*		struct type_manage{
			//�N���X����Ԃ�
			std::string name()const;
			//�N���X���𗅗񂷂�
			template<typename output_iterator>
			void name_label(output_iterator itr,const std::string& pre)const;
			//�N���X���𗅗񂷂�
			template<typename output_iterator>
			void name_list(output_iterator itr)const;
			//�N���X���̗��񐔂�Ԃ�
			unsigned int name_list_size()const;
			//�����񂩂�R���X�g���N�g����
			template<typename input_iterator>
			my_type string_build(input_iterator begin,input_iterator end)const;
			//�쐬�ɕK�v�ȕ�����
			template<typename output_iterator>
			void string_build_list(output_iterator itr,const std::string& pre)const:
			//�쐬�ɕK�v�ȕ�����̐�
			unsigned int string_build_list_size()const;
			//�p�����[�^�̒l��^����
			template<typename output_iterator>
			void parameter_label(output_iterator itr,const my_type& val)const;
			//�p�����[�^�̖��O��^����
			template<typename output_iterator>
			void parameter_list(output_iterator itr, const std::string& pre)const;
			//�p�����[�^�̐���^����
			unsigned int parameter_list_size()const;
		};
*/
	}
}
#
#endif
