
.PHONY: lib
lib: src/vec.c src/mat.c src/transform.c
	gcc -Iinclude -Wall -Wextra -fPIC -c src/vec.c -o obj/vec.o
	gcc -Iinclude -Wall -Wextra -fPIC -c src/mat.c -o obj/mat.o
	gcc -Iinclude -Wall -Wextra -fPIC -c src/transform.c -o obj/transform.o
	ar rvs lib/libglv.a obj/vec.o obj/mat.o obj/transform.o

test: lib/libglv.a tests/test.c
	gcc -Wall -Wextra tests/test.c lib/libglv.a -lm -o bin/test

clean: obj/*.o
	rm obj/*.o
