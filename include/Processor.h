#ifndef PROCESSOR_H_
#define PROCESSOR_H_


class Processor
{
  public:
    Processor();
    ~Processor();

    void step();

    void run();

  private:
    Clock             m_clock;
    ProgramCounter    m_pc;
    Control           m_ctrl;
    ALUControl        m_alu_ctrl;
    ALU               m_alu_add_4;       ///< ALU increments PC by 4 
    ALU               m_alu_add_branch;  ///< ALU increases PC by branch address
    ALU               m_alu;             ///< ALU main
    ANDGate           m_and_gate;        ///
    HardwiredConstant const_alu_add;
    HardwiredConstant const_4;
    HardwiredConstant const_00;
    MUX               mux_write_reg;
    MUX               mux_alu_src;
    MUX               mux_mem_to_reg;
    MUX               mux_branch;
    MUX               mux_jump;
    SignExtender      sign_ext;
    InstructionMemory inst_mem;
    RegisterFile      reg_file;
    DataMemory        data_mem;
};

#endif // PROCESSOR_H_