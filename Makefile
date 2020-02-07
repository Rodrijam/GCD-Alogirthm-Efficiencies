
algprog.x: main.cpp
	g++ -o algprog main.cpp -lboost_iostreams -lboost_system -lboost_filesystem

clean:
	rm -fr scatter_plots/*.png algprog