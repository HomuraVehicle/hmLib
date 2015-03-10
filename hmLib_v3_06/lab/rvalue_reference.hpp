#ifndef HMLIB_RVALUEREFERENCE_INC
#define HMLIB_RVALUEREFERENCE_INC 100
#
/*
���O�̉E�Ӓl�Q��&���[�u�p�N���X
C++03�������ł���A���R�{���͔񐄏�

=== rvalue_reference ===
v1_00/140405 hmIto
	�쐬
*/
namespace hmLib {
	template<typename T>
	struct rvalue_reference {
		T& ref;
		explicit rvalue_reference(T& ref_) :ref(ref_) {}
	};
	template<typename T>
	inline rvalue_reference<T> move(T& Ptr_) { return rvalue_reference<T>(Ptr_); }
}
#
#endif
