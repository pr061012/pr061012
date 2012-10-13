all:
	# Making manually-written docs.
	make convention.pdf

	# TODO Making Doxygen-latex docs.

	# Clean up.
	rm *.log *.aux

convention.pdf: convention.tex
	pdflatex convention.tex

clean:
	rm -f *.log *.aux *.pdf
