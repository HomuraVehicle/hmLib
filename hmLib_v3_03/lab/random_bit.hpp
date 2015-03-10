#ifndef HMLIB_RANDOMBIT_INC
#define HMLIB_RANDOMBIT_INC 100
#
/*===random_bit===
bit�P�ʂŗ�����񋟂���

random_bit:v1_00/130321 hmIto
	bit�P�ʂł̗����ێ��@�\�Arandom_bit��ǉ�
	random::uniform_bool�֐���ǉ�
*/
#ifndef HMLIB_RANDOM_INC
#	include"random.hpp"
#endif
namespace hmLib{
	class random_bit{
		unsigned int val;
		unsigned char pos;
	private:
		random_bit(const random_bit& My_);
		random_bit& operator=(const random_bit& My_);
	public:
		random_bit():val(0),pos(0){}
		random_bit(random_bit&& My_):val(My_.val),pos(My_.pos){}
		random_bit& operator=(random_bit&& My_){
			val=My_.val;
			pos=My_.pos;
			return *this;
		}
		template<typename random_engine_>
		bool operator()(random_engine_ Engine_){
			if(pos==0){
				val= std::uniform_int_distribution<int>(INT_MIN,INT_MAX)(Engine_);
				pos=32;
			}

			bool ans=((val&1)!=0);
			val>>=1;
			--pos;

			return ans;
		}
		bool operator()(void){return (*this)(random::Engine);}
	};
	namespace random{
		extern random_bit RandomBit;
		inline bool uniform_bool(){return RandomBit();}
	}
}
#
#endif
