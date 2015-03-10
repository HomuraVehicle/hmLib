#ifndef HMLIB_RANDOM_RANDOMENGINE_INC
#define HMLIB_RANDOM_RANDOMENGINE_INC 100
#
/*
===random_engine===
C++11�̗������C�u���������b�s���O���Ē�

random_engine v1_00/130328 hmIto
	random���番��
*/
#include<algorithm>
#include<functional>
#include<vector>
#include<random>
#include<numeric>
#
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#ifndef HMLIB_NOLIB
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_05/lib/Debug/random_engine.lib")
#	else
#		pragma comment(lib,"hmLib_v3_05/lib/Release/random_engine.lib")
#	endif
#endif

namespace hmLib{
	template<class random_engine_type = std::mt19937_64>
	class random_engine:public random_engine_type{
	public:
		random_engine(){
			// �����_���f�o�C�X
			std::random_device rnd ;

			// �������p�x�N�^
			std::vector< unsigned int> v(10) ;

			// �x�N�^�̏�����
			std::generate( v.begin(), v.end(), std::ref(rnd) ) ;

			//�V�[�h�ŏ�����
			seed(std::seed_seq( v.begin(), v.end() ));
		}
		template<class InputIterator>
		random_engine(InputIterator Begin,InputIterator End){
			seed(std::seed_seq(Begin,End));
		}
		int uniform_int(int Min,int Max){return std::uniform_int_distribution<int>(Min,Max)(*this);}
		double uniform_real(double Min=0.0,double Max=1.0){return std::uniform_real_distribution<double>(Min,Max)(*this);}
		double normal(double meen,double sigma){return std::normal_distribution<double>(meen,sigma)(*this);}
	};
	namespace random{
		extern random_engine<> Engine;
		inline int uniform_int(int Min,int Max){return Engine.uniform_int(Min,Max);}
		inline double uniform_real(double Min=0.0,double Max=1.0){return Engine.uniform_real(Min,Max);}
		inline double normal(double meen,double sigma){return Engine.normal(meen,sigma);}
	}
}
#
#endif
