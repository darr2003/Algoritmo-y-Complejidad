TARGETS = Cubico Cubico_op Strassen

all: $(TARGETS)

Cubico: Cubico.cpp
	g++ -Wall -o $@ Cubico.cpp

Cubico_op: Cubico_op.cpp
	g++ -Wall -o $@ Cubico_op.cpp

Strassen: Strassen.cpp
	g++ -Wall -o $@ Strassen.cpp

run: all
	clear
	./Cubico
	./Cubico_op
	./Strassen

runStrassen: Strassen
	clear
	./Strassen

clean:
	rm -f $(TARGETS)
