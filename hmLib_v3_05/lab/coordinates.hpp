#ifndef HMLIB_COORDINATES_INC
#define HMLIB_COORDINATES_INC 101
#
/*===coordinate.hpp ===

���Ђ傤�ϊ����s���N���X

hmrBufGate:v1_01/130519 amby
	���Ђ傤�ϊ��N���X������
	�P���ȓ���`�F�b�N�ς�(���ʂ͐�������)
	�Ȃ��A�ϊ��Ƌt�ϊ��������̂��������ۂɁA���l�덷��e^{-10}���x�o�Ă��܂��B�{���͒P�ʍs��ɂȂ�͂������c

*/


#include<cmath>
#include<boost/operators.hpp>
namespace hmLib{
    namespace coordinates3D{
		struct transfer;
		struct polar;
		struct angle;
		struct position;
		struct scale;

		//��]�N���X
		struct angle
			:private boost::equality_comparable<angle>
			,private boost::addable<angle>
			,private boost::subtractable<angle>
			,private boost::multipliable<angle,double>
			,private boost::dividable<angle,double>
			,private boost::andable<angle>{
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
			//���ϊ����Z
			const angle& operator+=(const angle& Agl_){
				pitch+=Agl_.pitch;
				roll+=Agl_.roll;
				yaw+=Agl_.yaw;
				return *this;
			}
			//���ϊ����Z
			const angle& operator-=(const angle& Agl_){
				pitch-=Agl_.pitch;
				roll-=Agl_.roll;
				yaw-=Agl_.yaw;
				return *this;
			}
			//���ϊ��ώZ
			const angle& operator*=(const double& Val_){
				pitch*=Val_;
				roll*=Val_;
				yaw*=Val_;
				return *this;
			}
			//���ϊ��ώZ
			const angle& operator/=(const double& Val_){
				pitch/=Val_;
				roll/=Val_;
				yaw/=Val_;
				return *this;
			}
			//���ϊ������@�������͕�
            const angle& operator&=(const angle& Agl_);			
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
		struct position
			:private boost::equality_comparable<position>
			,private boost::addable<position>
			,private boost::subtractable<position>
			,private boost::multipliable<position,double>
			,private boost::dividable<position,double>
			,private boost::multipliable<position,angle>
			,private boost::multipliable<position,scale>{
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
			//���ϊ����Z
			const position& operator+=(const position& Agl_){
				x+=Agl_.x;
				y+=Agl_.y;
				z+=Agl_.z;
				return *this;
			}
			//���ϊ����Z
			const position& operator-=(const position& Agl_){
				x-=Agl_.x;
				y-=Agl_.y;
				z-=Agl_.z;
				return *this;
			}
			//���ϊ��ώZ
			const position& operator*=(const double& Val_){
				x*=Val_;
				y*=Val_;
				z*=Val_;
				return *this;
			}
			//���ϊ��ώZ
			const position& operator/=(const double& Val_){
				x/=Val_;
				y/=Val_;
				z/=Val_;
				return *this;
			}
			//���W�ϊ� �@�������͕�
            const position& operator*=(const angle& Agl_);
			//�X�P�[���ϊ�
			const position& operator*=(const scale& Scl_);
		public:
			double abs()const{return sqrt(x*x+y*y+z*z);}
		};	
		//�ɍ��W�x�N�g��
		struct polar
			:private boost::equality_comparable<polar>
			,private boost::addable<polar>
			,private boost::subtractable<polar>
			,private boost::multipliable<polar,double>
			,private boost::dividable<polar,double>{
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
			//���ϊ����Z
			const polar& operator+=(const polar& Pol_){
				r+=Pol_.r;
				phi+=Pol_.phi;
				theta+=Pol_.theta;
				return *this;
			}
			//���ϊ����Z
			const polar& operator-=(const polar& Pol_){
				r-=Pol_.r;
				phi-=Pol_.phi;
				theta-=Pol_.theta;
				return *this;
			}
			//���ϊ��ώZ
			const polar& operator*=(const double& Val_){
				r*=Val_;
				phi*=Val_;
				theta*=Val_;
				return *this;
			}
			//���ϊ��ώZ
			const polar& operator/=(const double& Val_){
				r/=Val_;
				phi/=Val_;
				theta/=Val_;
				return *this;
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
        inline angle coordinate_transfer(const position& pole_,const position& plane_){
            // ���ʂƂ��ē�����̂�,
            //  �V�������W�n�Ō����Ƃ��̂���_�̈ʒu(�x�N�g��)�� x_newcoordinate, �Â����W�n�Ō����Ƃ��̈ʒu���@x_oldcoordinate �Ƃ����Ƃ���
            //  x_newcoordinate = transfer(angle) * x_oldcoordinate �Ƃ����`�Ŋ֌W�Â����邱�Ƃɒ���

            // �R�R�ł̌v�Z�̕��j
            //  pole vector ��P�ʃx�N�g��e1(�V���W��x������)�ɂ��Cplene vector ����Ce1�ɒ��s����P�ʃx�N�g��e2(�V���W��y���ɑΉ�)�����D
            //  ����� z�������̃x�N�g��e3�����߁C�����̃x�N�g�����@�V���W��x,y,z�ɂ���悤�ȕϊ� T ���ȉ��̎��ŋ��߂�
            //    I = T * (e1 e2 e3)�@, �܂�C�@T^{-1} = (e1 e2 e3)
            //  ���ǁ@T�@�����߂�ׂ� transfer(angle) �ɑΉ�����̂ŁC���̊֌W����angle �����߂邱�Ƃ��ł���D

            // �P�ʃx�N�g���v�Z
            position e1 = pole_;
            e1 = e1 / sqrt( e1.x*e1.x + e1.y*e1.y + e1.z*e1.z );

            // plane_�@����@e2���v�Z
            position e2 = plane_;
            e2 = e2 - e1 * (e1.x*e2.x + e1.y*e2.y + e1.z*e2.z );
            e2 = e2 / sqrt( e2.x*e2.x + e2.y*e2.y + e2.z*e2.z );

            // �ȏォ�� e3 ���O�ςŌv�Z
            position e3;
            e3.x = e1.y*e2.z - e1.z*e2.y;
            e3.y = e1.z*e2.x - e1.x*e2.z;
            e3.z = e1.x*e2.y - e1.y*e2.x;

            // �����܂ł̌��ʂ���CT^{-1}�����܂�
            transfer trans;
            trans.x[0][0] = e1.x;
            trans.x[1][0] = e1.y;
            trans.x[2][0] = e1.z;
            trans.x[0][1] = e2.x;
            trans.x[1][1] = e2.y;
            trans.x[2][1] = e2.z;
            trans.x[0][2] = e3.x;
            trans.x[1][2] = e3.y;
            trans.x[2][2] = e3.z;

            // ���̕ϊ��s���roll pitch yaw �����߂�
            angle invAngle;
            position invPos;
            trans.getAngleAndPosition(invAngle, invPos);

            // �Ō�Ɍ��ʂ��t�ɂ���
            angle ans = ~invAngle;
            return ans;
        }
		//polor to osition
		inline position::position(const polar& Pol_){
			x=Pol_.r*sin(Pol_.theta)*cos(Pol_.phi);
			y=Pol_.r*sin(Pol_.theta)*sin(Pol_.phi);
			z=Pol_.r*cos(Pol_.theta);
		}
		//position to polor
		inline polar::polar(const position& Pos_){
			r=sqrt(Pos_.x*Pos_.x+Pos_.y*Pos_.y+Pos_.z*Pos_.z);
			theta=acos(Pos_.z/r);
			phi=atan2(Pos_.y, Pos_.x);
		}
		//���ϊ�����
        inline const angle& angle::operator&=(const angle& Agl_){
            transfer compositeTrans;
            // �������g�ŕϊ����Ă���C�ړI�̕ϊ��֐����|�����킹��
            compositeTrans = transfer(Agl_) * transfer(*this);
            // �p�x�ω����v�Z
            angle angle_;
            position pos_;
            compositeTrans.getAngleAndPosition(angle_, pos_);

            // ���
            roll = angle_.roll;
            pitch = angle_.pitch;
            yaw = angle_.yaw;

            return *this;
        }
		//�t���ϊ�
        inline const angle angle::operator~()const{
			//�t���ϊ��͌��ǁCR(roll�j R(pitch), R(yaw) �̕ϊ����t�ɂ�邱�ƂȂ̂ŁC
			// x_inertial =  R(roll) * R(pitch) * R(yaw) * x_robot
			// ������C
			// x_robot = R(-yaw) * R(-pitch) * R(-roll) * x_inertial
			// �Ƃ��āD���̕ϊ��s������߂邱�ƂƓ��l
			transfer invTrans;
			invTrans = transfer(angle(0., 0., -yaw)) * transfer(angle(0., -pitch, 0.)) * transfer(angle(-roll, 0., 0.));
			// �p�x�ω����v�Z
			angle angle_;
			position pos_;
			invTrans.getAngleAndPosition(angle_, pos_);

			// ���
			return angle_;
		}
		//���W�ϊ�
        inline const position& position::operator*=(const angle& Agl_){
			*this = transfer(Agl_) * (*this);
			return *this;
		}	
		//���W�ϊ�
        inline const position& position::operator*=(const scale& Scl_){
			*this = transfer(Scl_) * (*this);
			return *this;
		}
	}
}
namespace std{
	double abs(const hmLib::coordinates3D::position& pos){return pos.abs();}
	double abs(const hmLib::coordinates3D::polar& pol){return pol.abs();}
}
#
#endif
