main:
	g++ -O2 *.cpp -o main -Wall

all:
	rm -f main
	g++ -O2 *.cpp -o main -Wall

graph:
	rm -f main
	g++ -O2 *.cpp -o main -Wall
	./main ../cases/case-4 no
	dot -Tps teste.dot -o graph1.ps
	dot -Tps spanning.dot -o graph2.ps
