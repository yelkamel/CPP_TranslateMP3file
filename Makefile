include .Makefile.rules

.PHONY: doc check Changelog ${OUTFILES}

.Makefile.rules:
	./configure

all:
	$(CFLAGS) -lboost_system -lboost_filesystem src/main.cc src/opt/option.cc -o ${OUTFILES}

changelog: Changelog

Changelog:
	git log --all --stat --pretty=medium --graph --color --source \
		--full-history	--abbrev-commit --relative-date > Changelog

clean:
	find -name "*[~#]" -delete
	rm -f .Makefile.rules
	rm -f Changelog
	rm -rf $(DISTDIR)
	rm -rf $(TARBALL)
	rm -f $(OUTFILES)

distclean: clean
	rm -f $(OUTFILES)
	rm -rf doc/{doxyfile,ast.png,ast.dot}
	rm -rf lib
	rm -f .42sh_history
	rm -f .Makefile.rules
	rm -f src/gui/gui
	rm -f src/gui/Makefile
	find . -name "*.o" -exec rm -f {} \;
	find . -name "moc_*.cpp" -exec rm -f {} \;

doc:
	mkdir -p doc
	doxygen doc/.doxyfile
	cd doc/doxygen/latex && make


dist: distclean Changelog $(DISTDIR)
	cp -r src/ doc/\
	Makefile configure TODO AUTHORS README CMakeLists.txt Changelog\
	test/ $(DISTDIR)
	tar cvjf $(TARBALL) $(DISTDIR)
	rm -rf $(DISTDIR)

$(DISTDIR):
	rm -rf $(DISTDIR)
	mkdir -p $(DISTDIR)

distcheck: dist
	tar xvf $(TARBALL)
	cd $(DISTDIR) && make check
