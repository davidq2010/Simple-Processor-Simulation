#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "SignExtender.h"
#include "ProcessorUtil.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Given an input and a correct output, check if SignExtender perform correctly
////////////////////////////////////////////////////////////////////////////////
bool testOutput(Component& _comp, unsigned long _input, 
				unsigned long _correct_output) 
{
	ioutil::setInputs(_comp, _input);
	unsigned long output = ioutil::getOutputs(_comp);

	cout << "Input:    " << _input << endl;
	cout << "Output:   " << setw(15) << left << output;
	if (output != _correct_output)
		cout << " Failed, expect " << _correct_output << endl;
	else
		cout << " Correct" << endl;

	return output == _correct_output;
}

int main(int argc, char const *argv[])
{
	SignExtender se;

	cout << hex << showbase; // print number in hexadecimal format,

	bool all_test_passed = true;

	cout << "========================================" << endl;
	cout << " Test output value" << endl;
	cout << "========================================" << endl << endl;

	all_test_passed = all_test_passed && testOutput(se, 0x1111UL, 0x1111UL);
	all_test_passed = all_test_passed && testOutput(se, 0x7FFFUL, 0x7FFFUL);
	all_test_passed = all_test_passed && testOutput(se, 0xFFFFUL, 0xFFFFFFFFUL);
	all_test_passed = all_test_passed && testOutput(se, 0x8000UL, 0xFFFF8000UL);

	cout << "========================================" << endl;
	cout << " Test out of range behavior" << endl;
	cout << "========================================" << endl << endl;

	all_test_passed = all_test_passed && testOutOfRange(se, 0x1111UL, 0x1111UL);
	all_test_passed = all_test_passed && testOutOfRange(se, 0x7FFFUL, 0x7FFFUL);
	all_test_passed = all_test_passed && testOutOfRange(se, 0xFFFFUL, 0xFFFFFFFFUL);
	all_test_passed = all_test_passed && testOutOfRange(se, 0x8000UL, 0xFFFF8000UL);
	
	cout << "========================================" << endl;
	cout << "All test passed: " << boolalpha << all_test_passed << endl;

	return 0;
}

