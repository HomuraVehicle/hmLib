#ifndef HMLIB_MEMORY_CLONECOUNTER_INC
#define HMLIB_MEMORY_CLONECOUNTER_INC 100
#
#include<memory>
namespace hmLib {
	namespace {
		class _clone_counter_base {
		private:
			unsigned int CloneCnt;
			unsigned int ObserverCnt;
		public:
			_clone_counter_base() :CloneCnt(1), ObserverCnt(0) {}
			void attachCounter() { ++CloneCnt; }
			void detachCounter() { --CloneCnt; }
			void attachObserver() { ++ObserverCnt; }
			void detachObserver() { --ObserverCnt; }
			operator bool()const { return CloneCnt+ObserverCnt>0; }
			unsigned int counter() { return CloneCnt; }
		};
	}
	class clone_observer;
	class clone_counter {
		friend class clone_observer;
	private:
		_clone_counter_base* p;
	public:
		clone_counter() :p(nullptr) {}
		clone_counter(const clone_counter& Cnt_) :p(nullptr) {
			//���肪nullptr�������ꍇ�́A�܂��J�E���^����
			if(Cnt_.p==nullptr) {
				const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
			}
			//�A�^�b�`
			p=Cnt_.p;
			p->attachCounter();
		}
		const clone_counter& operator=(const clone_counter& Cnt_) {
			//�Q�Ɛ悪�������g�łȂ��ꍇ
			if(p != Cnt_.p) {
				//���g�̕ێ��J�E���^���f�^�b�`
				if(p!=nullptr) {
					p->detachCounter();
					if(p==false)delete p;
					p=nullptr;
				}
				//���肪nullptr�������ꍇ�́A�܂��J�E���^����
				if(Cnt_.p==nullptr) {
					const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
				}
				//�A�^�b�`
				p=Cnt_.p;
				p->attachCounter();

			}//���J�E���^�Ƃ���nullptr�������ꍇ
			else if(Cnt_.p==nullptr) {
				//�܂��J�E���^����
				const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
				//�A�^�b�`
				p=Cnt_.p;
				p->attachCounter();
			}

			return *this;
		}
		clone_counter(clone_counter&& Cnt_) :p(nullptr) {
			//���̕ύX�͂Ȃ��̂ŁA�P�ɃX���b�v
			std::swap(p, const_cast<clone_counter&>(Cnt_).p);
		}
		const clone_counter& operator=(clone_counter&& Cnt_) {
			//�Q�Ɛ悪�������g�łȂ��ꍇ
			if(p != Cnt_.p) {
				//���g�̕ێ��J�E���^���f�^�b�`
				if(p!=nullptr) {
					p->detachCounter();
					if(p==false)delete p;
					p=nullptr;
				}
				//���̕ύX�͂Ȃ��̂ŁA�P�ɃX���b�v
				std::swap(p, const_cast<clone_counter&>(Cnt_).p);
			}

			return *this;
		}
		~clone_counter() {
			//���L�J�E���^������ꍇ�A�f�^�b�`
			if(p!=nullptr) {
				p->detachCounter();
				if(p==false)delete p;
			}
		}
		unsigned int count() const {
			if(p==nullptr)return 1;
			return p->counter();
		}		
		operator unsigned int()const {
			return count();
		}
		void reset() {
			//���g�̕ێ��J�E���^���f�^�b�`
			if(p!=nullptr) {
				p->detachCounter();
				if(p==false)delete p;
				p=nullptr;
			}
		}
		bool operator==(const clone_observer& My2_)const;
		bool operator==(const clone_counter& My2_)const {
			return p!=nullptr && p==My2_.p;
		}
	};
	class clone_observer {
		friend class clone_counter;
	private:
		_clone_counter_base* p;
	public:
		clone_observer(const clone_counter& Cnt_) :p(nullptr) {
			//���肪nullptr�������ꍇ�́A�܂��J�E���^����
			if(Cnt_.p==nullptr) {
				const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
			}
			//�A�^�b�`
			p=Cnt_.p;
			p->attachObserver();
		}
		const clone_observer& operator=(const clone_counter& Cnt_) {
			//�Q�Ɛ悪�������g�łȂ��ꍇ
			if(p != Cnt_.p) {
				//���g�̕ێ��J�E���^���f�^�b�`
				if(p!=nullptr) {
					p->detachObserver();
					if(p==false)delete p;
					p=nullptr;
				}
				//���肪nullptr�������ꍇ�́A�܂��J�E���^����
				if(Cnt_.p==nullptr) {
					const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
				}
				//�A�^�b�`
				p=Cnt_.p;
				p->attachObserver();

			}//���J�E���^�Ƃ���nullptr�������ꍇ
			else if(Cnt_.p==nullptr) {
				//�܂��J�E���^����
				const_cast<clone_counter&>(Cnt_).p = new _clone_counter_base();
				//�A�^�b�`
				p=Cnt_.p;
				p->attachObserver();
			}

			return *this;
		}
		~clone_observer() {
			//���L�J�E���^������ꍇ�A�f�^�b�`
			if(p!=nullptr) {
				p->detachObserver();
				if(p==false)delete p;
			}
		}
		unsigned int count() const {
			if(p==nullptr)return 0;
			return p->counter();
		}
		operator unsigned int()const {
			return count();
		}
		void reset() {
			//���g�̕ێ��J�E���^���f�^�b�`
			if(p!=nullptr) {
				p->detachObserver();
				if(p==false)delete p;
				p=nullptr;
			}
		}
		bool operator==(const clone_counter& My2_)const;
		bool operator==(const clone_observer& My2_) const{
			return p!=nullptr && p==My2_.p;
		}
	};
	inline bool clone_counter::operator==(const clone_observer& My2_) const {
		return p!=nullptr && p==My2_.p;
	}
	inline bool clone_observer::operator==(const clone_counter& My2_) const {
		return p!=nullptr && p==My2_.p;
	}
}
#
#endif
