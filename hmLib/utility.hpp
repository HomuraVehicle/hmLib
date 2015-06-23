#ifndef HMLIB_UTILITY_INC
#define HMLIB_UTILITY_INC 100
#
/*===utility===
��ɃI�u�W�F�N�g�̑��쓙�Ɋւ��ėp�N���X/�}�N���ނ�錾����

v1_00/130717
	hmLib_static_restrict��ǉ�
		template�����ɐ錾���邱�ƂŁAtemplate�����̎��s�����ɐ����������}�N��
	clone�֐���ǉ�
		�R�s�[�R���X�g���N�^/�R�s�[�t�@���N�^���Ăяo���ăN���[���𐶐�����
	exchange�֐���ǉ�
		�l�����ւ��A�O��̒l��Ԃ�
*/
namespace hmLib{
	namespace utility{
		namespace _enabler{
			extern void* enabler;
		}
	}
}
#define hmLib_static_restrict(condition) typename std::enable_if<condition>::type *& = hmLib::utility::_enabler::enabler
namespace hmLib{
	//�N���[���֐�
	template<typename T>
	T clone(const T& t_){return T(t_);}
	template<typename T,template Fn>
	T clone(const T& t_,Fn Func){return Func(t_);}
	//�l����ւ��֐�
	template<typename T, typename U>
	T exchange(T& obj, U&& new_val) {
		T old_val = std::move(obj);
		obj = std::forward<U>(new_val);
		return old_val;
	}
}
#
#endif
