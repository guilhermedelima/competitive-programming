SRCDIR=src
BINDIR=bin
RSCDIR=resources

CC=g++
CFLAGS=-W -Wall -pedantic -ansi

####### TARGET ########

.SECONDARY:

$(BINDIR)/%: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

c-%: $(BINDIR)/%
	@echo compiling

n-%:
	@echo creating new files
	touch $(SRCDIR)/$*.cpp $(RSCDIR)/$*.txt
	gedit $(SRCDIR)/$*.cpp $(RSCDIR)/$*.txt 2>>/dev/null 1>&2 &

%: $(BINDIR)/% $(RSCDIR)/%.txt
	@cat $(RSCDIR)/$*.txt | ./$<

clean:
	rm -f *~
	rm -f *.out
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*~
	rm -f $(RSCDIR)/*~
