#ifndef HMLIB_COORDINATES_INC
#define HMLIB_COORDINATES_INC 103
#
/*===coordinate.hpp ===

���Ђ傤�ϊ����s���N���X

=== coodinates ===
v1_03/150227 hmIto
	polor�𐔒l�{�����ۂɊp�x�܂ŐώZ���Ă��܂��Ă��������C��
v1_02/141203 hmIto
	boost::operators�Ɉˑ����Ȃ��`�ɕύX
v1_01/130519 amby
	���Ђ傤�ϊ��N���X������
	�P���ȓ���`�F�b�N�ς�(���ʂ͐�������)
	�Ȃ��A�ϊ��Ƌt�ϊ��������̂��������ۂɁA���l�덷��e^{-10}���x�o�Ă��܂��B�{���͒P�ʍs��ɂȂ�͂������c

*/
#ifndef HMLIB_CONFIG_INC
#	include "hmLib_config.h"
#endif
#if !(defined(HMLIB_NOLIB) || defined(HMLIB_COORDINATES_NOLIB))
#	ifdef _DEBUG
#		pragma comment(lib,"hmLib_v3_06/lib/Debug/coordinates.lib")
#	else
#		pragma comment(lib,"hmLib_v3_06/lib/Release/coordinates.lib")
#	endif
#endif
#include<cmath>
namespace hmLib{
	namespace coordinates3D{
		struct transfer;
		struct polar;
		struct angle;
		struct position;
		struct scale;

