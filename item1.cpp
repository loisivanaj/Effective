template <class T>
void f(ParamType param);
f(expr);

// Case 1: ParamType is ref or ptr, not univ ref
template <typename T>
void f(T* param);

int x = 27;
const int *px = &x;
f(&x); // T -> int, param -> int*
f(px); // T -> const int, param -> const int*

// funky shit
int* a, b; // only a is a pointer xd, hence the prefered
int *a, *b;

// Case 2: ParamType is a univ ref T&&
// if expr lvalue: T, ParamType deduced to be lvalue references
// if expr rvalue: see above

template<typename T>
void f(T&& param); 	// param is now a univ reference

int x = 27;
const int cx = x;
const int& rx = x;

f(x);			// x - lvalue, so T is int&
			// param - int&

f(cx);			// cx - lvalue
			// T - const int&, param - const int&

f(rx);			// rx - lvalue
			// T - const int&, param - const int&

f(27);			// 27 - rvalue
			// T - int, param int&&

// Case 3: ParamType is neither a pointer nor a reference

template<class T>
void f(T param); 	// rules -> ignore ref, const and volatile
			// because copies

int x = 27;
const int cx = x;
const int& rx = x;

f(x);			// x - lvalue
			// T - int, param - int

f(cx);			// cx - lvalue
			// T - int, param - int

f(rx);			// rx - lvalue
			// T - int, param - int, rx is automatically deferenced
	
f(27);			// 27 - rvalue;
			// T - int, param - int

const char* const ptr = "Fun with ptrs";
f(ptr);			// ptr - lvalue
			// constness of the ptr is ignored, as above as the ptr itself is copied
			// but T - const char*

// How about arrays ?
const char name[] = "J. P. Briggs";
const char* ptrToName = name; // decay to ptr

template<typename T>
void f(T param);
f(name);		// const char*
// Turns out that there is no such thing as an array function parameter.
// It's really decaying to a pointer -> void f(char[]) -> void f(char*)

// Le funny incoming: you can pass arrays by reference
template<typename T>
void f(T& param);
f(name);		// T - const char[13] xddddd, param - const char (&)[13]

// this actually actually allows you do get the size of the array in the template
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept { return N; }
// so at compile time, you allocate arrays of the same size as some init list
int keyVals[] = { 1, 3, 5, 7, 0 };
int mappedVals[arraySize(keyVals)];
std::array<int, arraySize(keyVals)> mappedVals;

// how about function arguments?
void someFunc(int, double);

template<typename T>
void f1(T param);	// passed by value -> decays to pointer

template<typename T>
void f2(T& param);	// passed by reference

f1(someFunc);		// param - ptr-to-func, T - void (*)(int, double)
f2(someFunc);		// param - ref-to-func, T - void (&)(int, double)
int (*fptr)(int, int)   // this one is for me. Declares pointer to function (int, int) -> int
		
// auto is algorithmically deduced from templates, so same rules, except:
// careful with initializer lists
auto x{ 27 } // std::initializer_list<int>
auto x = { 27 } // std::initializer_list<int>

// there's actually two type deductions here
