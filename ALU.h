#ifndef ALU_H_
#define ALU_H_

////////////////////////////////////////////////////////////////////////////////
/// Arithmetic and logic unit. Can perform the following opperations on two 
/// 32-bit signed integers (A and B):
/// - Addition
/// - Subtraction
/// - Comparision (less than, equal)
/// Input ID:
/// - A [ 0 - 31]
/// - B [32 - 63]
////////////////////////////////////////////////////////////////////////////////
class ALU : public ProcessorComponent
{
	public:
		ALU() {};

	private:
};

#endif // ALU_H_
