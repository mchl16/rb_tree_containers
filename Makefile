SHELL=/bin/bash

CC=g++
CFLAGS_DEBUG=-g -Wall -Werror -std=c++2a
CFLAGS=-O2 -std=c++2a
TESTS=test_set_insert

default:
	$(CC) $(CFLAGS) main.cpp -o main.exe

debug:
	$(CC) $(CFLAGS_DEBUG) main.cpp -o main.exe

tests:
	@cnt_ok=0;
	@cnt_total=0;
	@echo "Testing started";
	@cd tests;
	i="test_set_insert"
	$(CC) $(CFLAGS_DEBUG) $$i.cpp -o $$i

dupa:
	for i in $(TESTS);
	do
		$(CC) $(CFLAGS_DEBUG) $i.cpp -o $i
		./($i)
		((++cnt_total))
		@if (($? == 0))
		@then
		@	echo "OK"
		@	((++cnt_ok))
		@else
		@	echo "Not OK"
		@fi
	@done
	@echo "Successful tests: $(cnt_ok)"
	@echo "Total tests: $(cnt_total)"

clean:
	rm -rf *.o *.exe