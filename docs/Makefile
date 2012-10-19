all:
	# Making manually-written docs.
	for file in `ls *.tex`; do pdflatex $$file; done;

	# TODO Making Doxygen-latex docs.

	# Creating directory for docs.
	rm -rf pdf/
	mkdir pdf/
	mv *.pdf pdf/

clean:
	rm -rf docs *.log *.aux *.pdf
