# Makefile for the spellchecking program by 14103216,14103235,14103239,14103241

COMPILER=g++
CFLAGS=-c
VERSION=-std=c++11

all: spellcheck

spellcheck: spellcheck.o bktree.o bloomfilter.o hashtables.o trie.o levenshtein.o
	$(COMPILER) spellcheck.o bktree.o bloomfilter.o hashtables.o trie.o levenshtein.o -o spellcheck

spellcheck.o : spellcheck.cpp bktree.h bloomfilter.h hashtables.h trie.h levenshtein.h
	$(COMPILER) $(CFLAGS) spellcheck.cpp $(VERSION)

bktree.o: bktree.cpp bktree.h levenshtein.h
	$(COMPILER) $(CFLAGS) bktree.cpp $(VERSION)

bloomfilter.o: bloomfilter.cpp bloomfilter.h
	$(COMPILER) $(CFLAGS) bloomfilter.cpp $(VERSION)

hashtables.o: hashtables.cpp hashtables.h
	$(COMPILER) $(CFLAGS) hashtables.cpp $(VERSION)

trie.o: trie.cpp trie.h levenshtein.h
	$(COMPILER) $(CFLAGS) trie.cpp $(VERSION)

levenshtein.o: levenshtein.cpp levenshtein.h
	$(COMPILER) $(CFLAGS) levenshtein.cpp $(VERSION)
	
clean:
	rm -rf *o spellcheck
