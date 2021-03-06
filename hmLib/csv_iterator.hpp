#ifndef HMLIB_CSVITERATOR_INC
#define HMLIB_CSVITERATOR_INC 100
#
#include<iterator>
#include<iostream>
#include<sstream>
namespace hmLib{
	namespace csv{
		template<class Elem = char, class Traits = std::char_traits<Elem> >
		std::basic_string < Elem, Traits > cell_encode(std::basic_string < Elem, Traits > Str, Elem Sep_, Elem Esc){
			if(Str.find(Sep_) < Str.size() || Str.find(Esc) < Str.size()){
				for(auto itr = Str.begin(); itr != Str.end(); ++itr){
					if(*itr == Esc){
						itr = Str.insert(++itr, Esc);
					}
				}

				Str.insert(Str.begin(), Esc);
				Str.push_back(Esc);
			}

			return std::move(Str);
		}
		template<class Elem = char, class Traits = std::char_traits<Elem> >
		std::basic_string < Elem, Traits > cell_decode(std::basic_string < Elem, Traits > Str, Elem Sep_, Elem Esc){
			if(Str.size()>1 && Str.front()==Esc && Str.back()==Esc){
				Str.erase(Str.begin());
				Str.pop_back();

				bool EscFlag=false;
				for(auto itr = Str.begin(); itr != Str.end(); ++itr){
					if(*itr == Esc){
						if(EscFlag){
							itr = Str.erase(itr);
							--itr;
							EscFlag = false;
						} else{
							EscFlag = true;
						}
					} else{
						EscFlag = false;
					}
				}
			}

			return std::move(Str);
		}
	}
	template<class Elem = char, class Traits = std::char_traits<Elem> >
	class basic_ocsv_iterator : public std::iterator < std::output_iterator_tag, void, void, void, void > {
	private:
		using my_type = basic_ocsv_iterator < Elem, Traits >;
		using my_ostream = std::basic_ostream < Elem, Traits > ;
		using my_string = std::basic_string < Elem, Traits > ;
	private:
		struct output_proxy{
		private:
			my_type& My;
		public:
			output_proxy(my_type& My_) :My(My_){}
			void operator=(const my_string& Str){
				if(My.IsCellHead && !My.IsLineHead){
					*(My.pstream) << My.Sep;
					My.IsCellHead = false;
				}

				*(My.pstream) << csv::cell_encode(Str,My.Sep,My.Esc);
			}
			void raw_str(const my_string& Str){
				if(My.IsCellHead && !My.IsLineHead){
					*(My.pstream) << My.Sep;
					My.IsCellHead = false;
				}

				*(My.pstream) << Str;
			}
			template<typename T>
			output_proxy& operator<<(T Val){
				if(My.IsCellHead && !My.IsLineHead){
					*(My.pstream) << My.Sep;
					My.IsCellHead = false;
				}

				*(My.pstream) << Val;
				return *this;
			}
		};
	private:
		my_ostream* pstream;
		Elem Sep;
		Elem End;
		Elem Esc;
		bool IsCellHead;
		bool IsLineHead;
	public:
		basic_ocsv_iterator()
			: pstream(nullptr){
		}
		basic_ocsv_iterator(my_ostream& Stream_, Elem Sep_ = ',', Elem End_ = '\n', Elem Esc_ = '"')
			: pstream(&Stream_)
			, Sep(Sep_)
			, End(End_)
			, Esc(Esc_)
			, IsCellHead(false)
			, IsLineHead(true){
		}
		basic_ocsv_iterator(const my_type& x) = default;
	public:
		operator bool()const{ return pstream; }
		output_proxy operator*(){ return output_proxy(*this); }
		my_type& operator++(){
			IsCellHead = true;
			IsLineHead = false;
			return *this;
		}
		my_type operator++(int){
			my_type ans(*this);
			operator++();
			return ans;
		}
		bool eol()const{ return IsLineHead; }
		void endl(){
			(*pstream) << End;
			IsLineHead = true;
			IsCellHead = false;
		}
	};
	template<class Elem = char, class Traits = std::char_traits<Elem> >
	class basic_icsv_iterator : public std::iterator < std::input_iterator_tag, std::basic_string<Elem,Traits>> {
	private:
		using my_type = basic_icsv_iterator < Elem, Traits > ;
	public:
		using my_istream = std::basic_istream < Elem, Traits > ;
		using my_pos = typename my_istream::pos_type;
		using my_string = std::basic_string < Elem, Traits > ;
		using my_sstream = std::basic_stringstream < Elem, Traits > ;
	private:
		my_istream* pstream;
		Elem Sep;
		Elem End;
		Elem Esc;
		my_pos Pos;
		my_sstream sstream;
		bool HasRead;
		my_pos ReadPos;
		bool IsLineHead;
	private:
		void next(){
			if(HasRead){
				HasRead = false;
				Pos = ReadPos;
			} else{
				Elem c;
				pstream->seekg(0, std::ios::end);
				auto EndPos = pstream->tellg();
				pstream->seekg(Pos);

				bool EscFlag = false;
				while(pstream->tellg() != EndPos){
					c = pstream->get();

					if(c == End || c == EOF){
						IsLineHead = true;
						break;
					}

					if(c == Sep && !EscFlag){
						IsLineHead = false;
						break;
					}

					if(c == Esc){
						EscFlag = !EscFlag;
					}
				}

				Pos = pstream->tellg();
			}			
		}
		my_sstream& read(){
			if(!HasRead){
				Elem c;
				sstream.str(my_string());
				sstream.clear();

				pstream->seekg(0, std::ios::end);
				auto EndPos = pstream->tellg();
				pstream->seekg(Pos);

				bool EscFlag=false;
				while(pstream->tellg() != EndPos){
					c = pstream->get();

					if(c == End || c == EOF){
						IsLineHead = true;
						break;
					}

					if(c == Sep && !EscFlag){
						IsLineHead = false;
						break;
					}

					if(c == Esc){
						EscFlag = !EscFlag;
					}
					
					sstream << c;
				}

				ReadPos = pstream->tellg();
				HasRead = true;
			}
			return sstream;
		}
	private:
		struct input_proxy{
		private:
			my_type& My;
		public:
			input_proxy(my_type& My_) :My(My_){}
			operator my_string(){ return csv::cell_decode(My.read().str(), My.Sep, My.Esc); }
			my_string raw_str(){return My.read().str();}
			template<typename T>
			input_proxy& operator>>(T& Val){
				My.read() >> Val;
				return *this;
			}
			friend std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& out, input_proxy p){
				return out << static_cast<my_string>(p);
			}
		};
	public:
		basic_icsv_iterator() :pstream(nullptr){}
		basic_icsv_iterator(my_istream& Stream_, Elem Sep_ = ',', Elem End_ = '\n', Elem Esc_ = '"')
			: pstream(&Stream_)
			, Sep(Sep_)
			, End(End_)
			, Esc(Esc_)
			, Pos(Stream_.tellg())
			, sstream()
			, HasRead(false)
			, IsLineHead(false){
		}
		basic_icsv_iterator(const my_type& My_)
			: pstream(My_.pstream)
			, Sep(My_.Sep)
			, End(My_.End)
			, Esc(My_.Esc)
			, Pos(My_.Pos)
			, sstream(My_.sstream.str())
			, HasRead(My_.HasRead)
			, ReadPos(My_.ReadPos)
			, IsLineHead(My_.IsLineHead){
		}
		my_type& operator=(const my_type& My_){
			if(this != &My_){
				pstream = My_.pstream;
				Sep = My_.Sep;
				End = My_.End;
				Esc = My_.Esc;
				Pos = My_.Pos;
				sstream = My_.sstream.str();
				HasRead = My_.HasRead;
				ReadPos = My_.ReadPos;
				IsLineHead = My_.IsLineHead;
			}
		}
		input_proxy operator*(){return input_proxy(*this);}
		my_type& operator++(){
			next();
			return *this;
		}
		my_type operator++(int){
			basic_icsv_iterator ans(*this);
			operator++();
			return ans;
		}
		bool eol()const{ return IsLineHead; }
		bool eof(){
			pstream->seekg(0, std::ios::end);
			return Pos == pstream->tellg();
		}
		my_pos pos()const{ return Pos; }
		friend bool operator==(const my_type& my1, const my_type& my2){
			if(&my1 == &my2)return true;

			if(my1.pstream != my2.pstream) return false;

			return my1.Pos == my2.Pos;
		}
		friend bool operator!=(const my_type& my1, const my_type& my2){ return !(my1 == my2); }
	public:
		my_type get_line_end(){
			my_type ans(*this);
			advance_line(ans, 1);

			return ans;
		}
		my_type get_file_end(){
			my_type ans;
			ans.pstream = pstream;
			ans.End = End;
			ans.Sep = Sep;
			pstream->seekg(0, std::ios::end);
			ans.Pos = pstream->tellg();
			ans.HasRead = false;
			ans.ReadPos = pstream->tellg();
			ans.IsLineHead = true;

			return ans;
		}
	};
	template<class Elem = char, class Traits = std::char_traits<Elem> >
	inline basic_icsv_iterator<Elem, Traits> line_end(std::basic_istream < Elem, Traits >& Stream_, Elem Sep_ = ',', Elem End_ = '\n'){
		basic_icsv_iterator<Elem, Traits> itr(Stream_, Sep_, End_);
		return itr.get_line_end();
	}
	template<class Elem = char, class Traits = std::char_traits<Elem> >
	inline basic_icsv_iterator<Elem, Traits> file_end(std::basic_istream < Elem, Traits >& Stream_, Elem Sep_ = ',', Elem End_ = '\n'){
		basic_icsv_iterator<Elem, Traits> itr(Stream_, Sep_, End_);
		return itr.get_file_end();
	}
	template<class Elem = char, class Traits = std::char_traits<Elem> >
	inline void advance_line(basic_icsv_iterator<Elem, Traits>& itr, unsigned int num = 1){
		unsigned int no = 0;
		do{
			++itr;
			if(itr.eol())++no;
		} while(no < num);
	}

	using ocsv_iterator = basic_ocsv_iterator < char, std::char_traits<char> >;
	using icsv_iterator = basic_icsv_iterator < char, std::char_traits<char> >; 
}
#
#endif
