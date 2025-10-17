// C++98 idiom
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base 
{
	...
private:
	basic_ios(const basic_ios&);		   // copy ctor
	basic_ios& operator=(const basic_ios&)     // copty assignment

}

// C++11 version
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public:
	basic_ios(const basic_ios&) 	       = delete;
	basic_ios& operator=(const basic_ios&) = delete;
}

//C++98: improper usage detected only at link time
//C++11: use will cause compilation error
//	 reason to put them in public: access is checked before deletion status

// delete also provides a way to avoid implicit conversions
bool isLucky(int number);
bool isLucky(char)   = delete; // rejects char
bool isLucky(bool)   = delete; // rejects bool
bool isLucky(double) = delete; // rejects doubles, floats (floats prefer to convert to double)

// prevent template instantiation
template <class T>
void processPointer(T* ptr);

template <>
void processPointer<void>(void*) = delete; // can't deref, needs proper handling
template <>
void processPointer<char>(char*) = delete;
template <>
void processPointer<const char>(const char*) = delete; // typically pointer to C-style string, needs proper handling

// you really want to delete all CVR: const, volatile, ref
// fun (lol) fact: all template instances need to have the same access level
// not a problem for delete:

class Widget
{
public:
	template<class T>
		void processPointer(T* ptr) {...}
};

template<>
void Widget::processPointer<void>(void*) = delete;
