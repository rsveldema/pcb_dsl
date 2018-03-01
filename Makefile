


all:
	(cd src; make)
	(cd examples; make)

clean:
	(cd src; make clean)
	(cd examples; make clean)

c:
	python3 setup.py build_ext --inplace
