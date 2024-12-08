all: *.cpp
	g++ *.cpp -o rectangle -lsfml-graphics -lsfml-window -lsfml-system -lcurl -I./l

clean:  
	rm -f *.o
