#include "stack-vm.h"
using namespace std;

void StackVM::Halt(VirtualMachine* vm) {
  vm -> halt = true;
  cout << "The program sent a stop signal.";
}

void StackVM::Load(VirtualMachine* vm, int R, int mem_pos) {
  vm -> gpr[R] = vm -> memory[mem_pos + vm -> pc];
  cout << vm -> gpr[R] << endl;
};

void StackVM::Store(VirtualMachine* vm, int R, int mem_pos) {
  vm -> memory[mem_pos + vm -> pc] = vm -> gpr[R];
};

void StackVM::Read(VirtualMachine* vm, int R) {
  cout << "Enter a value: " << endl;
  scanf("%d", &vm -> gpr[R]);
};

void StackVM::Write(VirtualMachine* vm, int R) {
  // cout << "Write:" << endl;
  cout << vm -> gpr[R] << endl;

  printf("%d\n", vm -> gpr[R]);
}

void StackVM::Copy(VirtualMachine* vm, int R1, int R2) {
  vm -> gpr[R1] = vm -> gpr[R2];
  int result = vm -> gpr[R1];
  UpdatePSW(vm, result);
}

void StackVM::Push(VirtualMachine* vm, int R) {
  vm -> sp--;
  vm -> memory[vm -> sp] = vm -> gpr[R];
}

void StackVM::Pop(VirtualMachine* vm, int R) {
  vm -> gpr[R] = vm -> memory[vm -> sp];
  vm -> sp++;
}

void StackVM::Jump(VirtualMachine* vm, int mem_pos, Opcode op) {
  switch (op) {
    case JUMP:
      Branch(vm, mem_pos);
      break;
    case JZ:
      if (vm -> psw[0] == 1) { // jumps if zero
        Branch(vm, mem_pos);
      }
      break;
    case JNZ:
      if (!(vm -> psw[0] == 1)) { // jumps if NOT zero
        Branch(vm, mem_pos);
      }
      break;
    case JN:
      if (vm -> psw[1] == 1) { // jumps if negative
        Branch(vm, mem_pos);
      }
      break;
    case JNN:
      if (!(vm -> psw[1] == 1)) { // jumps if positive
        Branch(vm, mem_pos);
      }
      break;
  }
}

void StackVM::Call(VirtualMachine* vm, int mem_pos) {
  vm -> sp--;
  vm -> memory[vm -> sp] = vm -> sp;
  Branch(vm, mem_pos);
}

void StackVM::Branch(VirtualMachine* vm, int mem_pos) {
  vm -> pc += mem_pos;
}

void StackVM::Ret(VirtualMachine* vm) {
  vm -> pc = vm -> memory[vm -> sp];
}

void StackVM::BooleanOperations(VirtualMachine* vm, int R1, int R2, Opcode op) {
  int result;

  switch (op) {
    case AND:
      result = vm -> gpr[R1] & vm -> gpr[R2];
      break;
    case OR:
      result = vm -> gpr[R1] | vm -> gpr[R2];
      break;
    case NOT:
      result = !(vm -> gpr[R1]);
      break;
    case XOR:
      result = vm -> gpr[R1] ^ vm -> gpr[R2];
      break;
  }

  vm -> gpr[R1] = result;

  UpdatePSW(vm, result);
}

void StackVM::ArithmeticOperations(VirtualMachine* vm, int R1, int R2, Opcode op) {
  int result;

  switch (op) {
    case ADD:
      result = vm -> gpr[R1] + vm -> gpr[R2];
      break;
    case SUB:
      result = vm -> gpr[R1] - vm -> gpr[R2];
      break;
    case MUL:
      result = vm -> gpr[R1] * vm -> gpr[R2];
      break;
    case DIV:
      result = vm -> gpr[R1] / vm -> gpr[R2];
      break;
    case MOD:
      result = vm -> gpr[R1] % vm -> gpr[R2];
      break;
  }

  vm -> gpr[R1] = result;
  cout << "RESULT:  " <<  vm -> gpr[R1] << endl;

  UpdatePSW(vm, result);
}

void StackVM::Compare(VirtualMachine* vm, int R1, int R2) {
  int result = vm -> gpr[R1] - vm -> gpr[R2];
  UpdatePSW(vm, result);
}

void StackVM::Test(VirtualMachine* vm, int R1, int R2) {
  int result = vm -> gpr[R1] & vm -> gpr[R2];
  UpdatePSW(vm, result);
}

void StackVM::UpdatePSW(VirtualMachine* vm, int result) {
  if (result == 0) {
    vm -> psw[0] = 1;
    vm -> psw[1] = 0;
  } else if (result < 0) {
    vm -> psw[0] = 0;
    vm -> psw[1] = 1;
  } else {
    vm -> psw[0] = 0;
    vm -> psw[0] = 0;
  }
}