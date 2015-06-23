#ifndef HMLIB_COORDINATES_CPP_INC
#define HMLIB_COORDINATES_CPP_INC 100
#
/*===coordinate.cpp ===

���Ђ傤�ϊ����s���N���X

hmrBufGate:v1_01/130519 amby
	���Ђ傤�ϊ��N���X������
	�P���ȓ���`�F�b�N�ς�(���ʂ͐�������)
	�Ȃ��A�ϊ��Ƌt�ϊ��������̂��������ۂɁA���l�덷��e^{-10}���x�o�Ă��܂��B�{���͒P�ʍs��ɂȂ�͂������c

*/


#include <hmLib/coordinates.hpp>

namespace hmLib{
    namespace coordinates3D{        
		// �֐��̎�������
		angle coordinate_transfer(const position& pole_,const position& plane_){
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
		position::position(const polar& Pol_){
			x=Pol_.r*sin(Pol_.theta)*cos(Pol_.phi);
			y=Pol_.r*sin(Pol_.theta)*sin(Pol_.phi);
			z=Pol_.r*cos(Pol_.theta);
		}
		polar::polar(const position& Pos_){
			r=sqrt(Pos_.x*Pos_.x+Pos_.y*Pos_.y+Pos_.z*Pos_.z);
			theta=acos(Pos_.z/r);
			phi=atan2(Pos_.y, Pos_.x);
		}

		//���ϊ�����
        const angle& angle::operator&=(const angle& Agl_){
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
        const angle angle::operator~()const{
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
		const position& position::operator*=(const angle& Agl_){
			*this = transfer(Agl_) * (*this);
			return *this;
		}
		//���W�ϊ�
		const position& position::operator*=(const scale& Scl_) {
			*this = transfer(Scl_) * (*this);
			return *this;
		}
	}
}
#
#endif
