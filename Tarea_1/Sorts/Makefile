# Variables
CXX = g++
CXXFLAGS = -Wall -O2
TARGETS = OrdenadorBubbleSort OrdenadorQuickSort OrdenadorMergeSort OrdenadorImp

# Reglas de compilación
all: $(TARGETS)

OrdenadorBubbleSort: OrdenadorBubbleSort.cpp
	$(CXX) $(CXXFLAGS) -o $@ OrdenadorBubbleSort.cpp

OrdenadorQuickSort: OrdenadorQuickSort.cpp
	$(CXX) $(CXXFLAGS) -o $@ OrdenadorQuickSort.cpp

OrdenadorMergeSort: OrdenadorMergeSort.cpp
	$(CXX) $(CXXFLAGS) -o $@ OrdenadorMergeSort.cpp

OrdenadorImp: OrdenadorImp.cpp
	$(CXX) $(CXXFLAGS) -o $@ OrdenadorImp.cpp

# Regla para ejecutar los programas secuencialmente
run: all
	clear
	./OrdenadorBubbleSort
	./OrdenadorQuickSort
	./OrdenadorMergeSort
	./OrdenadorImp

# Limpieza de archivos binarios
clean:
	rm -f $(TARGETS)
