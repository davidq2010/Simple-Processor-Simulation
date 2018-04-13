#include "Processor.h"

int main(int argc, char const *argv[])
{
	std::vector<unsigned long> instructions = 
	{
		/*0x00220020ul, // add  $0  $1  $2    (0)
		0x00641820ul, // add  $3  $3  $4
		0x20410064ul, // addi $1  $2  100
		0x202103e8ul, // addi $1  $1  1000
		0x02bfa822ul, // sub  $21 $21 $31
		0x0085002aul, // slt  $0  $4  $5    (5)
		0x0295002aul, // slt  $0  $20 $21
		0x23de0001ul, // addi $30 $30 1
		0x13dffffeul, // beq  $30 $31 -2
		
		0x08100002ul, // j inst2
		0x08100003ul, // j inst3
		0x08100001ul, // j inst1
		*/
		0x20001000ul, // addi $0  $0  0x1000
		0x2021abcdul, // addi $1  $1  0xabcd
		0xac010004ul, // sw   $1  4($0)
		0x8c020004ul, // lw   $2  4($0)
		
		0x20000000ul  // addi $0  $0  0   last instruction do not change
	};

	std::vector<unsigned long> registers(32, 0);

	std::vector<unsigned long> memory (16, 0x100000);
	unsigned long mem_start_address = 0x1000;


	Processor processor (instructions, registers, memory,  mem_start_address);

	Logger logger;
	processor.setLogger(&logger);


	//--------------------------------------------------------------------------
	// Run

	// Repeat cycles
	int loops = instructions.size();
	for (int i = 0; i < loops; i++)
	{
		logger.log("========================================================================");
		logger.log(std::string("Cycle ") + std::to_string(i+1));
		logger.log("========================================================================");
		processor.step();
	}

	return 0;
}
