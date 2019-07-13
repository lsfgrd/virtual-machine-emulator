out: src/main.o src/stack-vm.o src/vm-startup.o
	g++ src/main.o src/stack-vm.o src/vm-startup.o -o VirtualMachine

main.o: src/main.cpp
	g++ -c src/main.cpp

stack-vm.o: src/stack-vm.cpp src/stack-vm.h
	g++ -c src/stack-vm.cpp

vm-startup.o: src/vm-startup.cpp
	g++ -c src/vm-startup.cpp

clean:
	rm *.o VirtualMachine