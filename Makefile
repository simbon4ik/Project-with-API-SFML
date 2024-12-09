all: *.cpp
	g++ *.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lcurl -I./

clean:  
	rm -f *.o
