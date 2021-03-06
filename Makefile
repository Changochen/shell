shell: cp wc cmp
	g++ ./source/shell.cpp -o shell

cp:
	g++ ./source/cp.cpp -o ./bin/cp

wc:
	g++ ./source/wc.cpp -o ./bin/wc

cmp:
	g++ ./source/cmp.cpp -o ./bin/cmp

clean:
	rm ./bin/* shell
