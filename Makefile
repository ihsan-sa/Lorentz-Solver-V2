

compiled_solver: ./numerical_simulation/main.cpp ./numerical_simulation/vector.cpp ./numerical_simulation/object.cpp ./numerical_simulation/space.cpp ./numerical_simulation/automation.cpp ./numerical_simulation/config.cpp

	mkdir compiled_files

	g++ -c ./numerical_simulation/main.cpp -o ./compiled_files/main.o
	g++ -c ./numerical_simulation/vector.cpp -o ./compiled_files/vector.o
	g++ -c ./numerical_simulation/object.cpp -o ./compiled_files/object.o
	g++ -c ./numerical_simulation/space.cpp -o ./compiled_files/space.o
	g++ -c ./numerical_simulation/automation.cpp -o ./compiled_files/automation.o
	g++ -c ./numerical_simulation/config.cpp -o ./compiled_files/config.o

	g++ ./compiled_files/main.o  ./compiled_files/vector.o ./compiled_files/object.o ./compiled_files/space.o ./compiled_files/automation.o ./compiled_files/config.o -o ./compiled_files/compiled_solver

	pip install manim
	pip install ffmpeg
	

clean: 
	rm -rf compiled_files
	rm data.csv
	