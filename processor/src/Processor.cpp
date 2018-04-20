#include "Processor.h"


Processor::
Processor(std::vector<unsigned long> _instructions,
          std::vector<unsigned long> _register_data,
          std::vector<unsigned long> _memory_data,
          unsigned long _memory_start_address)
  : m_alu_add_4      ("ALU PC + 4"),
    m_alu_add_branch ("ALU PC + branch"),
    m_alu            ("ALU Main"),
    m_const_alu_add  (2UL, 4),
    m_const_4        (4UL, 32),
    m_const_00       (0UL, 2),
    m_mux_write_reg  (5, "MUX DestReg"),
    m_mux_alu_src    (32, "MUX ALUSrc"),
    m_mux_mem_to_reg (32, "MUX MemToReg"),
    m_mux_branch     (32, "MUX Branch"),
    m_mux_jump       (32, "MUX Jump"),
    m_inst_mem       (_instructions),
    m_reg_file       (_register_data),
    m_data_mem       (_memory_data, _memory_start_address)
{
  //----------------------------------------------------------------------------
  // Wiring between components

  //--------------------------------------------
  // Clock dependent components (pc and hardwired constants)
  m_clock.addOutputComponent(0, m_pc, m_pc.clockID());
  m_clock.addOutputComponent(0, m_const_alu_add, 0);
  m_clock.addOutputComponent(0, m_const_4, 0);
  m_clock.addOutputComponent(0, m_const_00, 0);

  //--------------------------------------------
  // Main data cycle

  // pc -> instruction memory
  bulkConnect(m_pc, m_inst_mem, 0, 0, 32);

  // instruction decode
  //   opcode -> control
  bulkConnect(m_inst_mem, m_ctrl, 26, 0, 6);

  //   rs, rt, rd -> (write_reg MUX) -> register file
  bulkConnect(m_inst_mem      , m_reg_file      , 21 , m_reg_file.readRegStartID(0)      , 5);
  bulkConnect(m_inst_mem      , m_reg_file      , 16 , m_reg_file.readRegStartID(1)      , 5);
  bulkConnect(m_inst_mem      , m_mux_write_reg , 16 , m_mux_write_reg.operandStartID(0) , 5);
  bulkConnect(m_inst_mem      , m_mux_write_reg , 11 , m_mux_write_reg.operandStartID(1) , 5);
  bulkConnect(m_mux_write_reg , m_reg_file      , 0  , m_reg_file.writeRegStartID()      , 5);

  //   imm -> sign extender
  bulkConnect(m_inst_mem, m_sign_ext, 0, 0, 16);

  //   func -> alu control
  bulkConnect(m_inst_mem, m_alu_ctrl, 0, m_alu_ctrl.funcStartID(), 6);

  // alu sources (src1 from register file, src 2 from register file or sign extender)
  bulkConnect(m_reg_file    , m_alu         , m_reg_file.regDataStartID(0) , m_alu.operandStartID(0)         , 32);
  bulkConnect(m_reg_file    , m_mux_alu_src , m_reg_file.regDataStartID(1) , m_mux_alu_src.operandStartID(0) , 32);
  bulkConnect(m_sign_ext    , m_mux_alu_src , 0                            , m_mux_alu_src.operandStartID(1) , 32);
  bulkConnect(m_mux_alu_src , m_alu         , 0                            , m_alu.operandStartID(1)         , 32);

  // data memomry inputs (address from alu, write data from register file)
  bulkConnect(m_alu      , m_data_mem , 0                            , m_data_mem.addressStartID()   , 32);
  bulkConnect(m_reg_file , m_data_mem , m_reg_file.regDataStartID(1) , m_data_mem.writeDataStartID() , 32);

  // register file write data (from alu or data memory)
  bulkConnect(m_alu            , m_mux_mem_to_reg , 0 , m_mux_mem_to_reg.operandStartID(0)  , 32);
  bulkConnect(m_data_mem       , m_mux_mem_to_reg , 0 , m_mux_mem_to_reg.operandStartID(1)  , 32);
  bulkConnect(m_mux_mem_to_reg , m_reg_file       , 0 , m_reg_file.writeDataStartID()       , 32);

  //--------------------------------------------
  // PC update cycle

  // pc and hardwired constants -> add 4 alu
  bulkConnect(m_pc            , m_alu_add_4, 0 , m_alu_add_4.operandStartID(0)  , 32);
  bulkConnect(m_const_4       , m_alu_add_4, 0 , m_alu_add_4.operandStartID(1)  , 32);
  bulkConnect(m_const_alu_add , m_alu_add_4, 0 , m_alu_add_4.controlStartID()   , 4 );

  // branching alu
  bulkConnect(m_alu_add_4     , m_alu_add_branch , 0 , m_alu_add_branch.operandStartID(0)     , 32);
  bulkConnect(m_sign_ext      , m_alu_add_branch , 0 , m_alu_add_branch.operandStartID(1) + 2 , 30);
  bulkConnect(m_const_00      , m_alu_add_branch , 0 , m_alu_add_branch.operandStartID(1)     , 2 );
  bulkConnect(m_const_alu_add , m_alu_add_branch , 0 , m_alu_add_branch.controlStartID()      , 4 );

  // mux add4 vs. branch
  bulkConnect(m_alu_add_4      , m_mux_branch , 0 , m_mux_branch.operandStartID(0) , 32);
  bulkConnect(m_alu_add_branch , m_mux_branch , 0 , m_mux_branch.operandStartID(1) , 32);

  // mux add4+branch vs. jump
  bulkConnect(m_mux_branch , m_mux_jump, 0  , m_mux_jump.operandStartID(0)     , 32);

  bulkConnect(m_const_00   , m_mux_jump, 0  , m_mux_jump.operandStartID(1)     , 2 );
  bulkConnect(m_inst_mem   , m_mux_jump, 0  , m_mux_jump.operandStartID(1) + 2 , 26);
  bulkConnect(m_alu_add_4  , m_mux_jump, 28 , m_mux_jump.operandStartID(1) + 28, 4 );

  // cycle back to pc
  bulkConnect(m_mux_jump , m_pc , 0 , 0 , 32);

  //--------------------------------------------
  // Control and ALU Control

  // beq and-gate (ctrl branch && alu zero)
  m_alu.addOutputComponent(m_alu.zeroID(), m_and_gate, 1);
  m_and_gate.addOutputComponent(0, m_mux_branch, m_mux_branch.controlID());

  // control lines
  m_ctrl.addOutputComponent( 0, m_mux_write_reg , m_mux_write_reg.controlID()  );
  m_ctrl.addOutputComponent( 1, m_mux_jump      , m_mux_jump.controlID()       );
  m_ctrl.addOutputComponent( 2, m_and_gate      , 0                          );
  m_ctrl.addOutputComponent( 3, m_data_mem      , m_data_mem.memReadID()       );
  m_ctrl.addOutputComponent( 4, m_mux_mem_to_reg, m_mux_mem_to_reg.controlID() );
  m_ctrl.addOutputComponent( 5, m_alu_ctrl      , m_alu_ctrl.aluOpStartID()    );
  m_ctrl.addOutputComponent( 6, m_alu_ctrl      , m_alu_ctrl.aluOpStartID() + 1);
  m_ctrl.addOutputComponent( 7, m_data_mem      , m_data_mem.memWriteID()      );
  m_ctrl.addOutputComponent( 8, m_mux_alu_src   , m_mux_alu_src.controlID()    );
  m_ctrl.addOutputComponent( 9, m_reg_file      , m_reg_file.writeControlID()  );

  // alu control lines
  bulkConnect(m_alu_ctrl, m_alu, 0, m_alu.controlStartID(), 4);


  //----------------------------------------------------------------------------
  // Load firt instruction address before runing processor
  for (int i = 0; i < 32; i++)
    m_pc.setInput(i, (InstructionMemory::START_ADDRESS >> i) & 1UL);

}


