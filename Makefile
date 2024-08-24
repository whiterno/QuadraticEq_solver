Header := in_out/in_out.h QES_funcs/QES_funcs.h QES_structs.h terminal/terminal.h tests/tests.h useful/useful.h  consts.h cprint/cprint.h
Flags :=

a.out: obj/main.o obj/cprint.o obj/in_out.o obj/QES_funcs.o obj/terminal.o obj/tests.o obj/useful.o
	g++ obj/main.o obj/cprint.o obj/in_out.o obj/QES_funcs.o obj/terminal.o obj/tests.o obj/useful.o

obj/main.o: main.cpp $(Header)
	g++ -c $(Flags) main.cpp -o obj/main.o

obj/in_out.o: ./in_out/in_out.cpp $(Header)
	g++ -c $(Flags) ./in_out/in_out.cpp -o obj/in_out.o

obj/cprint.o: ./cprint/cprint.cpp $(Header)
	g++ -c $(Flags) ./cprint/cprint.cpp -o obj/cprint.o

obj/QES_funcs.o: ./QES_funcs/QES_funcs.cpp $(Header)
	g++ -c $(Flags) ./QES_funcs/QES_funcs.cpp -o obj/QES_funcs.o

obj/terminal.o: ./terminal/terminal.cpp $(Header)
	g++ -c $(Flags) ./terminal/terminal.cpp -o obj/terminal.o

obj/tests.o: ./tests/tests.cpp $(Header)
	g++ -c $(Flags) ./tests/tests.cpp -o obj/tests.o

obj/useful.o: ./useful/useful.cpp $(Header)
	g++ -c $(Flags) ./useful/useful.cpp -o obj/useful.o