		//��]�N���X
		struct angle{
		public:
			double roll; //
			double pitch; // -PI/2 < pitch < PI/2
			double yaw;   //
		public:
			angle():pitch(0.),roll(0.),yaw(0.){}
			angle(const angle& Agl_):pitch(Agl_.pitch),roll(Agl_.roll),yaw(Agl_.yaw){}
			angle(angle&& Agl_):pitch(Agl_.pitch),roll(Agl_.roll),yaw(Agl_.yaw){}
			angle(double roll_,double pitch_,double yaw_):roll(roll_),pitch(pitch_),yaw(yaw_){}
		public:
			//�������Z
			bool operator==(const angle& Agl_)const{
				return pitch==Agl_.pitch && roll==Agl_.roll && yaw==Agl_.yaw;
			}
			bool operator!=(const angle& Agl_)const {
				return !(*this==Agl_);
			}
			//���ϊ����Z
			const angle& operator+=(const angle& Agl_){
				pitch+=Agl_.pitch;
				roll+=Agl_.roll;
				yaw+=Agl_.yaw;
				return *this;
			}
			friend angle operator+(const angle& Agl1_, const angle& Agl2_) {
				angle Src(Agl1_);
				return Src+=Agl2_;
			}
			//���ϊ����Z
			const angle& operator-=(const angle& Agl_){
				pitch-=Agl_.pitch;
				roll-=Agl_.roll;
				yaw-=Agl_.yaw;
				return *this;
			}
			friend angle operator-(const angle& Agl1_, const angle& Agl2_) {
				angle Src(Agl1_);
				return Src-=Agl2_;
			}
			//���ϊ��ώZ
			const angle& operator*=(const double& Val_){
				pitch*=Val_;
				roll*=Val_;
				yaw*=Val_;
				return *this;
			}
			friend angle operator*(const angle& Agl_, const double& Val_) {
				angle Src(Agl_);
				return Src*=Val_;
			}
			//���ϊ��ώZ
			const angle& operator/=(const double& Val_){
				pitch/=Val_;
				roll/=Val_;
				yaw/=Val_;
				return *this;
			}
			friend angle operator/(const angle& Agl_, const double& Val_) {
				angle Src(Agl_);
				return Src/=Val_;
			}
			//���ϊ������@�������͕�
			const angle& operator&=(const angle& Agl_);			
			friend angle operator&(const angle& Agl1_, const angle& Agl2_) {
				angle Src(Agl1_);
				return Src&=Agl2_;
			}
			//�t���ϊ��@�@�������͕�
			const angle operator~()const;
		};
		//�g��N���X
		struct scale{
		public:
			double rx;
			double ry;
			double rz;
		public:
			scale():rx(1.),ry(1.),rz(1.){}
			scale(double rx_,double ry_,double rz_):rx(rx_),ry(ry_),rz(rz_){}
			//�t���ϊ��@�@�������͕�
			const scale operator~()const{return scale(1/rx,1/ry,1/rz);}
		};
		//�������W�x�N�g��
		struct position{
			double x;
			double y;
			double z;
		public:
			position():x(0.),y(0.),z(0.){}
			position(const position& Pos_):x(Pos_.x),y(Pos_.y),z(Pos_.z){}
			position(position&& Pos_):x(Pos_.x),y(Pos_.y),z(Pos_.z){}
			position(double x_,double y_,double z_):x(x_),y(y_),z(z_){}
			position(const polar& Pol_);
		public:
			//�������Z
			bool operator==(const position& Agl_)const{
				return x==Agl_.x && y==Agl_.y && z==Agl_.z;
			}
			bool operator!=(const position& Agl_)const {
				return !(*this==Agl_);
			}
			//���ϊ����Z
			const position& operator+=(const position& Agl_){
				x+=Agl_.x;
				y+=Agl_.y;
				z+=Agl_.z;
				return *this;
			}
			friend position operator+(const position& Agl1_, const position& Agl2_) {
				position Src(Agl1_);
				return Src+=Agl2_;
			}
			//���ϊ����Z
			const position& operator-=(const position& Agl_){
				x-=Agl_.x;
				y-=Agl_.y;
				z-=Agl_.z;
				return *this;
			}
			friend position operator-(const position& Agl1_, const position& Agl2_) {
				position Src(Agl1_);
				return Src-=Agl2_;
			}
			//���ϊ��ώZ
			const position& operator*=(const double& Val_){
				x*=Val_;
				y*=Val_;
				z*=Val_;
				return *this;
			}
			friend position operator*(const position& Agl_,const double& Val_) {
				position Src(Agl_);
				return Src*=Val_;
			}
			//���ϊ��ώZ
			const position& operator/=(const double& Val_){
				x/=Val_;
				y/=Val_;
				z/=Val_;
				return *this;
			}
			friend position operator/(const position& Agl_,const double& Val_) {
				position Src(Agl_);
				return Src/=Val_;
			}
			//���W�ϊ� �@�������͕�
			const position& operator*=(const angle& Agl_);
			friend position operator*(const position& Pos_, const angle& Agl_) {
				position Src(Pos_);
				return Src*=Agl_;
			}
			//�X�P�[���ϊ�
			const position& operator*=(const scale& Scl_);
			friend position operator*(const position& Pos_, const scale& Scl_) {
				position Src(Pos_);
				return Src*=Scl_;
			}
		public:
			double abs()const{return sqrt(x*x+y*y+z*z);}
		};	
		//�ɍ��W�x�N�g��
		struct polar{
		public:
			double r;
			double phi;		//x������̊p�x�y�E��n��]�����@���z
			double theta;	//z������̊p�x �iz�����炘��������)
		public:
			polar():r(0.),phi(0.),theta(0.){}
			polar(const polar& Pol_):r(Pol_.r),phi(Pol_.phi),theta(Pol_.theta){}
			polar(polar&& Pol_):r(Pol_.r),phi(Pol_.phi),theta(Pol_.theta){}
			polar(double r_,double phi_,double theta_):r(r_),phi(phi_),theta(theta_){}
			polar(const position& Pos_);
		public:
			//�������Z
			bool operator==(const polar& Pol_)const{
				if(r==0 && Pol_.r==0)return true;

				if(r!=Pol_.r)return false;

				double pi=acos(-1);

				double rphi=phi-Pol_.phi;
				while(rphi<0)rphi+=2*pi;
				while(rphi>=2*pi)rphi-=2*pi;
				if(rphi!=0.)return false;

				double rtheta=theta-Pol_.theta;
				while(rtheta<0)rtheta+=2*pi;
				while(rtheta>=2*pi)rtheta-=2*pi;
				if(rtheta!=0.)return false;

				return true;
			}
			bool operator!=(const polar& Pol_)const {
				return !(*this==Pol_);
			}
			//���ϊ����Z
			const polar& operator+=(const polar& Pol_){
				r+=Pol_.r;
				phi+=Pol_.phi;
				theta+=Pol_.theta;
				return *this;
			}
			friend polar operator+(const polar& Pol1_, const polar& Pol2_) {
				polar Src(Pol1_);
				return Src+=Pol2_;
			}
			//���ϊ����Z
			const polar& operator-=(const polar& Pol_){
				r-=Pol_.r;
				phi-=Pol_.phi;
				theta-=Pol_.theta;
				return *this;
			}
			friend polar operator-(const polar& Pol1_, const polar& Pol2_) {
				polar Src(Pol1_);
				return Src-=Pol2_;
			}
			//���ϊ��ώZ
			const polar& operator*=(const double& Val_){
				r*=Val_;
				return *this;
			}
			friend polar operator*(const polar& Pol_, const double& Val_) {
				polar Src(Pol_);
				return Src*=Val_;
			}
			//���ϊ��ώZ
			const polar& operator/=(const double& Val_){
				r/=Val_;
				return *this;
			}
			friend polar operator/(const polar& Pol_, const double& Val_) {
				polar Src(Pol_);
				return Src/=Val_;
			}
		public:
			double abs()const{return r;}
		};
		//���W�ϊ��s��
		struct transfer{
		public:
			double x[4][4];
		public:
			//�P�ʍs��
			transfer(){
				for(unsigned int r=0;r<4;++r){
					for(unsigned int c=0;c<4;++c){
						x[r][c]=(r==c?1:0);
					}
				}
			}
			//��]
			// ����́@roll pitch yaw �ł���킳���@���{�b�g���W�n���C�������W�n�ɖ߂��s��
			// x_{inertial frame} = Matrix * x_{robot frame}
			transfer(const angle& Agl_){
				x[0][0] = cos(Agl_.pitch) * cos(Agl_.yaw);
				x[0][1] = - cos(Agl_.pitch) * sin(Agl_.yaw);
				x[0][2] = sin(Agl_.pitch);
				x[0][3] = 0.;

				x[1][0] = sin(Agl_.roll) * sin(Agl_.pitch) * cos(Agl_.yaw) + cos(Agl_.roll) * sin(Agl_.yaw);
				x[1][1] = - sin(Agl_.roll) * sin(Agl_.pitch) * sin(Agl_.yaw) + cos(Agl_.roll) * cos(Agl_.yaw);
				x[1][2] = - sin(Agl_.roll) * cos(Agl_.pitch);
				x[1][3] = 0.;

				x[2][0] = - cos(Agl_.roll) * sin(Agl_.pitch) * cos(Agl_.yaw) + sin(Agl_.roll) * sin(Agl_.yaw);
				x[2][1] = cos(Agl_.roll) * sin(Agl_.pitch) * sin(Agl_.yaw) + sin(Agl_.roll) * cos(Agl_.yaw);
				x[2][2] = cos(Agl_.roll) * cos(Agl_.pitch);
				x[2][3] = 0.;

				x[3][0] = 0.;
				x[3][1] = 0.;
				x[3][2] = 0.;
				x[3][3] = 1.;
			}
			//�g��
			transfer(const scale& Scl_){
				for(int i = 0;i<4;++i){
					for(int j = 0;j<4;++j){
						x[i][j] = (i==j?1.:0.);
					}
				}
				x[0][0] = Scl_.rx;
				x[1][1] = Scl_.ry;
				x[2][2] = Scl_.rz;
			}
			//�ړ�
			// Pos_ �Ŏw�肳�������Ɉړ����ꂽ���W�n�̍��W���C�������W�n�ɖ߂��s��
			//  x_{inertial frame} = Matrix * x_{robot frame}
			transfer(const position& Pos_){
				for(int i = 0;i<4;++i){
					for(int j = 0;j<4;++j){
						x[i][j] = (i==j?1.:0.);
					}
				}
				x[0][3] = Pos_.x;
				x[1][3] = Pos_.y;
				x[2][3] = Pos_.z;
			}
		public:
			// �ϊ��s�񂩂�C�ϊ��p�x�C���s�ړ����������߂�
			void getAngleAndPosition(angle& angle_, position& pos_){
				// position �v�Z
				pos_.x = x[0][3];
				pos_.y = x[1][3];
				pos_.z = x[2][3];

				// angle �v�Z
				double cos_pitch = fabs(sqrt(x[0][0]*x[0][0] +  x[0][1]*x[0][1]));

				if( cos_pitch > 0.001 )
				//  pitch�p�@���@+-90�x�łȂ��ꍇ
				{
					angle_.pitch = atan2(x[0][2], cos_pitch);
					angle_.roll = atan2(-x[1][2], x[2][2]);
					angle_.yaw = atan2(-x[0][1], x[0][0]);
				}else
				// pitch �p��+- 90�x�̏ꍇ�͑S�Ă̊p����ӂɌ��߂邱�Ƃ��ł��Ȃ��̂ŁCyaw�p��0�ɂ���
				{
					angle_.pitch = atan2(x[0][2], 0.);
					angle_.roll = atan2(x[2][1], x[1][1]);
					angle_.yaw = 0.;
				}
				return;
			}
		public:
			//�@�s�񉉎Z�I�y���[�^
			// �ϊ��s�񓯎m�̐�
			transfer operator*(const transfer& Val_){
				transfer ans;
				for(int i=0;i<4;++i){
					for(int j=0;j<4;++j){
						double value = 0.;
						for(int k=0;k<4;++k){
							value += x[i][k] * Val_.x[k][j];
						}
						ans.x[i][j] = value;
					}
				}
				return ans;
			}
			// �ϊ��s�񓯎m�̊���Z�i�t�s��j �ۗ�
			transfer operator/(const transfer& Val_);
			// ���W�Ƃ̐�
			position operator*(const position& Pos_){
				position ans;
				double ansVec[4] = {0.};
				double derVec[4];
				derVec[0] = Pos_.x;
				derVec[1] = Pos_.y;
				derVec[2] = Pos_.z;
				derVec[3] = 1;

				for(int i = 0;i<4;++i){
					for(int j=0;j<4;++j){
						ansVec[i] += x[i][j] * derVec[j];
					}
				}
				ans.x = ansVec[0];
				ans.y = ansVec[1];
				ans.z = ansVec[2];

				return ans;
			}
		};		
		//���ϊ��̍쐬 pole��x���Aplane��pole��xy����
		angle coordinate_transfer(const position& pole_, const position& plane_);
	}
}
namespace std{
	double abs(const hmLib::coordinates3D::position& pos){return pos.abs();}
	double abs(const hmLib::coordinates3D::polar& pol){return pol.abs();}
}
#
#endif
