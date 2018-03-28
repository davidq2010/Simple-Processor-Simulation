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
	const int n_insts = 0;
	unsigned long instructions[n_insts] {

	}

	unsigned long reg_data[32] {
		
	}

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

	ALU alu_add_4;
	ALU alu_add_jump
	ALU alu;

	bool arr_add_ctrl[4] = {0, 0, 1, 0};
	HardwiredConstant const_alu_add(arr_add_ctrl, 4);
	bool arr_const_4[32] = {}; arr_const_4[2] = 1;
	HardwiredConstant const_4 (arr_const_4, 32);

	SignExtender sign_ext;

	MUX mux_write_reg(5);
	MUX mux_alu_src(32);
	MUX mux_mem_to_reg(32);
	MUX mux_branch(32);
	MUX mux_jump(32);

	InstructionMemory inst_mem(instructions, n_insts);

	RegisterFile reg_file(reg_data);

	DataMemory data_mem(mem_data, mem_start_address, mem_start_address + mem_size);

	//--------------------------------------------------------------------------
	// Wiring between components

	// Clock dependent components (pc and hardwired constants)
	clock.addOutputComponent(0, pc, 0);
	clock.addOutputComponent(0, const_alu_add, 0);
	clock.addOutputComponent(0, const_4, 0);

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

	// data mem inputs (address from alu, write data from register file)
	bulkConnect(alu      , data_mem , 0                          , data_mem.addressStartID()   , 32);
	bulkConnect(reg_file , data_mem , reg_file.regDataStartID(1) , data_mem.writeDataStartID() , 32);

	// register file write data (from alu or data memory)
	bulkConnect(alu      , mux_mem_to_reg , 0 , mux_mem_to_reg.startID(0) , 32);
	bulkConnect(data_mem , mux_mem_to_reg , 0 , mux_mem_to_reg.startID(1) , 32);

	//--------------------------------------------
	// PC update cycle

	// pc and hardwired constants -> add 4 alu
	bulkConnect(pc            , alu_add_4, 0 , alu_add_4.inputStartID(0)  , 32);
	bulkConnect(const_4       , alu_add_4, 0 , alu_add_4.inputStartID(1)  , 32);
	bulkConnect(const_alu_add , alu_add_4, 0 , alu_add_4.controlStartID() , 4 );

	// 

	//--------------------------------------------
	// Control and ALU Control







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