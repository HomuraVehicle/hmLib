#ifndef HMLIB_ALGORITHM_SAMPLING_INC
#define HMLIB_ALGORITHM_SAMPLING_INC 102
/*
===algorithm::sampling===
����͈͂̒�����l��I������A���S���Y����񋟂���

algorithm::sampling:v1_02/130917 hmIto
	��O�����̃w�b�_���s�����Ă��������C��
algorithm::sampling:v1_01/130711 hmIto
	random_sampler�ǉ�
		�C�e���[�^�Ń����W���󂯎��A���̒�����operator()�Ń����_���ɕԂ�
algorithm::sampling:v1_00/130328 hmIto
	algorithm���番��
*/
#include<algorithm>
#ifndef HMLIB_RANDOM_INC
#	include<hmLib_v3_05/random.hpp>
#endif
#ifndef HMLIB_EXCEPTIONS_INC
#	include<hmLib_v3_05/exceptions.hpp>
#endif
namespace hmLib{
	namespace algorithm{
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
		//���[���b�g�I���N���X
		template<typename InputIterator>
		class random_sampler{
		private:
			InputIterator Begin;
			InputIterator End;
		public:
			random_sampler(){}
			random_sampler(InputIterator Begin_,InputIterator End_){sync(Begin_,End_);}
		public:
			InputIterator operator()(){
				return Begin+hmLib::random::uniform_int(0,End-Begin-1);
			}
			double assess()const{return AssessVec.back().Val;}
			void sync(InputIterator Begin_,InputIterator End_){
				Begin=Begin_;
				End=End_;
			}
		};
		//���[���b�g�I���N���X�̃r���_�[
		template<typename InputIterator>
		random_sampler<InputIterator> build_random_sampler(InputIterator Begin_,InputIterator End_){
			return random_sampler<InputIterator>(Begin_,End_);
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
			double assess()const{
				hmLib_assert(AssessVec.size(),hmLib::exceptions::invalid_request,"roulette_sampler have not been initialized yet.");
				return AssessVec.back().Val;
			}
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
