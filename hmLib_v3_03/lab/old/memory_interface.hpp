#ifndef HMLIB_OBJECTINTERFACE_INC
#define HMLIB_OBJECTINTERFACE_INC 1
#
/*===object_interface===
object������{�I�֐��Q�̃C���^�[�t�F�[�X��񋟂���

object_interface:v0_01/130308 hmIto
	clone,copy,move��ǉ�
*/
namespace hmLib{
	namespace interface{
		//���g�̒l�𑊎��copy����copy�֐�
		template<typename my_type>
		struct copy_interface{
		protected:
			virtual void itf_copy(my_type& my_typeo_)=0;
		public:
			void copy(my_type& my_typeo_){itf_copy(my_typeo_);}
		};
		//���g�̒l�𑊎��move����move�֐�
		template<typename my_type>
		struct move_interface{
		protected:
			virtual void itf_move(my_type& my_typeo_)=0;
		public:
			void move(my_type& my_typeo_){itf_copy(my_typeo_);}
		};
		//���I�m�ۂŃR�s�[�����clone�֐� :::allocator���ǂ����邩��肪�c���Ă���
		template<typename my_type>
		struct clone_interface{
		protected:
			virtual void itf_clone(my_type* ptr_)=0;
		public:
			void clone(my_type* ptr_){return itf_clone();}
		};
	}
}
#
#endif
