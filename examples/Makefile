


all:
	rm -f model.dot model.pdf
	python3 ../src/generate.py sampler.edsl
	#sfdp -Tpdf model.dot > model.pdf
	dot -Tpdf model.dot > model.pdf

clean:
	rm -f *.dot
