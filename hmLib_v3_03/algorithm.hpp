#ifndef HMLIB_ALGORITHM_INC
#define HMLIB_ALGORITHM_INC 109
/*
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
#include<algorithm>
#include"random.hpp"


namespace hmLib{
	namespace algorithm{
		//2�v�f��sort
		template<class T>
		inline void sort_swap(T& val1,T& val2){if(val1>val2)swap(val1,val2);}
		//3�v�f��sort
		template<class T>
		inline void sort_swap(T& val1,T& val2,T& val3){
			if(val1>val2)swap(val1,val2);
			if(val2>val3){
				swap(val2,val3);
				if(val1>val2)swap(val1,val2);
			}
		}
		//3�v�f��median
		template<class T>
		inline T med(T val1,T val2,T val3){
			if(val1>val2){
				if(val2>val3)return val2;
				else if(val1>val3)return val3;
				else return val1;
			}else{
				if(val1>val3)return val1;
				else if(val2>val3)return val3;
				else return val2;
			}
		}
		//3�v�f��min
		template<class T>
		inline T min(T val1,T val2,T val3){return std::min(val1,std::min(val2,val3));}
		//3�v�f��max
		template<class T>
		inline T max(T val1,T val2,T val3){return std::max(val1,std::max(val2,val3));}
		//���ɂȂ�Ȃ��]��
		template<class T>
		inline T positive_mod(T num,T divisor){
			if(num>=0)return num%divisor;
			else return divisor-1-((-1-num)%divisor);
		}
		//cnd�̏����łǂ����Ԃ����ς��ȈՊ֐�
		template <class T>
		inline const T& sel(bool cnd,const T& trueAns,const T& falseAns){
			if(cnd)return trueAns;
			else return falseAns;
		}
		//�����_���I��
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out){
			unsigned int Size=0;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr)++Size;

			unsigned int Pos=hmLib::random::uniform_int(0,Size-1);
			Itr=Begin;
			for(unsigned int Cnt=0;Cnt<Pos;++Cnt)++Itr;
			*Out=*Itr;
			++Out;

			return Out;
		}
		//�����_���I�� OutputIterator�͈̔͂𖄂߂�܂�
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator OutBegin,OutputIterator OutEnd){
			unsigned int Size=0;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr)++Size;

			for(;OutBegin!=OutEnd;++OutBegin){
				unsigned int Pos=hmLib::random::uniform_int(0,Size-1);
				Itr=Begin;
				for(unsigned int Cnt=0;Cnt<Pos;++Cnt)++Itr;
				*OutBegin=*Itr;
			}

			return OutBegin;
		}
		//�����_���I�� n��
		template<class InputIterator,class OutputIterator>
		OutputIterator random_sample(InputIterator Begin,InputIterator End,OutputIterator Out,unsigned int n){
			unsigned int Size=0;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr)++Size;

			for(unsigned int m=0;m!=n;++m){
				unsigned int Pos=hmLib::random::uniform_int(0,Size-1);
				Itr=Begin;
				for(unsigned int Cnt=0;Cnt<Pos;++Cnt)++Itr;
				*Out=*Itr;
				++Out;
			}

			return Out;
		}
		//���[���b�g�I��
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out){
			double TotalFitness=0.;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr){
				TotalFitness+=Value(*Itr);
			}

			double SelectFitnes=hmLib::random::uniform_real(0.,TotalFitness);
			for(Itr=Begin;Itr!=End;++Itr){
				SelectFitness-=Value(*Itr);
				if(SelectFitness<=0.)break;
			}
			*Out=*Itr;
			++Out;

			return Out;
		}
		//���[���b�g�I�� OutputIterator�͈̔͂𖄂߂�܂�
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator OutBegin,OutputIterator OutEnd){
			double TotalFitness=0.;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr){
				TotalFitness+=Value(*Itr);
			}

			for(;OutBegin!=OutEnd;++OutBegin){
				double SelectFitnes=hmLib::random::uniform_real(0.,TotalFitness);
				for(Itr=Begin;Itr!=End;++Itr){
					SelectFitness-=Value(*Itr);
					if(SelectFitness<=0.)break;
				}
				*OutBegin=*Itr;
				++OutBegin;
			}

			return OutBegin;
		}
		//���[���b�g�I�� n��
		template<class InputIterator,class FnRealValue,class OutputIterator>
		OutputIterator roulette_sample(InputIterator Begin,InputIterator End,FnRealValue Value,OutputIterator Out,unsigned int n){
			double TotalFitness=0.;
			InputIterator Itr;
			for(Itr=Begin;Itr!=End;++Itr){
				TotalFitness+=Value(*Itr);
			}

			for(unsigned int m=0;m!=n;++m){
				double SelectFitnes=hmLib::random::uniform_real(0.,TotalFitness);
				for(Itr=Begin;Itr!=End;++Itr){
					SelectFitness-=Value(*Itr);
					if(SelectFitness<=0.)break;
				}
				*Out=*Itr;
				++Out;
			}

			return Out;
		}
		//���[���b�g�I���N���X
		template<typename InputIterator>
		class roulette_sampler{
			struct assess_itr{
				InputIterator Itr;
				double Val;
			public:
				assess_itr(double Val_):Val(Val_){}
				assess_itr(InputIterator Itr_,double Val_):Itr(Itr_),Val(Val_){}
				bool operator<(const assess_itr& My_)const{return Val<My_.Val;}
			};
		private:
			std::vector<assess_itr> AssessVec;
		public:
			roulette_sampler(){}
			template<typename fnAssess>
			roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_){sync(Begin_,End_,FnAssess_);}
		public:
			InputIterator operator()(){
				return std::lower_bound(
					AssessVec.begin()
					,AssessVec.end()
					,assess_itr(hmLib::random::uniform_real(0.,assess())))->Itr;
			}
			double assess()const{return AssessVec.back().Val;}
			template<typename fnAssess>
			void sync(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_){
				double Val=0.;
				AssessVec.clear();
				while(Begin_!=End_){
					Val+=FnAssess_(*Begin_);
					AssessVec.push_back(assess_itr(Begin_++,Val));
				}
			}
		};
		//���[���b�g�I���N���X�̃r���_�[
		template<typename InputIterator,typename fnAssess>
		roulette_sampler<InputIterator> build_roulette_sampler(InputIterator Begin_,InputIterator End_,fnAssess FnAssess_){
			return roulette_sampler<InputIterator>(Begin_,End_,FnAssess_);
		}
	}
}
#
#endif
