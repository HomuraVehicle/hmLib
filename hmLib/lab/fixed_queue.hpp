#ifndef HMLIB_FIXEDQUEUE_INC
#define HMLIB_FIXEDQUEUE_INC 100
/*=== fixed_deque ===
�Œ蒷�̊ȈՔz��

=== fixed_deque ===
v1_00/140329 hmIto
�쐬
*/
#ifndef HMLIB_FIXEDDEQUE_INC
#	include <hmLib/lab/fixed_deque.hpp>
#endif
namespace hmLib {
	template<typename T>
	class fixed_queue {
		typedef fixed_queue<T> my_type;
		typedef fixed_deque<T> base_type;
	public:
		typedef base_type::destructor destructor;
	private:
		static void default_destructor(T* Ptr) { delete[] Ptr; }
	public:
		typedef base_type::iterator iterator;
		typedef base_type::const_iterator const_iterator;
	private:
		base_type Base;
	public:
		//�R���X�g���N�^
		fixed_queue() :Base() {
		}
		fixed_queue(unsigned int Size_)
			:Base(Size){
		}
		fixed_queue(T* BufBegin_, T* BufEnd_, destructor Destructor_)
			:Base(BufBegin_,BufEnd_,Destructor_) {
		}
		~fixed_queue() {
		}
	private:
		//�R�s�[�֎~
		fixed_queue(const my_type& My_);
		const my_type& operator=(const my_type& My_);
	public:
		//�o�b�t�@���Ċm��
		void reset(unsigned int Size_) {
			Base.reset(Size_);
		}
		void reset(T* BufBegin_, T* BufEnd_, destructor Destructor_) {
			Base.reset(BufBegin_, BufEnd_, Destructor_);
		}
		//�o�b�t�@����
		bool empty()const { return Base.empty(); }
		//�o�b�t�@�������ς���
		bool full()const { return Base.full(); }
		//�o�b�t�@�T�C�Y
		unsigned int size()const {return Base.size();}
		//�ő�T�C�Y
		unsigned int maxsize()const { return Base.maxsize(); }
		//�o�b�t�@�̊m�ۂ̗L��
		operator bool()const { return static_cast<bool>(Base); }
		//�X���b�v
		void swap(my_type& My_) {Base.swap(My_.Base);}
		//�N���A
		void clear() {Base.clear();}
	public:
		void pop() { Base.pop_front(); }
		void push(const T& val_) { Base.push_back(val_); }
	public:
		//�擪�A�h���X���擾
		T* data() { return Base.data(); }
		//�擪�̃f�[�^���擾
		T& next() {return Base.front();}
		const T& next()const { return Base.front(); }
		//�C�e���[�^���擾
		iterator begin() { return Base.begin(); }
		iterator end() { return Base.end(); }
		const_iterator begin()const { return Base.begin(); }
		const_iterator end()const { return Base.end(); }
	};
}
#
#endif
