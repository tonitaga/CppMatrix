CC = gcc -lstdc++
CFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -lgtest
SRC = s21_matrix_oop.cpp s21_matrix_private.cpp s21_matrix_operators.cpp
OBJ = s21_matrix_oop.o s21_matrix_private.o s21_matrix_operators.o
TEST = test.cpp
LIB = s21_matrix_oop.a
REPORT = GcovReport
OS := $(uname -s)



ifeq ($(OS), Darwin)
	CC+= -D OS_MAC
endif
ifeq ($(OS), Linux)
	CC+= -D OS_LINUX
	TESTFLAGS+= -lgmock -pthread
endif



all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(SRC) -c
	ar rcs $(LIB) $(OBJ)

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) $(TEST) $(LIB) $(TESTFLAGS) -o test -g
	@./test
	@rm ./test

clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf leaks
	@rm -rf *.gch
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf gcov_report



check: $(NAME)
	@echo -------------------CLANG_FORMAT------------------------
	@cppcheck $(SRC)
	@echo -------------------------------------------------------
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -style=file --dry-run --Werror $(SRC) $(TEST) *.cpp *.h
	@rm .clang-format
	@make leaks

leaks:
	@echo --------------------MEMORY_LEAKS-----------------------
	$(CC) $(CFLAGS) $(TEST) $(SRC) $(TESTFLAGS) -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks


gcov_report:
	$(CC) $(GCOVFLAGS) $(TEST) $(SRC) $(TESTFLAGS) -o $(REPORT)
	@chmod +x *
	@./GcovReport
	lcov --no-external -t "$(REPORT)" -o $(REPORT).info -c -d .
	genhtml -o report $(REPORT).info
	@rm -rf ./*.gcno ./*.gcda ./$(REPORT).*
	@open ./report/index.html
	@rm $(REPORT)
	@rm -rf *.dSYM

