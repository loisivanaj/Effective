int f(int x) throw;	// c++98, possibly unwinds call stack in c++11
int f(int x) noexcept;  // c++11

// noexcept tells the compiler that it doesn't need to keep the function in an unwindable state
// even stronger case for move operations

std::vector<Widget> vw;
Widget w;
vw.push_back(w); // old pushback: copies from old mem, then destroys old mem when realloc
		 // this offers exception safety guarantees where v is recoverable if some
		 // exception rises during the copying.
		 // Blindly moving breaks this so you can't just move without a noexcept
		 // guarantee, so now you need the noexcept part on move operations

// conditionally noexcept
template <class T, size_t N>
void swap(T (&a)[N],
	  T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

template <class T1, class T2>
struct pair {
	void swap(pair& p) noxecept(noexcept(swap(first, p.first)) &&
				    noexcept(swap(second, p.second)));
};

// stl memory dealloc and destructor functions pretty much all but noexcept
// implicitely noexcept
