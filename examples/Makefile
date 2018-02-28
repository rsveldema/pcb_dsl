


all: clean
	python3 ../src/generate.py sampler.edsl
	dot -Tpdf model.dot > model.pdf


clean:
	rm -f model.dot best-iteration* clone* *.png out.* *.svg *.pdf
	rm -f *.dot
