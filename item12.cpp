class Base
{
public:
	virtual void doWork();
};

class Derived : public Base 
{
public:
	virtual void doWork();
};

std::unique_ptr<Base> upb = std::make_unique<Derived>();
upb->doWork();	// dynamic dispatch calls Derived::doWork()

// there are a couple of conditions for this:
// 	- base class function must be virtual
// 	- base and derived functions must have the same name (except if dtor)
// 	- parameter types must be the same
// 	- constness must be the same
// 	- return types and exception specifications must be compatible
// 	- and c++11 ref qual must be the same

// C++11 reference qualifiers
class Widget
{
public:
	void doWork() &;	// applies when *this lvalue, i.e. lvalue calls it
	void doWork() &&;	// applies when *this rvalue, i.e. rvalue calls it
};

Widget makeWidget(); 		// returns rvalue
Widget w;			// lvalue
w.doWork();			// calls Widget::doWork() &  -> *this is lvalue
makeWidget().doWork();		// calls Widget::doWork() && -> *this is rvalue

// note to self: this is a pointer to the current instance of the class

// if you make mistakes with the above rules, very likely that compilers won't say shit
// here comes C++11 override

class Derived public Base {
public:
	virtual void mf1() 	         override;
	virtual void mf2(unsigned int x) override;
	virtual void mf3() &&		 override;
	virtual void mf4() const	 override;

}

// more about c++11 referene qualifiers
void doSomething(Widget& w);	// accepts only lvalue Widgets
void doSomething(Widget&& w);	// accepts only rvalue Widgets, rvalue ref param

// a use case
class Widget
{
public:
	using DataType = std::vector<double>;
	DataType& data() { return values; }
private:
	DataType values;
};

Widget w;
auto vals1 = w.data();	// copy w.values into vals1
			// data returns an lvalue reference DataType&
			// init vals1 from lvalue -> copy ctor

Widget makeWidget();
auto vals2 = makeWidget().data();	// makeWidget().data() lvalue ref, so lvalue
					// we copy what's in there
					// but it's a temp, we'd rather just move
					// hence we'd like to specify when data is invoked on rvalue Widget
					// --> reference qualifiers

class Widgget 
{
public:
	using DataType = std::vector<double>;
	DataType& data() & { return values; }
	DataType data() && { return std::move(values); } // notice that no "&" in signature
private:
	DataType values;
}

auto vals1 = w.data(); 	 	  // lvalue overload called, copy ctor
auto vals2 = makeWidget().data(); // rvalue overload, move ctor
