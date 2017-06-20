
CXX = clang++
CXXFLAGS = -w -Wall -std=c++11
DEPS = neuron.h layer.h neuralnet.h
OBJ = neuron.o layer.o neuralnet.o main.o
OUTFILE = NN_Test
DELCMD = rm
EDITOR = gedit

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTFILE): $(OBJ)
	$(CXX) -o $@ $^

neuron.o: 		neuron.h
layer.o: 			layer.h
neuralnet.o: 	neuralnet.h
main.o: 			neuron.h layer.h neuralnet.h

clean:
	$(DELCMD) $(OBJ) $(OUTFILE)

run:
	./$(OUTFILE)
	$(EDITOR) neuralnet.code&
	$(EDITOR) neuralnet.info&

.PHONY: clean run
