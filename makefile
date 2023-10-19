COMPILATEUR=gcc
EXEC=main
SOURCE=src/main
GLOBAL=src/Global
TOOLS=src/Tools/Tools
STRING=src/String/String
BUILTIN=src/Builtin/Builtin
PROCESSUS=src/Processus/Processus
SIGNAL=src/Signal/Signal
TASKS=src/Task/Tasks



all: prog clean

prog: main.o Tools.o String.o Builtin.o Processus.o Signal.o Tasks.o
	gcc *.o -o $(EXEC)

main.o: $(SOURCE).c $(GLOBAL).h $(TOOLS).h $(STRING).h $(SIGNAL).h $(TASKS).h
	gcc -g -Wall -c $(SOURCE).c


Tools.o: $(TOOLS).c $(TOOLS).h
	gcc -g -Wall -c $(TOOLS).c

String.o: $(STRING).c $(STRING).h $(TOOLS).h
	gcc -g -Wall -c $(STRING).c

Builtin.o: $(BUILTIN).c $(BUILTIN).h $(TOOLS).h $(GLOBAL).h
	gcc -g -Wall -c $(BUILTIN).c

Processus.o: $(PROCESSUS).c $(PROCESSUS).h
	gcc -g -Wall -c $(PROCESSUS).c

Signal.o: $(SIGNAL).c $(SIGNAL).h $(PROCESSUS).h
	gcc -g -Wall -c $(SIGNAL).c

Tasks.o: $(TASKS).c $(TASKS).h $(TOOLS).h $(SIGNAL).h $(PROCESSUS).h $(BUILTIN).h
	gcc -g -Wall -c $(TASKS).c

clean:
	rm -rf *.o


