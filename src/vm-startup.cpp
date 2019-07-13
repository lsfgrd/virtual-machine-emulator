#include "stack-vm.h"
#include <vector>

using namespace std;

void StackVM::LoadProgram(VirtualMachine* vm, char* file) {
  char header_pointer;
  bool error = false;
  int ii = 0;

  int program_size, load_address, initial_stack_value, entry_point;

  ifstream infile(file);

  if (infile.good()) {
    string sLine;
    getline(infile, sLine);

    if (sLine != "MV-EXE") {
      cout << "Error: Invalid file. Executable files must start with a 'MV-EXE' line." << endl;
      vm -> halt = true;
      return;
    }

    infile >> program_size >> load_address >> initial_stack_value >> entry_point;

    while (!infile.eof()) {
      infile >> vm -> memory[ii];
      ii++;
    }

    infile.close();
  }

  vm -> halt = false;
}


void StackVM::RunMachine(VirtualMachine* vm, bool verbose) {
  vm -> psw[0] = 0;
  vm -> psw[1] = 0;
  Opcode opcode;
  int R1, R2, M = 0;

  while (!vm -> halt) {
    opcode = (Opcode) vm -> memory[vm -> pc];
    if (verbose) Verbose(vm, opcode);

    switch (opcode) {
      case HALT:
        Halt(vm);
        break;

      case LOAD:
        TwoOperands(vm, R1, M);
        Load(vm, R1, M);
        break;

      case READ:
        OneOperand(vm, R1);
        Read(vm, R1);
        // vm -> halt = true; // TODO: Remover
        break;

      case WRITE:
        OneOperand(vm, R1);
        Write(vm, R1);
        break;

      case COPY:
        TwoOperands(vm, R1, R2);
        Copy(vm, R1, R2);
        break;

      case PUSH:
        OneOperand(vm, R1);
        Push(vm, R1);

      case POP:
        OneOperand(vm, R1);
        Pop(vm, R1);
        break;

      case JUMP:
      case JZ:
      case JNZ:
      case JN:
      case JNN:
        OneOperand(vm, M);
        Jump(vm, M, opcode);
        break;

      case CALL:
        OneOperand(vm, M);
        Call(vm, M);
        break;

      case RET:
        Ret(vm);
        break;

      case AND:
      case OR:
      case XOR:
        TwoOperands(vm, R1, R2);
        BooleanOperations(vm, R1, R2, opcode);
        break;

      case NOT:
        OneOperand(vm, R1);
        BooleanOperations(vm, R1, R2, opcode);
        break;

      case ADD:
      case SUB:
      case MUL:
      case DIV:
      case MOD:
        TwoOperands(vm, R1, R2);
        ArithmeticOperations(vm, R1, R2, opcode);
        break;

      case CMP:
        TwoOperands(vm, R1, R2);
        Compare(vm, R1, R2);
        break;
        
      case TST:
        TwoOperands(vm, R1, R2);
        Test(vm, R1, R2);
        break;
    }
  }
}

void StackVM::IncrementPC(VirtualMachine* vm) {
  vm -> pc++;
}

void StackVM::OneOperand(VirtualMachine* vm, int& OP1) {
  IncrementPC(vm);
  OP1 = vm -> memory[vm -> pc];
  IncrementPC(vm);
}

void StackVM::TwoOperands(VirtualMachine* vm, int& OP1, int& OP2) {
  IncrementPC(vm);
  OP1 = vm -> memory[vm -> pc];
  IncrementPC(vm);
  OP2 = vm -> memory[vm -> pc];
  IncrementPC(vm);
}

void StackVM::Verbose(VirtualMachine* vm, Opcode opcode) {
  printf(
    "Curent operation: %d\n | PC: %d\n | SP: %d\n | PSW: %d\n | GPR[0]: %d\n | GPR[1]: %d\n | GPR[2]: %d\n | GPR[3]: %d\n | ",
    opcode,
    vm -> pc,
    vm -> sp,
    vm -> psw[0] + vm -> psw[1],
    vm -> gpr[0],
    vm -> gpr[1],
    vm -> gpr[2],
    vm -> gpr[3]);
}