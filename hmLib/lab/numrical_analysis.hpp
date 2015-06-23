#ifndef HMLIB_NUMERICALANALYSIS_INC
#define HMLIB_NUMERICALANALYSIS_INC 100
#
/*
���l��͂̎�@��񋟂��郉�C�u����
===numerical_analysis===
v1_00/131004 hmIto	
	small_step�@, �񕪖@��ǉ�
*/
#include<utility>
//#include<hmLib/parameter.hpp>
namespace hmLib{
	namespace numerical{
		template<typename dFn_d>
		double small_step_analysis(dFn_d Fn,double Begin_,double End_,double Step_){
			bool IsPositive=(Fn(Begin_)>0);

			while(IsPositive==Fn(Begin_+Step_)>0 && Begin_<End_){
				Begin_+=Step_;
			}

			return std::min(Begin_,End_);
		}
		template<typename dFn_d>
		std::pair<double,double> bisection_analysis(dFn_d Fn,double Begin_,double End_,double Error_){
			double Val=Fn(Begin_);

			if(Val==0.)return std::make_pair(Begin_,End_-Begin_);

			bool IsPositive=(Val>0);

			while(End_-Begin_>Error_){
				double Pos=(End_+Begin_)/2;

				Val=Fn(Pos);
				//�[���_���������ꍇ
				if(Val==0.){
					double CheckLow=Fn((Begin_+Pos)/2.);
					double CheckHgh=Fn((End_+Pos)/2.);

					//�Œ��ԓ_���[���ƂȂ��Ă��܂�Ȃ����m�F
					if(CheckHgh==0. || CheckLow==0.){
						if(CheckLow!=0.)Begin_=(Begin_+Pos)/2.;
						if(CheckHgh!=0.)End_=(Begin_+Pos)/2.;
						break;
					}
					Begin_=(Begin_+Pos)/2.;
					End_=(End_+Pos)/2.;
				}else if(Val>0==IsPositive){
					Begin_=Pos;
				}else{
					End_=Pos;
				}
			}

			return std::make_pair((End_+Begin_)/2.,End_-Begin_);
		}
	}
}
#
#endif
