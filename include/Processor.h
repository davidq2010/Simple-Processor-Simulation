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
    //------------------------------------------------------------------------
    // Processor Components
    Clock             m_clock;
    ProgramCounter    m_pc;
    Control           m_ctrl;
    ALUControl        m_alu_ctrl;
    ALU               m_alu_add_4;      ///< ALU increments PC by 4 
    ALU               m_alu_add_branch; ///< ALU increases PC by branch address
    ALU               m_alu;            ///< ALU main
    ANDGate           m_and_gate;       ///< And Control branch line with ALU zero line
    HardwiredConstant m_const_alu_add;  ///< Constant for add operation control for ALU
    HardwiredConstant m_const_4;        ///< Constant for the literal 4 
    HardwiredConstant m_const_00;       ///< Constant for the literal 00, used to shift left 2
    MUX               m_mux_write_reg;  ///< Choose rt or rd to write to
    MUX               m_mux_alu_src;    ///< Choose immediate or regiter data for ALU input
    MUX               m_mux_mem_to_reg; ///< Choose ALU result or Memory data to write back
    MUX               m_mux_branch;     ///< Choose PC+4 or PC+branch
    MUX               m_mux_jump;       ///< Choose PC or jump address
    SignExtender      m_sign_ext;
    InstructionMemory m_inst_mem;
    RegisterFile      m_reg_file;
    DataMemory        m_data_mem;
};

#endif // PROCESSOR_H_