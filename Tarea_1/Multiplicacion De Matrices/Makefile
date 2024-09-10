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
	python3 Generador\ de\ matrices.py
	./Cubico
	./Cubico_op
	./Strassen


clean:
	rm -f $(TARGETS)
	rm -f Input.txt
	rm RCubico.txt
	rm RCubicoOp.txt
	rm RStrassen.txt