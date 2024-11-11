#+- SVN Keywords ----------------------------------------------------+
#|                                                                   |
#| $HeadURL: svn+ssh://bkreczmer@robrex.iiar.pwr.wroc.pl/home/bkreczmer/repos/GDiagUI/GDiagUI-software-qt4/trunk/gui-source/app-doctor/doc/Makefile $:
#|                                                                   |
#|    $Rev:: 67                                                    $:|
#|   $Date:: 2015-03-08 06:07:13 +0100 (Sun, 08 Mar 2015)          $:|
#| $Author:: bkreczmer                                             $:|
#|                                                                   |
#+-------------------------------------------------------------------+

PROJECT=serwer_graficzny
FILE=${PROJECT}
COMDIR=/tmp/${USER}/doc
TMPDIR=${COMDIR}/${PROJECT}
LOGFILE=${TMPDIR}/${FILE}.log
MAINPAGE=main.pag
__start_doxy__: doc
	less -P "(q - quit):" ${LOGFILE}

doc: ${TMPDIR}
	(cat ${FILE}.doxy; echo "HTML_OUTPUT = ${TMPDIR}/html";\
                  echo "OUTPUT_DIRECTORY = ${TMPDIR}";\
             ) | doxygen - 2> ${LOGFILE}; \
        echo;
	@echo
	@echo " Doc. dir: ${TMPDIR}/html"
	@echo


log:
	less -P "(q - quit):" ${LOGFILE}

${TMPDIR}:
	mkdir -p ${TMPDIR}

update:
	! grep "Last modification: `date +%Y.%m.%d`"\
                      res/pages/${MAINPAGE} > /dev/null
	cp res/pages/${MAINPAGE} res/pages/${MAINPAGE}.bak
	sed "s/Last modification:.*/Last modification: `date +%Y.%m.%d`/" \
           res/pages/${MAINPAGE} > res/pages/${MAINPAGE}.new
	mv res/pages/${MAINPAGE}.new res/pages/${MAINPAGE}

browse:  ${TMPDIR}/html
	#konqueror  ${TMPDIR}/html/index.html 2> /dev/null&
	falkon ${TMPDIR}/html/index.html 2> /dev/null&


clean:
	rm -rf ${TMPDIR}/html
	@echo   "  doc cleaned"

cleantotally: clean

help:
	@echo
	@echo "  Goals:"
	@echo "      doc  - documentation is created (the default goal),"
	@echo "      log  - log browsing,"
	@echo "     clean - documentation removing,"
	@echo "    browse - browse HTML documentation,"
	@echo "    update - a date of project modifcation is set to the current date"
	@echo
