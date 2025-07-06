.PHONY: run

run:
	python3 percep_main.py p22.dat test.dat 1.2 -7 2 0 weights-test-1.dat logs-test-1.dat
	python3 percep_main.py p22.dat test.dat 3.6 -7 2 0 weights-test-2.dat logs-test-2.dat
	python3 percep_main.py p22.dat test.dat 2.0 11 5 0 weights-test-3.dat logs-test-3.dat
	python3 plot-log2d.py logs-test-1.dat logs-test-2.dat logs-test-3.dat output.png

self:
	python3 percep_main.py mydata.dat mytest.dat 1.2 -7 2 0 weights-self-1.dat logs-self-1.dat
	python3 percep_main.py mydata.dat mytest.dat 3.6 -7 2 0 weights-self-2.dat logs-self-2.dat
	python3 percep_main.py mydata.dat mytest.dat 2.0 11 5 0 weights-self-3.dat logs-self-3.dat
	python3 plot-log3d.py logs-self-1.dat logs-self-2.dat logs-self-3.dat output-self.png