CFLAGS += -c -g -Wall -Wextra -Wpedantic \
                  -Wformat=2 -Wno-unused-parameter \
                  -Wshadow -Wwrite-strings -Wstrict-prototypes \
                  -Wold-style-definition -Wredundant-decls \
                  -Wnested-externs -Wmissing-include-dirs \
                  -Wjump-misses-init -Wlogical-op -O2

SRC += ../src/
LIB += $(SRC)/lib/

FILES += $(SRC)/temple.c \
		 $(LIB)/agram.c $(LIB)/cipher.c $(LIB)/words.c

.PHONY: build clean

build: temple
	@rm -rf *.o

temple: magic_obj_files
	@gcc *.o -o temple

magic_obj_files:
	@gcc $(CFLAGS) $(FILES)

clean:
	@find . -type f -name "*.o" -exec rm -rf {} \;
	@rm -rf output temple