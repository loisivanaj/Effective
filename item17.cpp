class Widget
{
public:
	Widget(Widget&& rhs); 		 // move constructor
	Widget& operator=(Widget&& rhs); // move assignment operator
};

// moves happen member-wise for each member variable
// quick note: static members are "per class". if derived class redefines,
// then it will have it's own

// move constructor also move-constructs base class parts

// turns out it's more like a move "request".
// if the underlying member value can't be moved, it'll be copy constructed

// defining any of move, movea, copy, copya deletes the others (= delete)
// -> rule of 5
// for backwards compatibility reasons, dtor doesn't delete cpy, cpya (though should)
// but nukes mv, mva

// to sum it up:
// Move operations are generated for classes (when needed) if:
// 	No copy op declared
// 	No move op declared
// 	No dtor

// to quickly fix things, = default (C++11)
// classic example: polymorphic base class
// you have to defined a virtual dtor but this disables the rest so:

class Base
{
public:
	virtual ~Base() = default; // disables the others

	Base(const Base&) 	     = default;
	Base& operator=(const Base&) = default;

	Base(const Base&&)  	      = default;
	Base& operator=(const Base&&) = default;
};

class StringTable 
{
public:
	StringTable() {}
private:
	std::map<int, std::string> values;
};

// if you add logging
class StringTable
{
public:
	StringTable()
	{ makeLogEntry("Creating StringTable object"); }

	~StringTable()
	{ makeLogEntry("Destroying StringTable object"); } // disables move (though copy deprec)
private:
	std::map<int, std::string> values;
}
// this will get through functional unit testing for testing move because the move thing will
// call copy as it's not movable, even though move = delete;. Declaring = default would have
// fixed this

// as of c++11, these special member rules do not apply to all templates
class Widget
{
	template<typename T>
	Widget(const T& rhs); // cpy

	template<typenameT>
	Widget& operator=(const T& rhs); // cpya
};
// compiler will still generate copy and move operations
