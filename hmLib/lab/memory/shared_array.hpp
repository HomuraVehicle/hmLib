#ifndef HMLIB_MEMORY_SHAREDARRAY_INC
#define HMLIB_MEMORY_SHAREDARRAY_INC 104
#
/*
=== memory::shared_array ===
v1_04/140719 hmIto
	iterator��ǉ�
v1_03/140415 hmIto
	unique_ptr��include�Y����C��
v1_02/140412 hmIto
	_shared_array_element�𖳖����O��Ԃֈړ�
	allocator��rebind��p�����������L�ڂ֕ύX
v1_01/140408 hmIto
	shared_write_array��write�֐���ǉ�
	flush�𓯎��Ɏ����ł���Ă����
	�߂�l�ɏ������ݍς݂̃T�C�Y���A���Ă���
	shared_read_array��pointer��unique_ptr���璼�ڍ\�z�ł���悤�ɃR���X�g���N�^,reset�֐���ǉ�
	�����ł́Ashared_write_array���ꎞ�I�ɍ쐬���Ă���󂯎���Ă���
	shared_read_array��flowing��ǉ�
	�������ݏI�����Ă��邩�̊m�F�B�Y��Ă��B]
	���̑��A�S�̓I�ɃR�����g�ǉ�
*/
#include<memory>
#include<hmLib/lab/rvalue_reference.hpp>
#include"unique_ptr.hpp"
#include"default_deleter.hpp"
namespace hmLib {
	namespace {
		template<typename T, typename D>
		struct _shared_array_element {
		public:
			typedef T* pointer;
			typedef D deleter;
			typedef _shared_array_element<T, D> my_type;
			typedef rvalue_reference<my_type> rvalue_reference;
		private:
			pointer ptr;
			deleter dlt;
			unsigned int rcnt;
			unsigned int wcnt;
			unsigned int rsize;
			unsigned int wsize;
		public:
			_shared_array_element(pointer ptr_, unsigned int size_, deleter dlt_)
				: ptr(ptr_)
				, dlt(dlt_)
				, rcnt(0)
				, wcnt(0)
				, rsize(0)
				, wsize(0) {
				if(ptr) {
					wsize=size_;
					++wcnt;
				}
			}
			_shared_array_element(rvalue_reference ref_)
				: ptr(ref_.ref.ptr)
				, dlt(ref_.ref.dlt)
				, rcnt(ref_.ref.rcnt)
				, wcnt(ref_.ref.wcnt)
				, rsize(ref_.ref.rsize)
				, wsize(ref_.ref.wsize) {
				ref_.ref.ptr=0;
				ref_.ref.rcnt=0;
				ref_.ref.wcnt=0;
				ref_.ref.rsize=0;
				ref_.ref.wsize=0;
			}
			const _shared_array_element& operator=(rvalue_reference ref_) {
				if(ptr)dlt(ptr);
				prt=ref_.ref.ptr;
				dlt=ref_.ref.dlt;
				cnt=ref_.ref.cnt;
				ref_.ref.ptr=0;
				ref_.ref.rcnt=0;
				ref_.ref.wcnt=0;
				ref_.ref.rsize=0;
				ref_.ref.wsize=0;
			}
			~_shared_array_element() {
				if(ptr)dlt(ptr);
			}
			my_type* read_attach() {
				++rcnt;
				return this;
			}
			bool read_detach() {
				if(rcnt>0)--rcnt;
				return ptr!=0 && rcnt==0 && wcnt==0;
			}
			my_type* write_attach() {
				++wcnt;
				return this;
			}
			bool write_detach() {
				if(wcnt>0)--wcnt;
				if(wcnt==0)rsize=wsize;
				return ptr!=0 && rcnt==0 && wcnt==0;
			}
			pointer get() { return ptr; }
			const pointer get()const { return ptr; }
			deleter get_deleter()const { return dlt; }
			unsigned int get_read_count()const {
				return rcnt;
			}
			unsigned int get_write_count()const {
				return wcnt;
			}
			operator bool()const { ptr!=0; }
			unsigned int get_rsize()const {
				return rsize;
			}
			unsigned int get_wsize()const {
				return wsize;
			}
			bool resize(unsigned int size_) {
				if(rsize>size_ || wsize<size_)return true;
				wsize=size_;
				return false;
			}
			bool resize() {
				wsize=rsize;
				return false;
			}
			void flush() { rsize=wsize; }
			void flush(unsigned int pos_) {
				if(wsize>pos_)rsize=pos_+1;
				else rsize=wsize;
			}
			bool flowing()const { return rsize==wsize; }
		public:
			_shared_array_element()
				: ptr(0)
				, dlt()
				, rcnt(0)
				, wcnt(0)
				, rsize(0)
				, wsize(0){
			}
			_shared_array_element(const _shared_array_element& my_)
				: ptr(my_.ptr)
				, dlt(my_.dlt)
				, rcnt(my_.rcnt)
				, wcnt(my_.wcnt)
				, rsize(my_.rsize)
				, wsize(my_.wsize){
			}
			const _shared_array_element& operator=(const _shared_array_element& my_) {
				if(this!=&my_) {
					ptr=my_.ptr;
					dlt=my_.dlt;
					rcnt=my_.rcnt;
					wcnt=my_.wcnt;
					rsize=my_.rsize;
					wsize=my_.wsize;
				}
				return *this;
			}
		};
	}
	template<typename T, typename D=default_deleter<T>, typename Alloc=std::allocator<T> >
	class shared_read_array;

