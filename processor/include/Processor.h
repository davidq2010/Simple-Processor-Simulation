#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "ALU.h"
#include "ALUControl.h"
#include "ANDGate.h"
#include "Clock.h"
#include "Control.h"
#include "DataMemory.h"
#include "HardwiredConstant.h"
#include "InstructionMemory.h"
#include "Logger.h"
#include "MUX.h"
#include "ProgramCounter.h"
#include "RegisterFile.h"
#include "SignExtender.h"

// STL
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Processor
/// @brief Builds the processor
///
/// @details
/// Input lines:
///   ALUOp     [1 - 0]
///   func      [7 - 2]
/// Output lines:
///   control   [3 - 0]
///
/// Input - output mapping:
///   ALUOp   func             ALU Action        Output
///
///    00    XXXXXX    Add (for LW, SW, ADDI)     0010
///    01    XXXXXX    Subtract (for BEQ)         0110
///    10    100000    R-type, Add                0010
///    10    100010    R-type, Substract          0110
///    10    101010    R-type, Set on less than   0111
////////////////////////////////////////////////////////////////////////////////
class Processor
{
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructor/Destructor
    /// @{
    ///
    /// @param _instructions Vector of binary-encoded ASM instructions;
    /// instructions always start at 0x400'000
    /// @param _register_data Vector of starting register values
    /// @param _memory_data Vector of starting data memory values
    /// @param _memory_start_address Starting address of data memory values;
    /// allows us to correspond offsets to other addresses in data memory
    Processor(std::vector<unsigned long> _instructions,
              std::vector<unsigned long> _register_data,
              std::vector<unsigned long> _memory_data,
              unsigned long _memory_start_address);

    ~Processor();

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    void setLogger(Logger* logger);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Executes a single instruction
    ////////////////////////////////////////////////////////////////////////////
    void step();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Runs the whole program
    ////////////////////////////////////////////////////////////////////////////
    void run();

    bool isFinished();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Used for logging the instruction with Logger
    /// @details Compares the upcoming instruction address to the start address
    /// to determine which index in vector of binary instructions to retrieve
    /// the instruction from, which is logged in its toString form
    ////////////////////////////////////////////////////////////////////////////
    unsigned long getNextInstructionAddress() { return m_pc.getInstructionAddress(); }


  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Processor Components
    /// @{

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

    /// @}
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    /// @brief Connect component 1's output lines to component 2's input lines
    /// @param c1            component 1
    /// @param c2            component 2
    /// @param line_1_start  the first line of component 1 to connect
    /// @param line_2_start  the first line of component 2 to connect
    /// @param n_lines       number of lines to connect
    ////////////////////////////////////////////////////////////////////////////
    void bulkConnect(ProcessorComponent& c1,
                     ProcessorComponent& c2,
                     int line1_start,
                     int line2_start,
                     int n_lines);
};

#endif // PROCESSOR_H_