Processor::
~Processor() {}


void
Processor::
setLogger(Logger* logger)
{
  m_clock.setLogger(logger);
  m_pc.setLogger(logger);
  m_ctrl.setLogger(logger);
  m_alu_ctrl.setLogger(logger);
  m_alu_add_4.setLogger(logger);
  m_alu_add_branch.setLogger(logger);
  m_alu.setLogger(logger);
  m_and_gate.setLogger(logger);
  m_mux_write_reg.setLogger(logger);
  m_mux_alu_src.setLogger(logger);
  m_mux_mem_to_reg.setLogger(logger);
  m_mux_branch.setLogger(logger);
  m_mux_jump.setLogger(logger);
  m_sign_ext.setLogger(logger);
  m_inst_mem.setLogger(logger);
  m_reg_file.setLogger(logger);
  m_data_mem.setLogger(logger);
}


void
Processor::
step()
{
  m_clock.tick();
}


void
Processor::
run()
{
  while (!isFinished())
    m_clock.tick();
}


void
Processor::
bulkConnect(ProcessorComponent& c1,
            ProcessorComponent& c2,
            int line1_start,
            int line2_start,
            int n_lines)
{
  for (int i = 0; i < n_lines; i++)
    c1.addOutputComponent(i + line1_start, c2, i + line2_start);
}


bool
Processor::
isFinished()
{
  return m_pc.getInstructionAddress() == m_inst_mem.getLastAddress();
}
