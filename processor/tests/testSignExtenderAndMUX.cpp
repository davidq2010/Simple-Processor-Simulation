#include <iomanip>
#include <iostream>

#include "MUX.h"
#include "ProcessorUtil.h"
#include "SignExtender.h"

using namespace std;

int main(int argc, char const *argv[])
{
	cout << hex << showbase;

	SignExtender se1;
	SignExtender se2;
	MUX mux (se1.numOutputs());

	for (int i = 0; i < se1.numOutputs(); i++)
		se1.addOutputComponent(i, mux, i + mux.startID(0));

	for (int i = 0; i < se2.numOutputs(); i++)
		se2.addOutputComponent(i, mux, i + mux.startID(1));

	ioutil::setInputs(se1, 0xABCD);
	ioutil::setInputs(se2, 0x1234);
	mux.setInput(MUX::CONTROL_LINE_ID, 0);
	unsigned long muxOut0 = ioutil::getOutputs(mux);

	ioutil::setInputs(se1, 0xABCD);
	ioutil::setInputs(se2, 0x1234);
	mux.setInput(MUX::CONTROL_LINE_ID, 1);
	unsigned long muxOut1 = ioutil::getOutputs(mux);

	cout << setw(10) << left << muxOut0 << "[0xFFFFABCD]" << endl;
	cout << setw(10) << left << muxOut1 << "[0x1234]" << endl;

	return 0;
}