COMPILATEUR=gcc
EXEC=main
SOURCE=src/main
SOURCE1=src/Tools/Tools
SOURCE2=src/String/String
SOURCE3=src/Signal/Signal
SOURCE4=src/Task/Tasks
SOURCE5=src/Processus/Processus
SOURCE6=src/Colors/colors


all: prog clean

prog: main.o file1.o file2.o file3.o file4.o file5.o
	gcc *.o -o $(EXEC)

main.o: $(SOURCE).c $(SOURCE1).h $(SOURCE2).h $(SOURCE3).h $(SOURCE6).h
	gcc -g -Wall -c $(SOURCE).c


file1.o: $(SOURCE1).c $(SOURCE1).h
	gcc -g -Wall -c $(SOURCE1).c


file2.o: $(SOURCE2).c $(SOURCE2).h $(SOURCE1).h
	gcc -g -Wall -c $(SOURCE2).c
	
file5.o: $(SOURCE5).c $(SOURCE5).h
	gcc -g -Wall -c $(SOURCE5).c
	
file3.o: $(SOURCE3).c $(SOURCE3).h $(SOURCE5).h
	gcc -g -Wall -c $(SOURCE3).c
	
		
file4.o: $(SOURCE4).c $(SOURCE4).h $(SOURCE1).h $(SOURCE5).h
	gcc -g -Wall -c $(SOURCE4).c
	
clean:
	rm -rf *.o
	
	
