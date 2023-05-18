.DEFAULT_GOAL := all

all: clean hierarchyTree

hierarchyTree: hierarchyTree.c
	touch hierarchyTree.c
	gcc -o hierarchyTree hierarchyTree.c
	./hierarchyTree.exe

clean:
	rm *.exe

size:
	size hierarchyTree.exe