#include "ASMParser.h"

using namespace std;

vector<Instruction>
ASMParser::
operator() (string _file_name)
{
  vector<Instruction> instructions;

  Instruction i;

  // Create ifstream
  ifstream in(_file_name);
  if(!in)
    throw invalid_argument( string("File does not exist: ") + _file_name );

  // Parser file
  int line_number = 0;
  string line;
  while( getline(in, line) )
  {
    line_number++;

    string opcode("");
    string operand[80];
    int operand_count = 0;

    getTokens(line, opcode, operand, operand_count);

    if(opcode.length() == 0)
      continue;

    Opcode o = opcodes.getOpcode(opcode);
    if(o == UNDEFINED){
      // invalid opcode specified
      cerr << _file_name << ":" << line_number
           << "Syntax error, skip to next line"  << endl
           << "  " << line << endl;
      continue;
    }

    bool success = getOperands(i, o, operand, operand_count);
    if(!success){
      cerr << _file_name << ":" << line_number
           << "Syntax error, skip to next line"  << endl
           << "  " << line << endl;
      continue;
    }

    i.setString(line);
    string encoding = encode(i);
    i.setEncoding(encoding);

    instructions.push_back(i);
  }

  return instructions;
}

void ASMParser::getTokens(string line,
             string &opcode,
             string *operand,
             int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands,
  // checking for syntax errors and counting the number of operands.
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos) // found a '#'
      line = line.substr(0,idx);

    int len = line.length();
    opcode = "";
    numOperands = 0;

    if (len == 0)
      return;

    int p = 0; // position in line

    // line.at(p) is whitespace or p >= len
    while (p < len && isWhitespace(line.at(p)))
      p++;
    // opcode starts
    while (p < len && !isWhitespace(line.at(p)))
    {
      opcode = opcode + line.at(p);
      p++;
    }
    // for(int i = 0; i < 3; i++){
    int i = 0;
    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
        p++;

      // operand may start
      bool flag = false;
      while (p < len && !isWhitespace(line.at(p)))
      {
        if(line.at(p) != ','){
          operand[i] = operand[i] + line.at(p);
          flag = true;
          p++;
        }
        else{
          p++;
          break;
        }
      }
      if(flag == true){
        numOperands++;
      }
      i++;
    }

    if (numOperands == 0)
      return;
    idx = operand[numOperands-1].find('(');
    string::size_type idx2 = operand[numOperands-1].find(')');

    if (idx == string::npos || idx2 == string::npos ||
        ((idx2 - idx) < 2 ))
    { // no () found
    }
    else
    { // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);

      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }

    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
  /*int len = s.length();
  if (len == 0) return false;
  if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
  {
    // check remaining characters
    for (int i=1; i < len; i++)
    {
        if (!isdigit(s.at(i))) return false;
    }
    return true;
  }
  return false;*/
  return true;
}


unsigned long ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
  return stoul(s, 0, 0);
}


bool ASMParser::getOperands(Instruction &i, Opcode o,
          string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands,
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o)) {
    cerr << "Op count: " << operand_count << " [" << opcodes.numOperands(o) << "]" << endl;
    return false;
  }

  int rs, rt, rd;
  unsigned long imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1)
  {
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1)
  {
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;
  }

  if(rd_p != -1)
  {
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;
  }

  if(imm_p != -1)
  {
    imm = cvtNumString2Number(operand[imm_p]);
  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  InstType type = opcodes.getInstType(i.getOpcode());
  if (type == RTYPE)
    return encodeRType(i);
  else if (type == ITYPE)
    return encodeIType(i);
  else
    return encodeJType(i);
}

string ASMParser::encodeRType(Instruction& i) {
  // Format: Opcode - rs - rt - rd - shamt - funct
  string s = opcodes.getOpcodeField(i.getOpcode()); // opcode
  s += numberToBinary( i.getRS(), 5 ); // rs
  s += numberToBinary( i.getRT(), 5 ); // rt
  s += numberToBinary( i.getRD(), 5 ); // rd
  s += numberToBinary( i.getImmediate(), 5 ); // shamt
  s += opcodes.getFunctField(i.getOpcode());  // funct
  return s;
}

string ASMParser::encodeIType(Instruction& i) {
  // Format: Opcode - rs - rt - immediate
  string s = opcodes.getOpcodeField(i.getOpcode()); // opcode
  s += numberToBinary( i.getRS(), 5 ); // rs
  s += numberToBinary( i.getRT(), 5 ); // rt
  unsigned long imm = i.getImmediate();
  if ( i.getOpcode() == BEQ) {
    if ( imm >> 15 )
      imm |= (~0xFFFFul);
    s += numberToBinary( imm >> 2, 16);
  }
  else
    s += numberToBinary( i.getImmediate(), 16 ); // immediate

  return s;
}

string ASMParser::encodeJType(Instruction& i) {
  // Format: Opcode - label immediate
  string s = opcodes.getOpcodeField(i.getOpcode()); // opcode
  s += numberToBinary( i.getImmediate() >> 2, 26 ); // label (shift 2 bits to the right)
  return s;
}
