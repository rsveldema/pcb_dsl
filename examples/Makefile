


all:
	rm -f model.dot model.pdf
	python3 ../src/generate.py sampler.edsl
	#sfdp -Tpdf model.dot > model.pdf
	dot -Tpdf model.dot > model.pdf
	inkscape -D -z --export-pdf=model2.pdf -w 1024 -h 1024 model.svg
	inkscape -D -z --export-pdf=cloned.pdf -w 1024 -h 1024 clone.svg 


clean:
	rm -f *.dot
