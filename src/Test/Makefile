SHELL = /bin/sh 

GCC := g++ -Werror -Wextra -Wall --std=c++17 -lstdc++ -lm
SANITIZER :=  -fsanitize=address
SOURSE :=  ../app/fileparserfacade.cpp TestFileParser.cc
FLAGS_LCOV := -g -fprofile-arcs -ftest-coverage
FLAGS_GTEST := -lgtest -lgcov -pthread
OS = $(shell uname)

all: test
test: clean
	$(GCC) $(FLAGS_LCOV) $(SOURSE) $(FLAGS_GTEST) -o s21_test_file
	./s21_test_file
gcov_report: test #--ignore-errors mismatch 
	@lcov -t test -o rep.info -c -d .
	@genhtml -o report rep.info
	@rm -rf gcovreport gcovreport.info *.gcda *.gcno math_test.gcda math_test.gcno
	@open ./report/index.html
clean:
	rm -rf s21_test_file
	rm -rf *.o test *.a a.out *.gcno *.gcda s21_test_file.dSYM *.info report *.gch *.txt
check: test
	clang-format --style=Google -n $(shell find ../app/ -name '*.cc') $(shell find ../app/ -name '*.h') $(shell find ../app/ -name '*.cpp')
	clang-format --style=Google -i $(shell find ../app/ -name '*.cc') $(shell find ../app/ -name '*.h') $(shell find ../app/ -name '*.cpp')
ifeq ($(OS), Darwin)
	leaks --atExit -- ./s21_test_file
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_test_file
endif
