#ifndef HMLIB_DXLIB_DISPLAY_INC
#define HMLIB_DXLIB_DISPLAY_INC 100
#
#include<string>
#ifndef HMLIB_POSITION_INC
#	include<hmLib_v3_06/position.hpp>
#endif
namespace hmLib{
	namespace dxlib{
		class display{
		private:
			class cTask :public hm::cTask{
				friend class cDisplay;
			private:
				//�`���w��p�T�u�^�X�N
				class :public hm::cTask{
				private:
					int Handle;
				protected://hm::cTask
					//�^�X�N��������
					virtual bool construct(){
						// �`����ʂ𗠉�ʂɂ���
						SetDrawScreen(dx::cScreen::DefaultBackScreen.getHandle());

					}
				public:
					void setHandle(int Handle_){ Handle=Handle_; }
				};
			protected://hm::cTask
				//�^�X�N��������
				virtual bool construct(){
					//�E�B���h�E�A�C�R���ύX
					SetWindowIconID(1);

					return false;
				}
				//�^�X�N�ʏ폈��
				virtual bool task(){
					// ����ʂ̓��e��\��ʂɔ��f������
					ScreenFlip();
					//�������MainDisplay�֕ύX
					dx::cScreen::scoped_active TmpScr(dx::cScreen::DefaultBackScreen);
					//��ʕ`����e����
					ClearDrawScreen();

					return false;
				}
				//�^�X�N�I������
				virtual bool destruct(){ return false; }
			public:
				cTask() :hm::cTask(DX_DISPLAY_TASK){ return; }
			};
		private:
			pint Size;
			int ClrBit;
			bool IsWindowMode;
			bool IsWindowExtendMode;
			std::string Name;
		public:
			display(bool WindowMode_=false, const std::string& Name_="", pint DisplaySize_=pint(800, 600), int DisplayClrBit_=32)
				:Size(pint(800, 600))
				, ClrBit(32)
				, CanWindowExtend(false){

				dxlib::screen::DefaultBackScreen.getHandle();

				//�𑜓x��ύX����
				SetGraphMode(DisplaySize_.x, DisplaySize_.y, DisplayClrBit_);

				//�E�B���h�E���[�h
				ChangeWindowMode(IsWindowMode);

				//�E�B���h�E�T�C�Y�ύX�\���[�h
				SetWindowSizeChangeEnableFlag(IsWindowExtendMode);

				//�E�B���h�E����ύX
				SetMainWindowText(Name.c_str());

				//�E�B���h�E�A�C�R���ύX
				SetWindowIconID(1);

			}
			void setDisplay(pint Size_, int ClrBit_){
				if(Size==Size_ && ClrBit_==ClrBit)return;
				//�`���ʂ�ݒ�
				SetGraphMode(Size_.x, Size_.y, ClrBit_);
				Size=Size_;
				ClrBit=ClrBit_;
			}
			pint getDisplaySize()const{ return Size; }
			int getDisplayClrBit()const{ return ClrBit; }
			bool setName(const std::string& Name_){
				//�E�B���h�E����ύX
				SetMainWindowText(Name_.c_str());
				Name=Name_;
				return false;
			}
			std::string getName()const{ return Name; }
			void setWindowExtendMode(bool IsWindowExtendMode_){
				if(IsWindowExtendMode==IsWindowExtendMode_)return;
				SetWindowSizeChangeEnableFlag(IsWindowExtendMode_);
				IsWindowExtendMode=IsWindowExtendMode_;
			}
			bool getWindowExtendMode()const{ return IsWindowExtendMode; }
			void setWindowMode(bool IsWindowMode_){
				if(IsWindowMode==IsWindowMode_)return;
				ChangeWindowMode(static_cast<int>(IsWindowMode_));
				IsWindowMode=IsWindowMode_;
			}
			bool getWindowMode()const{ return IsWindowMode; }
		};
		extern  cDisplay Display;
	}
}
#
#endif
