#ifndef HMLIB_OBJECTINTERFACE_INC
#define HMLIB_OBJECTINTERFACE_INC 1
#
/*===object_interface===
object������{�I�֐��Q�̃C���^�[�t�F�[�X��񋟂���

object_interface:v0_01/130308 hmIto
	clone,copy,move��ǉ�
*/
namespace hmLib{
	namespace interfaces{
		//���g�̒l�𑊎��copy����copy�֐�
		template<typename my_type>
		struct copy_interface{
		protected:
			virtual void itf_copy(my_type& my_typeo_)const=0;
		public:
			void copy(my_type& my_typeo_)const{itf_copy(my_typeo_);}
		};
		//���g�̒l�𑊎��move����move�֐�
		template<typename my_type>
		struct move_interface{
		protected:
			virtual void itf_move(my_type& my_typeo_)=0;
		public:
			void move(my_type& my_typeo_)const{itf_move(my_typeo_);}
		};
		//���I�m�ۂŃR�s�[�����clone�֐� :::allocator���ǂ����邩��肪�c���Ă���
		template<typename my_type>
		struct clone_interface{
		protected:
			virtual my_type* itf_clone(void)const=0;
		public:
			my_type* clone(void)const{return itf_clone();}
		};
		//���I�m�ۂŃR�s�[�����clone�֐� :::allocator���ǂ����邩��肪�c���Ă���
		template<typename my_type>
		struct destroy_interface{
		protected:
			virtual void itf_destroy(void)=0;
		public:
			void destroy(void){itf_destroy();}
		};
	}
}
#
#endif
