#include "stack-vm.h"

using namespace std;

int main(int argc, char** argv) {
  FILE *f;
  StackVM stackVM;
  VirtualMachine vm;
  bool verbose = false;

  if (argc > 2) {
    if (argv[2][0] == '-' && argv[2][1] == 'v') {
      verbose = true;
    }
  }

  stackVM.LoadProgram(&vm, argv[1]);
  stackVM.RunMachine(&vm, verbose);

  return 0;
}
