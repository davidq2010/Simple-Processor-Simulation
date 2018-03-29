#include "ALU.h"
#include "ALUControl.h"
#include "ANDGate.h"
#include "Clock.h"
#include "Control.h"
#include "DataMemory.h"
#include "HardwiredConstant.h"
#include "InstructionMemory.h"
#include "MUX.h"
#include "ProgramCounter.h"
#include "RegisterFile.h"
#include "SignExtender.h"


void bulkConnect(ProcessorComponent& c1, 
				ProcessorComponent& c2, 
				int line1_start, 
				int line2_start, 
				int n_lines);

int main(int argc, char const *argv[])
{
	//--------------------------------------------------------------------------
	// Starting data
	const int n_cycles = 4; // number of cycles to run
	
	// Instructions (address starting at 0x400000)
	const int n_insts = 4;
	unsigned long instructions[n_insts] = 
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
		*/
		
		0x08100002ul, // j inst2
		0x08100003ul, // j inst3
		0x08100001ul, // j inst1
		
		
		0x20000000ul  // addi $0  $0  0   last instruction do not change
	};

	// Register content
	unsigned long reg_data[32] {};

	// Memory content
	unsigned long mem_start_address = 0x1000;
	const int mem_size = 256;
	unsigned long mem_data[mem_size];
	for (int i = 0; i < mem_size; i++) 
		mem_data[i] = i;

	//--------------------------------------------------------------------------
	// Init components
	Clock clock;
	ProgramCounter pc;

	Control ctrl;

	ALUControl alu_ctrl;

	ALU alu_add_4 ("ALU Add 4");
	ALU alu_add_branch ("ALU Branching");
	ALU alu ("Main ALU");

	ANDGate and_gate;

	bool arr_add_ctrl[4] = {0, 1, 0, 0};
	HardwiredConstant const_alu_add(arr_add_ctrl, 4);
	bool arr_const_4[32] = {}; arr_const_4[2] = 1;
	HardwiredConstant const_4 (arr_const_4, 32);
	bool arr_const_00[2] = {0, 0};
	HardwiredConstant const_00 (arr_const_00, 2);


	MUX mux_write_reg(5, "MUX DestReg");
	MUX mux_alu_src(32, "MUX ALUSrc");
	MUX mux_mem_to_reg(32, "MUX MemToReg");
	MUX mux_branch(32, "MUX Branch");
	MUX mux_jump(32, "MUX Jump");

	SignExtender sign_ext;

	InstructionMemory inst_mem(instructions, n_insts);

	RegisterFile reg_file(reg_data);

	DataMemory data_mem(mem_data, mem_start_address, mem_start_address + mem_size);

	//--------------------------------------------------------------------------
	// Wiring between components

	//--------------------------------------------
	// Clock dependent components (pc and hardwired constants)
	clock.addOutputComponent(0, pc, pc.clockID());
	clock.addOutputComponent(0, const_alu_add, 0);
	clock.addOutputComponent(0, const_4, 0);
	clock.addOutputComponent(0, const_00, 0);

	//--------------------------------------------
	// Main data cycle

	// pc -> instruction memory
	bulkConnect(pc, inst_mem, 0, 0, 32);

	// instruction decode
	//   opcode -> control
	bulkConnect(inst_mem, ctrl, 26, 0, 6);

	//   rs, rt, rd -> (write_reg MUX) -> register file
	bulkConnect(inst_mem      , reg_file      , 21 , reg_file.readRegStartID(0) , 5);
	bulkConnect(inst_mem      , reg_file      , 16 , reg_file.readRegStartID(1) , 5);
	bulkConnect(inst_mem      , mux_write_reg , 16 , mux_write_reg.startID(0)   , 5);
	bulkConnect(inst_mem      , mux_write_reg , 11 , mux_write_reg.startID(1)   , 5);
	bulkConnect(mux_write_reg , reg_file      , 0  , reg_file.writeRegStartID() , 5);

	//   imm -> sign extender
	bulkConnect(inst_mem, sign_ext, 0, 0, 16);

	//   func -> alu control
	bulkConnect(inst_mem, alu_ctrl, 0, alu_ctrl.funcStartID(), 6);

	// alu sources (src1 from register file, src 2 from register file or sign extender)
	bulkConnect(reg_file    , alu         , reg_file.regDataStartID(0) , alu.inputStartID(0)    , 32);
	bulkConnect(reg_file    , mux_alu_src , reg_file.regDataStartID(1) , mux_alu_src.startID(0) , 32);
	bulkConnect(sign_ext    , mux_alu_src , 0                          , mux_alu_src.startID(1) , 32);
	bulkConnect(mux_alu_src , alu         , 0                          , alu.inputStartID(1)    , 32);

	// data memomry inputs (address from alu, write data from register file)
	bulkConnect(alu      , data_mem , 0                          , data_mem.addressStartID()   , 32);
	bulkConnect(reg_file , data_mem , reg_file.regDataStartID(1) , data_mem.writeDataStartID() , 32);

	// register file write data (from alu or data memory)
	bulkConnect(alu            , mux_mem_to_reg , 0 , mux_mem_to_reg.startID(0)  , 32);
	bulkConnect(data_mem       , mux_mem_to_reg , 0 , mux_mem_to_reg.startID(1)  , 32);
	bulkConnect(mux_mem_to_reg , reg_file       , 0 , reg_file.writeDataStartID(), 32);

	//--------------------------------------------
	// PC update cycle

	// pc and hardwired constants -> add 4 alu
	bulkConnect(pc            , alu_add_4, 0 , alu_add_4.inputStartID(0)  , 32);
	bulkConnect(const_4       , alu_add_4, 0 , alu_add_4.inputStartID(1)  , 32);
	bulkConnect(const_alu_add , alu_add_4, 0 , alu_add_4.controlStartID() , 4 );

	// branching alu
	bulkConnect(alu_add_4     , alu_add_branch , 0 , alu_add_branch.inputStartID(0)     , 32);
	bulkConnect(sign_ext      , alu_add_branch , 0 , alu_add_branch.inputStartID(1) + 2 , 30);
	bulkConnect(const_00      , alu_add_branch , 0 , alu_add_branch.inputStartID(1)     , 2 );
	bulkConnect(const_alu_add , alu_add_branch , 0 , alu_add_branch.controlStartID()    , 4 );

	// mux add4 vs. branch
	bulkConnect(alu_add_4      , mux_branch , 0 , mux_branch.startID(0) , 32);
	bulkConnect(alu_add_branch , mux_branch , 0 , mux_branch.startID(1) , 32);

	// mux add4+branch vs. jump
	bulkConnect(mux_branch , mux_jump, 0  , mux_jump.startID(0)     , 32);

	bulkConnect(const_00   , mux_jump, 0  , mux_jump.startID(1)     , 2 );
	bulkConnect(inst_mem   , mux_jump, 0  , mux_jump.startID(1) + 2 , 26);
	bulkConnect(alu_add_4  , mux_jump, 28 , mux_jump.startID(1) + 28, 4 );

	// cycle back to pc
	bulkConnect(mux_jump , pc , 0 , 0 , 32);

	//--------------------------------------------
	// Control and ALU Control

	// beq and-gate (ctrl branch && alu zero)
	alu.addOutputComponent(alu.zeroID(), and_gate, 1);
	and_gate.addOutputComponent(0, mux_branch, mux_branch.controlID());

	// control lines
	ctrl.addOutputComponent( 0, mux_write_reg , mux_write_reg.controlID()  );
	ctrl.addOutputComponent( 1, mux_jump      , mux_jump.controlID()       );
	ctrl.addOutputComponent( 2, and_gate      , 0                          );
	ctrl.addOutputComponent( 3, data_mem      , data_mem.memReadID()       );
	ctrl.addOutputComponent( 4, mux_mem_to_reg, mux_mem_to_reg.controlID() );
	ctrl.addOutputComponent( 5, alu_ctrl      , alu_ctrl.aluOpStartID()    );
	ctrl.addOutputComponent( 6, alu_ctrl      , alu_ctrl.aluOpStartID() + 1);
	ctrl.addOutputComponent( 7, data_mem      , data_mem.memWriteID()      );
	ctrl.addOutputComponent( 8, mux_alu_src   , mux_alu_src.controlID()    );
	ctrl.addOutputComponent( 9, reg_file      , reg_file.writeControlID()  );

	// alu control lines
	bulkConnect(alu_ctrl, alu, 0, alu.controlStartID(), 4);


	//--------------------------------------------------------------------------
	// Run

	// Put starting instruction's address into PC
	for (int i = 0; i < 32; i++)
		pc.setInput(i, (InstructionMemory::START_ADDRESS >> i) & 1ul);

	Logger logger = LoggerFactory::getLogger();
	// Repeat cycles
	for (int i = 0; i < n_cycles; i++)
	{
		logger.log("========================================================================");
		logger.log(std::string("Cycle ") + std::to_string(i+1));
		logger.log("========================================================================");
		clock.rise();
		clock.fall();
	}

}

void bulkConnect(ProcessorComponent& c1, 
				ProcessorComponent& c2, 
				int line1_start, 
				int line2_start, 
				int n_lines)
{
	for (int i = 0; i < n_lines; i++)
		c1.addOutputComponent(i + line1_start, c2, i + line2_start);
}
