DOCNAME=xmlinterpreter

__start__:
	doxygen ${DOCNAME}.doxy 2> doxygen.log
	echo >> doxygen.log
	echo "Nacisnij Q, aby zakonczyc przegladanie" >> doxygen.log
	less doxygen.log

clean:
	rm -rf html latex doxygen.log

view:
	less doxygen.log

help:
	@echo
	@echo " Dodatkowe opcje:"
	@echo
	@echo "  clean - usuwa wygenerowana dokumentacje"
	@echo "  view  - uruchamia przegladanie logu"
	@echo "  help  - wyswietla niniejsza informacje"
	@echo
