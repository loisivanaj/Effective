// initializer list ctor is VERY STRONGLY prefered
// compiler will do almost anything to use it

class Widget {
public:
	Widget(int i, bool b);
	Widget(int i, double d);
	Widget(std::initializer_list<long double> il);
	
	operator float() const;
};


Widget w1(10, true); // calls ctor 1
Widget w1{10, true}; // calls il ctor and will implicitly convert bool to long double
widget w3(10, 5.0);  // calls ctor 2;
Widget w4{10, 5.0};  // calls il ctor and converts 5.0 to long double
// even move and copy ctors can be hijacked
Widget w5(w4); 	     // cpy ctor
Widget w5{w4};       // calls il ctor, w4 converts to float then to long double;
Widget w7(std::move(w4)); // calls move ctor
Widget w8{std::move(w4)}; // calls il ctor
// even calls it when ctors can't match it

class Widget {
public:
	Widget(int i, bool b);
	Widget(int i, double d);
	Widget(std::initializer_list<bool> il);
};
Widget w{10, 5.0}; // error! requires narrowing conversions

// will only use another more appropriate one if there is no conversion possible such as
Widget(std::initializer_list<std::string> il);

// edge case: {}. Can mean no arguments for ctor but can also mean empty il
// This will always call the default constructor. If you want to force il{}: 
Widget w{{}};
Widget w({});

// turns out this shit is actually super important
// std::vector has an il ctor and a non il ctor where you provide the size of the vector and the element to be repeated
std::vector v0{10, 20}; 	// makes vector with 10 and 20 as values
std::vector v1(10, 20);		// makes a vector of size 10 with 20 in each spot 

// variadic template
template<class T, class... Ts>
void doSomeWork(Ts&&... params)
{
	// create local T object from params
	T localObject(std::forward<Ts>(params)...);
	T localObject{std::forward<Ts>(params)...};
}
// then call
std::vector<int> v;
doSomeWork<std::vector<int>>(10, 20);
// if you used braces in the template, you'll get a 2-elem vector (10, 20)
// if you used parentheses, you'll get a 10-elem vector will with 20
// this is the exact problem that make_unique and make_shared solve