	//�������ݑ��̔z��Ǘ��N���X
	template<typename T, typename D=default_deleter<T>, typename Alloc=std::allocator<T> >
	class shared_write_array {
		typedef shared_read_array<T, D, Alloc> read_type;
		friend class read_type;
	private:
		typedef shared_write_array<T, D, Alloc> my_type;
		typedef _shared_array_element<T, D> my_array_element;
		typedef rvalue_reference<my_type> rvalue_reference;
		typedef hmLib::rvalue_reference<unique_ptr<T[], D> > unique_ptr_rvalue_reference;
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef D deleter;
		typedef typename Alloc::template rebind<my_array_element>::other allocator;
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		my_array_element* ptrh;
		allocator alloc;
	public:
		shared_write_array() :ptrh(0) {}
		shared_write_array(pointer ptr_, unsigned int size_) :ptrh(0) {
			construct(ptr_, size_, deleter());
		}
		shared_write_array(pointer ptr_, unsigned int size_, deleter dlt_) :ptrh(0) {
			construct(ptr_, size_, dlt_);
		}
		shared_write_array(const my_type& my_) :ptrh(0) {
			share(my_.ptrh);
		}
		const my_type& operator=(const my_type& my_) {
			if(ptrh!=my_.ptrh) {
				if(ptrh)destroy();
				share(my_.ptrh);
			}
			return *this;
		}
		explicit shared_write_array(rvalue_reference mptr_) :ptrh(0) {
			swap(mptr_.ref.ptrh);
		}
		const my_type& operator=(rvalue_reference mptr_) {
			if(this!=&(mptr_.ref)) {
				if(ptrh)destroy();
				swap(mptr_.ref.ptrh);
			}
			return *this;
		}
		shared_write_array(unique_ptr_rvalue_reference mptr_, unsigned int size_) :ptrh(0) {
			construct(mptr_.ref.get(), size_, mptr_.ref.get_deleter());
			mptr_.ref.release();
		}
		~shared_write_array() {
			if(ptrh)destroy();
		}
	public:
		//�z����Ǘ����Ă��邩
		operator bool() const { return ptrh!=0; }
		//�Ǘ����Ă���z��̐擪�A�h���X���擾
		pointer get() {
			if(ptrh)return const_cast<T*>(ptrh->get());
			else return 0;
		}
		//�Ǘ����Ă���z��̐擪�A�h���X���擾
		const pointer get() const{
			if(ptrh)return const_cast<T*>(ptrh->get());
			else return 0;
		}
		//�Ǘ����Ă���z��̃f���[�^���擾
		deleter get_deleter() const {
			if(ptrh)return deleter();
			return ptrh->get_deleter();
		}
		//�z��A�N�Z�X
		reference operator[](unsigned int pos_) {
			return (ptrh->get())[pos_];
		}
		//�z��A�N�Z�X
		const reference operator[](unsigned int pos_) const {
			return (ptrh->get())[pos_];
		}
		//�w��ʒu��val���������݁A������flush����@�߂�l�ŁA���݂�flush_size��Ԃ�
		unsigned int write(unsigned int pos_, const T& val_) {
			if(prth==0)return 0;
			(ptrh->get())[pos_]=val_;
			prth->flush(pos_);
			return prth->get_rsize();
		}
		//����������val���������݁A������flush����@�߂�l�ŁA���݂�flush_size��Ԃ�
		unsigned int  write(const T& val_) {
			return write(flush_size(), val_);
		}
		//�Ǘ����Ă���z��̂̃T�C�Y��Ԃ�
		unsigned int size() const {
			if(ptrh==0)return 0;
			return ptrh->get_wsize();
		}
		//�����ς݃T�C�Y��Ԃ�
		unsigned int flush_size()const {
			if(ptrh==0)return 0;
			return ptrh->get_rsize();
		}
		//�Ǘ����Ă���z��̃T�C�Y��size_�܂Ō��炷
		bool resize(unsigned int size_) {
			if(ptrh==0)return true;
			return ptrh->resize(size_);
		}
		//�Ǘ����Ă���z��̃T�C�Y�����݂�flush�ς݃T�C�Y�܂Ō��炷
		bool resize() {
			if(ptrh==0)return true;
			return ptrh->resize();
		}
		//pos_�܂ł͏����ς݂ɂ���
		void flush(unsigned int pos_) {
			if(ptrh)ptrh->flush(pos_);
		}
		//�Ǘ����Ă���z�񖖔��܂ŏ����ς݂ɂ���
		void flush() {
			if(ptrh)ptrh->flush();
		}
		//���ݏ��L���Ă���z����Ǘ����Ă���shared_write/read_array�̐���Ԃ�
		unsigned int use_count()const {
			if(ptrh==0)return 0;
			return ptrh->get_read_count() + ptrh->get_write_count();
		}
		//�Ǘ�����z���^���Ȃ��� ���łɊǗ����Ă���z��͊J������
		void reset(pointer ptr_=0, unsigned int size_=0) {
			if(ptrh)destroy();
			construct(ptr_, size_, deleter());
		}
		//�Ǘ�����z���^���Ȃ��� ���łɊǗ����Ă���z��͊J������i�f���[�^�t�j
		void reset(pointer ptr_, unsigned int size_, deleter dlt_) {
			if(ptrh)destroy();
			construct(ptr_, size_, dlt_)
		}
		//�Ǘ�����z���unique_ptr����^���Ȃ��� ���łɊǗ����Ă���z��͊J������
		void reset(unique_ptr_rvalue_reference mptr_, unsigned int size_) {
			if(ptrh)destroy();
			construct(mptr_.ref.get(), size_, mptr_.ref.get_deleter());
			mptr_.ref.release();
		}
		//�Ǘ����Ă���z�����������
		void swap(my_type& My_) {
			my_array_element* ptrh_=My_.ptrh;
			allocator alloc_=My_.alloc;
			My_.ptrh=ptrh;
			My_.alloc=alloc;
			ptrh=ptrh_;
			alloc=alloc_;
		}
		//�Ǘ����Ă���z����J������i�z��̃�����������̂́A�S�Ă̊Ǘ��҂����Ȃ��Ȃ������ɍs����j
		void release() {
			if(ptrh)destroy();
		}
		//iterator�֐�
		iterator begin() { return get(); }
		iterator end() { return get()+size(); }
		const_iterator begin()const { return get(); }
		const_iterator end()const { return get()+size(); }
	private://������̊֐����Aptrh�����݂��Ă���/��ł��邱�Ƃ̊m�F�͂��Ă��Ȃ��̂Œ���
		void construct(pointer ptr_, unsigned int size_, deleter dlt_) {
			if(ptr_==0)return;
			if(size_==0) {
				dlt_(ptr_);
				return;
			}
			ptrh=alloc.allocate(std::size_t(1));
			alloc.construct(ptrh, move(my_array_element(ptr_, size_, dlt_)));
		}
		void destroy() {
			if(ptrh->write_detach()) {
				alloc.destroy(ptrh);
				alloc.deallocate(ptrh, std::size_t(1));
			}
			ptrh=0;
		}
		void share(my_array_element* ptrh_) {
			if(ptrh_) {
				ptrh=ptrh_->write_attach();
			}
		}
		void swap(my_array_element*& ptrh_) {
			my_array_element* tmp_prth=ptrh_;
			ptrh_=ptrh;
			ptrh=tmp_prth;
		}
	};
	//�ǂݍ��ݑ��̔z��Ǘ��N���X
	template<typename T, typename D, typename Alloc>
	class shared_read_array {
	private:
		typedef shared_read_array<T, D, Alloc> my_type;
		typedef shared_write_array<T, D, Alloc> write_type;
		typedef _shared_array_element<T, D> my_array_element;
		typedef rvalue_reference<my_type> my_rvalue_reference;
		typedef rvalue_reference<write_type> write_rvalue_reference;
		typedef hmLib::rvalue_reference<unique_ptr<T[], D> > unique_ptr_rvalue_reference;
	public:
		typedef const T* pointer;
		typedef const T& reference;
		typedef D deleter;
		typedef typename Alloc::template rebind<my_array_element>::other allocator;
		typedef const T* const_iterator;
	private:
		my_array_element* ptrh;
		allocator alloc;
	public:
		shared_read_array() :ptrh(0) {}
		shared_read_array(const my_type& my_) :ptrh(0) {
			share(my_.ptrh);
		}
		shared_read_array(pointer ptr_, unsigned int size_) :ptrh(0) {
			*this=hmLib::move(shared_write_array(mptr_, size_));
		}
		shared_read_array(pointer ptr_, unsigned int size_, deleter dlt_) :ptrh(0) {
			*this=hmLib::move(shared_write_array(mptr_, size_, dlt_));
		}
		const my_type& operator=(const my_type& my_) {
			if(ptrh!=my_.ptrh) {
				if(ptrh)destroy();
				share(my_.ptrh);
			}
			return *this;
		}
		explicit shared_read_array(my_rvalue_reference mptr_) :ptrh(0) {
			swap(mptr_.ref);
		}
		const my_type& operator=(my_rvalue_reference mptr_) {
			if(this!=&(mptr_.ref)) {
				if(ptrh)destroy();
				swap(mptr_.ref);
			}
			return *this;
		}
		shared_read_array(const write_type& my_) :ptrh(0) {
			share(my_.ptrh);
		}
		const my_type& operator=(const write_type& my_) {
			if(ptrh!=my_.ptrh) {
				if(ptrh)destroy();
				share(my_.ptrh);
			}
			return *this;
		}
		explicit shared_read_array(write_rvalue_reference mptr_) :ptrh(0) {
			swap(mptr_.ref.ptrh);
		}
		const my_type& operator=(write_rvalue_reference mptr_) {
			if(this!=&(mptr_.ref)) {
				if(ptrh)destroy();
				swap(mptr_.ref.ptrh);
			}
			return *this;
		}
		shared_read_array(unique_ptr_rvalue_reference mptr_, unsigned int size_) :ptrh(0) {
			*this=hmLib::move(shared_write_array(mptr_, size_));
		}
		~shared_read_array() {
			if(ptrh)destroy();
		}
	public:
		//�z����Ǘ����Ă��邩
		operator bool() const{ return ptrh!=0; }
		//�Ǘ����Ă���z��̐擪�A�h���X���擾
		pointer get() const {
			if(ptrh==0)return 0;
			return const_cast<T*>(ptrh->get());
		}
		//�Ǘ����Ă���z��̃f���[�^���擾
		deleter get_deleter() const {
			if(prth==0)return deleter();
			return ptrh->get_deleter();
		}
		//�z��A�N�Z�X
		reference operator[](unsigned int pos)const { return (ptrh->get())[pos]; }
		//�Ǘ����Ă���z��̓Ǎ��\�ȃT�C�Y��Ԃ�
		unsigned int size() const {
			if(ptrh==0)return 0;
			return ptrh->get_rsize();
		}
		//�Ǘ����Ă���z��̃T�C�Y��Ԃ�
		unsigned int maxsize()const {
			if(ptrh==0)return 0;
			return ptrh->get_wsize();
		}
		//�Ǘ����Ă���z�񂪏������ݏI�����Ă��邩���擾����
		bool flowing()const {
			if(ptrh==0)return 0;
			ptrh->flowing();
		}
		//���ݏ��L���Ă���z����Ǘ����Ă���shared_write/read_array�̐���Ԃ�
		unsigned int use_count()const {
			if(ptrh==0)return 0;
			return ptrh->get_write_count() + ptrh->get_read_count();
		}
		//�Ǘ�����z���^���Ȃ��� ���łɊǗ����Ă���z��͊J������
		void reset(pointer ptr_=0, unsigned int size_=0) {
			if(ptrh)destroy();
			*this=hmLib::move(shared_write_array(ptr_, size_));
		}
		//�Ǘ�����z���^���Ȃ��� ���łɊǗ����Ă���z��͊J������i�f���[�^�t�j
		void reset(pointer ptr_, unsigned int size_, deleter dlt_) {
			if(ptrh)destroy();
			*this=hmLib::move(shared_write_array(ptr_, size_, dlt_));
		}
		//�Ǘ�����z���unique_ptr����^���Ȃ��� ���łɊǗ����Ă���z��͊J������
		void reset(unique_ptr_rvalue_reference mptr_, unsigned int size_) {
			if(ptrh)destroy();
			*this=hmLib::move(shared_write_array(mptr_, size_));
		}
		//�Ǘ����Ă���z�����������
		void swap(my_type& My_) {
			my_array_element* ptrh_=My_.ptrh;
			allocator alloc_=My_.alloc;
			My_.ptrh=ptrh;
			My_.alloc=alloc;
			ptrh=ptrh_;
			alloc=alloc_;
		}
		//�Ǘ����Ă���z����J������i�z��̃�����������̂́A�S�Ă̊Ǘ��҂����Ȃ��Ȃ������ɍs����j
		void release() {
			if(ptrh)destroy();
		}
		//iterator�֐�
		const_iterator begin()const { return get(); }
		const_iterator end()const { return get()+size(); }
	private://������̊֐����Aptrh�����݂��Ă���/��ł��邱�Ƃ̊m�F�͂��Ă��Ȃ��̂Œ���
		void destroy() {
			if(ptrh->read_detach()) {
				alloc.destroy(ptrh);
				alloc.deallocate(ptrh, std::size_t(1));
			}
			ptrh=0;
		}
		void share(my_array_element* ptrh_) {
			if(ptrh_) {
				ptrh=ptrh_->read_attach();
			}
		}
		void swap(my_array_element*& ptrh_) {
			my_array_element* tmp_prth=ptrh_;
			ptrh_=ptrh;
			ptrh=tmp_prth;
		}
	};
}
#
#endif
