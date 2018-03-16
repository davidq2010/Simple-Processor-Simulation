#include <iomanip>
#include <iostream>

#include "ALU.h"

using namespace std;

bool testALUOutput(ALU& _alu, 
					unsigned long _a, 
					unsigned long _b, 
					bool _b_negate, 
					bool _less, 
					bool _equal, 
					unsigned long _expected_result, 
					bool _expected_zero)
{
	for (int i = 0; i < 32; i++)
	{
		_alu.setInput(i, (_a >> i) & 1ul);
		_alu.setInput(i + 32, (_b >> i) & 1ul);
	}

	_alu.setInput(_alu.bNegateID(), _b_negate);
	_alu.setInput(_alu.lessID()   , _less    );
	_alu.setInput(_alu.equalID()  , _equal   );

	unsigned long result = 0ul;

	for (int i = 31; i >= 0; i--)
	{
		result <<= 1;
		result |= _alu.getOutput(i);
	}

	bool zero = _alu.getOutput(_alu.zeroID());

	cout << "Result: " << setw(12) << left << result;

	if (result == _expected_result) 
		cout << "Pass" << endl;
	else
		cout << "Fail, expect " << _expected_result << endl;

	cout << "Zero:   " << setw(12) << left << zero;
	if (zero == _expected_zero)
		cout << "Pass" << endl;
	else
		cout << "Fail, expect " << _expected_zero << endl;

	return (result == _expected_result) && (zero == _expected_zero);
}

int main(int argc, char const *argv[])
{
	ALU alu;

	// Control lines (bNeg, less, equal)
	// ADD: 0 0 0
	// SUB: 1 0 0
	// SLT: 1 1 0
	// BEQ: 1 0 1
	
	testALUOutput(alu, 1000'000ul, 500'000ul, 0, 0, 0,  1500'000ul, 0);
	cout << endl;
	testALUOutput(alu, 1000'000ul, 500'000ul, 1, 0, 0,  500'000ul, 0);
	cout << endl;
	testALUOutput(alu, 500'000ul, 1000'000ul, 1, 0, 0,  0xFFFFFFFFll - 499'999, 0);
	cout << endl;
	testALUOutput(alu, 500'000ul, 1000'000ul, 1, 1, 0,  1, 0);
	cout << endl;
	testALUOutput(alu, 1000'000ul, 500'000ul, 1, 1, 0,  0, 0);
	cout << endl;
	testALUOutput(alu, 500'000ul, 1000'000ul, 1, 0, 1,  0xFFFFFFFFll - 499'999, 0);
	cout << endl;
	testALUOutput(alu, 500'000ul,  500'000ul, 1, 0, 1,  0, 1);
	cout << endl;
}