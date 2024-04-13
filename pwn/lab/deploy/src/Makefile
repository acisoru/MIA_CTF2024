task: clean main.o dict.o scan.o sorts.o
	gcc main.o dict.o scan.o sorts.o -o task -lreadline -no-pie -fno-stack-protector 

main.o: main.c
	gcc -c main.c -no-pie -fno-stack-protector

dict.o: dict.c
	gcc -c dict.c -lreadline -no-pie -fno-stack-protector

scan.o: scan.c
	gcc -c scan.c -lreadline  -no-pie -fno-stack-protector

sorts.o:sorts.c
	gcc -c sorts.c -lreadline -no-pie -fno-stack-protector



clean:
	rm -rf *.o task
