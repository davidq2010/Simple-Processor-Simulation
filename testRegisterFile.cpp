#include <iostream>
#include <iomanip>

#include "ProcessorUtil.h"
#include "RegisterFile.h"

using namespace std;

typedef unsigned long long ullong;

void testRead(RegisterFile& rf, ullong reg1, ullong reg2,
				ullong expected_out_1, ullong expected_out_2)
{
	for (int i = 0; i < 5; i++)
	{
		rf.setInput(i, (reg1 >> i) & 1);
		rf.setInput(i + 5, (reg2 >> i) & 1);
	}

	ullong out = ioutil::getOutputs(rf);

	ullong out_1 = out & 0xFFFF'FFFFull;
	ullong out_2 = out >> 32 & 0xFFFF'FFFFull;

	cout << setw(5) << left << out_1 << "[" << expected_out_1 << "]" << endl;
	cout << setw(5) << left << out_2 << "[" << expected_out_2 << "]" << endl;
}

void testWrite(RegisterFile& rf, ullong reg, ullong data)
{
	rf.setInput(rf.writeControlID());
	for (int i = 0; i < 5; i++)
		rf.setInput(i + rf.writeRegStartID(), (reg >> i) & 1);

	for (int i = 0; i < 32; i++)
		rf.setInput(i + rf.writeDataStartID(), (data >> i) & 1);

	ullong out = ioutil::getOutputs(rf);

	testRead(rf, reg, reg, data, data);
}


int main(int argc, char const *argv[])
{
	unsigned long data[32];
	for (int i = 0; i < 32; i++)
		data[i] = i;

	RegisterFile rf(data);

	cout << "============================" << endl;
	cout << " Test read" << endl;
	cout << "============================" << endl;
	testRead(rf, 1, 2, 1, 2); cout << endl;
	testRead(rf, 31, 8, 31, 8); cout << endl;
	testRead(rf, 1, 1, 1, 1); cout << endl;
	testRead(rf, 0, 0, 0, 0); cout << endl;

	testWrite(rf, 0, 100); cout << endl;
	testWrite(rf, 1, 101); cout << endl;
	testWrite(rf, 1, 111); cout << endl;
	testWrite(rf, 31, 131); cout << endl;

	return 0;
}