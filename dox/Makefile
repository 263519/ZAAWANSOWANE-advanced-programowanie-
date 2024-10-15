__start__:
	doxygen Doxyfile 2> doxy.log
	less -P " Aby zakonczyc, nacisnij klawisz Q " doxy.log
	@echo
	@echo " Wygenerowana dokumentacja znajduje sie w katalogu: doc/html"
	@echo


clean:
	rm -fr doc/html doxy.log

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
