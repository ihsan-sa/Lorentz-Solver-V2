
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
	pip install pandas
	pip install numpy
	pip install csv	

clean: 
	-rm -rf compiled_files
	-mkdir other_config_files
	-mv *.txt other_config_files
	-mv ./other_config_files/config.txt .
	-rm data.csv
	-rm a.out
	
compile_test: ./numerical_simulation/test.cpp ./numerical_simulation/vector.cpp ./numerical_simulation/object.cpp ./numerical_simulation/space.cpp ./numerical_simulation/automation.cpp ./numerical_simulation/config.cpp
	
	make clean

	mkdir compiled_files

	g++ -c ./numerical_simulation/test.cpp -o ./compiled_files/test.o
	g++ -c ./numerical_simulation/vector.cpp -o ./compiled_files/vector.o
	g++ -c ./numerical_simulation/object.cpp -o ./compiled_files/object.o
	g++ -c ./numerical_simulation/space.cpp -o ./compiled_files/space.o
	g++ -c ./numerical_simulation/automation.cpp -o ./compiled_files/automation.o
	g++ -c ./numerical_simulation/config.cpp -o ./compiled_files/config.o

	g++ -g ./compiled_files/test.o  ./compiled_files/vector.o ./compiled_files/object.o ./compiled_files/space.o ./compiled_files/automation.o ./compiled_files/config.o -o ./compiled_files/compiled_test


comp_run_test: ./numerical_simulation/test.cpp ./numerical_simulation/vector.cpp ./numerical_simulation/object.cpp ./numerical_simulation/space.cpp ./numerical_simulation/automation.cpp ./numerical_simulation/config.cpp
	make compile_test
	./compiled_files/compiled_test


fresh: ./numerical_simulation/main.cpp ./numerical_simulation/vector.cpp ./numerical_simulation/object.cpp ./numerical_simulation/space.cpp ./numerical_simulation/automation.cpp ./numerical_simulation/config.cpp
	make clean
	make compiled_solver

