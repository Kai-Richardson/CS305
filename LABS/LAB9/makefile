all: isa isl ssa ssl qs ms

isa: arrayInsertionSort.c
	gcc -o isa arrayInsertionSort.c

isl: listInsertionSort.c
	gcc -o isl listInsertionSort.c

ssa: arraySelectionSort.c
	gcc -o ssa arraySelectionSort.c

ssl: listSelectionSort.c
	gcc -o ssl listSelectionSort.c

qs:  quicksort.c
	gcc -o qs quicksort.c

ms:  mergesort.c
	gcc -o ms mergesort.c

clean:
	/bin/rm -f isa isl ssa ssl qs ms
