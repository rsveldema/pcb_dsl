


all: clean
	#python3  -m cProfile ../src/generate.py sampler.edsl
	python3 ../src/generate.py sampler1.edsl
	dot -Tpdf model.dot > model.pdf


clean:
	rm -f model.dot best-iteration* clone* *.png out.* *.svg *.pdf
	rm -f *.dot
