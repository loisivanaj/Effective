// unique_ptr use case: factory functions
template<typename... Ts>
std::unique_ptr<Investment>
makeInvestments(Ts&&... params);

// usage
{
	auto pInvestment = makeInvestments(arguments);
} // destroy *pInvestment

class Investment {
public:
	virtual ~Investment();
};

// you can pass custom deleters
auto delInvmt = [](Investment* pInvestment)
		{
			makeLogEntry(pInvestment);
			delete pInvestment;
		};

template<typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt)>
makeInvestment(Ts&&... params)
{
	std::unique_ptr<Investment, decltype(delInvmt)>
	pInv(nullptr, delInvmt); // custom deleter

	if ( /* stock */)
	{
		pInv.reset(new Stock(std::forward<Ts>(params)...));
	}
	else if ( /* bond */)
	{
		pInv.reset(new Bond(std::forward<Ts>(params)...));
	}
	else if ( /* real estate */)
	{
		pInv.reset(new RealEstate(std::forward<Ts>(params)...));
	}

	return pInv;
}

// using C++14 auto function type deduction
template<typename... Ts>
auto makeInvestment(Ts&&... params)
{
	auto delInvmt = [](Investment* pInvestment) // now inside
			{
				makeLogEntry(pInvestment);
				delete pInvestment;
			};
	...
}
