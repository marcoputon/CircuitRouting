main:
	rm -f main
	g++ -O2 *.cpp -o main -Wall

test-3:
	rm -f main
	g++ -O2 *.cpp -o main -Wall
	./main ../cases/case-3 no

image-3:
	rm -f main
	g++ -O2 *.cpp -o main -Wall
	./main ../cases/case-3 no
	dot -Tps out/grau1.dot -o out/grau1.ps

b-compile:
	rm -f bi1st
	g++ -O2 *.cpp -o bi1st -Wall

bi1st-compile:
	rm -f bi1st
	g++ -O2 bi1st.cpp lib/*.cpp -o bi1st -Wall

bi1st-execute:
	./bi1st ../cases/case-3 no
