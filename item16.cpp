// mutable use case
class Polynomial
{
public:
	using RootsType = std::vector<double>;

	RootsType roots() const
	{
		if (!rootsAre Valid)
		{
			// compute and store roots
			rootsAreValid = true;
		}

		return rootVals;
	}

private:
	mutable bool rootsAreValid{ false };	// cache empty marker
	mutable RootsType rootVals{}; 		// functions as cache
};

const Polynomial P; // you still want to cache the values inside, hence mutable

// problem is that not thread-safe, even though it's (on the surface) a read-only op
// can add mutex

class Polynomial
{
public:
	using RootsType = std::vector<double>;

	RootsType roots() const
	{
		std::lock_guard<std::mutex> g(m);
		if (!rootsAre Valid)
		{
			// compute and store roots
			rootsAreValid = true;
		}

		return rootVals;
	}

private:
	mutable std::mutex m;
	mutable bool rootsAreValid{ false };	// cache empty marker
	mutable RootsType rootVals{}; 		// functions as cache
};

// problem: mutex is a move only-type so Polynomial essentially can't be copied anymore

// mutex can be overkill, atomics can solve
class Point {
public:
	double distanceFromOrigin() const noexcept
	{
		++callCount;
		return std::sqrt((x * x) + (y * y));
	}

private:
	mutable std::atomic<unsigned> callCount{ 0 };	// move only
	double x, y;
};

// big problems can arise from atomics when there are more than one variable to check
// mutexes are a better solution there

// bref, const functions aren't necessarily thread-safe, even less thread-friendly.
