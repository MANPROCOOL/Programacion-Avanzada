CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wpedantic
CPPFLAGS += -I.. -I.

NUMEROS := 01 05 06 07 08 18 21 24
FUENTES := $(foreach n,$(NUMEROS),$(wildcard $(n)_*.cpp))
COLA := 08 21 24
.DEFAULT_GOAL := ayuda
.NOTPARALLEL:

.PHONY: ayuda clean $(NUMEROS)

ayuda:
	@echo "Uso: make NN. Ejercicios disponibles: $(NUMEROS)"
	@echo "make clean elimina los ejecutables de los ejercicios."

clean:
	$(RM) $(FUENTES:.cpp=)

$(NUMEROS): %:
	$(RM) $(FUENTES:.cpp=)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(filter $@_%,$(FUENTES)) ../tGrafo.cpp $(if $(filter $@,$(COLA)),../tCola.cpp) -o $(basename $(filter $@_%,$(FUENTES)))
