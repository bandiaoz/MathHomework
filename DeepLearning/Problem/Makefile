.PHONY: ctan doc example install save test

example:
	latexmk -xelatex example.tex

ctan:
	l3build ctan

doc:
	latexmk -xelatex *-doc.tex

install:
	l3build install

save:
	bash tools/l3build-save.sh

test:
	l3build check
