main:
	g++ -O2 *.cpp -o main -Wall

all:
	rm -f main
	g++ -O2 *.cpp -o main -Wall

test:
	rm -f main
	g++ -O2 *.cpp -o main -Wall
	./main ../cases/case-3 no
	
graph:
	rm -f main
	g++ -O2 *.cpp -o main -Wall
	./main ../cases/case-3 no
	dot -Tps teste.dot -o graph1.ps
	dot -Tps grau1.dot -o grau1.ps
