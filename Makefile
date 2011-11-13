PREPROCESS=gcc -E -P -C -x c -iquote ./src
# -E : Stop after preprocessing.
# -P : Don't generate line markers (which confuse Javascript).
# -C : Don't discard comments.
# -x c : Treat the file as C code.
# -iquote ./src : Use ./src for the non-system include path.

all: sketches/morse/morse.h

%.h: %.cpp.in
	$(PREPROCESS) $< -o $@

