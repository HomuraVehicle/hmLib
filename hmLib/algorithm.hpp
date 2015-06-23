#ifndef HMLIB_ALGORITHM_INC
#define HMLIB_ALGORITHM_INC 111
/*===algorithm===
C++ algorthm��⏕����A���S���Y����񋟂���

algorithm v1_11/130529 hmito
	algorithm���O��Ԃ̃t�H���_�w�薼���Ԉ���Ă��������C��
algorithm v1_10/130328 hmito
	algorithm���O��ԂɊ�Â��ăt�@�C�������
algorithm:v1_09/130128 hmIto
	roulette_sampler��sync�֐���ǉ�
		roulette_sampler���̂��ė��p�\�ɕύX
algorithm:v1_08/130109
	roulette_sampler�̍�����
		�����Ŕz��̌`�ŕێ����Ă������ƂŁA�J��Ԃ����̓����������
		std::lower_bound�𗘗p���鎖�ō�����
algorithm.hpp v1_07
		class roulette_sampler�̏�������Begin��s���ɏ��������Ă����̂��C��
algorithm.hpp v1_06
		class random_sampler�̒���
algorithm.hpp v1_05
	�����_���I�����s���ȉ��̃N���X�Ɗ֐���ǉ��B
	//���[���b�g�I���N���X
	template<typename InputIterator,typename fnAssess>
	class roulette_sampler{
	public:
		roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_);
		OutputIterator operator()();
	};
	//���[���b�g�I���N���X�̃r���_�[
	template<typename InputIterator,typename fnAssess>
	roulette_sampler<InputIterator,fnAssess> build_roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_);
algorithm.hpp v1_04
	�����_���I���A���[���b�g�I���Ŏw��͈͂��甲���o���A�ȉ���6�֐���ǉ��B
	//�����_���I��
	template<class InputIterator,class OutputIterator>
	OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out);
	//�����_���I�� OutputIterator�͈̔͂𖄂߂�܂�
	template<class InputIterator,class OutputIterator>
	OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator OutBegin,OutputIterator OutEnd);
	//�����_���I�� n��
	template<class InputIterator,class OutputIterator>
	OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out,unsigned int n);
	//���[���b�g�I��
	template<class InputIterator,class FnRealValue,class OutputIterator>
	OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out);
	//���[���b�g�I�� OutputIterator�͈̔͂𖄂߂�܂�
	template<class InputIterator,class FnRealValue,class OutputIterator>
	OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator OutBegin,OutputIterator OutEnd);
	//���[���b�g�I�� n��
	template<class InputIterator,class FnRealValue,class OutputIterator>
	OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out,unsigned int n);
*/
#ifndef HMLIB_ALGORITHM_COMPARE_INC
#	include"algorithm/compare.hpp"
#endif
#ifndef HMLIB_ALGORITHM_SAMPLING_INC
#	include"algorithm/sampling.hpp"
#endif
#
#endif
