/*
 * Virtual Machine Simulator
 * Author: lsfgrd - Laís Figueiredo
 * Initially written for a university course
 * Software Básico - 2019/01 - UFMG
 */

#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <fstream>

#define MEMSIZE 1000 // machine's memory size

typedef struct VirtualMachine {
  int memory[MEMSIZE];
  bool halt;
  int pc, sp, psw[2]; // specifc purpose registers
  int gpr[4]; // general purpose registers
} VirtualMachine;


enum Opcode {
  HALT = 0,
  LOAD = 1,
  STORE = 2,
  READ = 3,
  WRITE = 4,
  COPY = 5,
  PUSH = 6,
  POP = 7,
  JUMP = 8,
  JZ = 9,
  JNZ = 10,
  JN = 11,
  JNN = 12,
  CALL = 13,
  RET = 14,
  AND = 15,
  OR = 16,
  NOT = 17,
  XOR = 18,
  ADD = 19,
  SUB = 20,
  MUL = 21,
  DIV = 22,
  MOD = 23,
  CMP = 24,
  TST = 25
};

class StackVM {
  public:
  void Halt(VirtualMachine* vm);
  void Load(VirtualMachine* vm, int R, int mem_pos);
  void Store(VirtualMachine* vm, int R, int mem_pos);
  void Read(VirtualMachine* vm, int R);
  void Write(VirtualMachine* vm, int R);
  void Copy(VirtualMachine* vm, int R1, int R2); // updates psw (how?)
  void Push(VirtualMachine* vm, int R);
  void Pop(VirtualMachine* vm, int R);
  void Jump(VirtualMachine* vm, int mem_pos, Opcode op);
  void Call(VirtualMachine* vm, int mem_pos);
  void Ret(VirtualMachine* vm);
  void BooleanOperations(VirtualMachine* vm, int R1, int R2, Opcode op);
  void ArithmeticOperations(VirtualMachine* vm, int R1, int R2, Opcode op);
  void Compare(VirtualMachine* vm, int R1, int R2);
  void Test(VirtualMachine* vm, int R1, int R2);
  void UpdatePSW(VirtualMachine* vm, int result);
  void Branch(VirtualMachine* vm, int mem_pos);
  void LoadProgram(VirtualMachine* vm, char* file);
  void RunMachine(VirtualMachine* p, bool verbose);
  void IncrementPC(VirtualMachine* vm);
  void OneOperand(VirtualMachine* vm, int& OP1);
  void TwoOperands(VirtualMachine* vm, int& OP1, int& OP2);
  void Verbose(VirtualMachine* vm, Opcode opcode);
};

#endif