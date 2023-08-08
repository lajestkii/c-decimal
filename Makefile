GCC=gcc
STD_FLAGS=-Wall -Werror -Wextra -std=c11
LIB=-lcheck
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

TEST_FOLDER=tests/
FUNCTIONS_FOLDER=functions/

LIB_NAME = s21_decimal.a

UNIT_TEST=-o unit_test
GCOV_TEST=-o gcov_test

ifeq ($(shell uname), Linux)
 LIB +=-lpthread -lrt -lsubunit -lm
endif


all: ${LIB_NAME} test

${LIB_NAME}:
	${GCC} ${STD_FLAGS} -c ${wildcard ${FUNCTIONS_FOLDER}convertors/*.c}  ${wildcard ${FUNCTIONS_FOLDER}additional/*.c} ${wildcard ${FUNCTIONS_FOLDER}comparison/*.c} ${wildcard ${FUNCTIONS_FOLDER}arithmetic/*.c} ${wildcard ${FUNCTIONS_FOLDER}others/*.c}  
	ar rc ${LIB_NAME} *.o
	ranlib ${LIB_NAME}
	rm *.o

clean: 
	rm -rf report a.out unit_test gcov_test *.gcda *.gcno *.info ${LIB_NAME} *.o

test: ${LIB_NAME}
	${GCC} ${STD_FLAGS} ${UNIT_TEST} ${wildcard ${TEST_FOLDER}*.c} ${LIB_NAME} ${LIB}
	./unit_test
	rm ${LIB_NAME}
	rm unit_test

valgrind_test: ${LIB_NAME}
	${GCC} ${STD_FLAGS} ${UNIT_TEST} ${wildcard ${TEST_FOLDER}*.c} ${LIB_NAME} ${LIB}
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --leak-check=full --track-origins=yes --log-file=valgrind-out.txt --show-leak-kinds=all ./unit_test
	rm ${LIB_NAME}
	rm unit_test
	
gcov_report: 
	${GCC} ${STD_FLAGS} ${GCOV_FLAGS} --coverage ${wildcard ${FUNCTIONS_FOLDER}convertors/*.c}  ${wildcard ${FUNCTIONS_FOLDER}additional/*.c} ${wildcard ${FUNCTIONS_FOLDER}comparison/*.c} ${wildcard ${FUNCTIONS_FOLDER}arithmetic/*.c} ${wildcard ${FUNCTIONS_FOLDER}others/*.c} ${GCOV_TEST} ${wildcard ${TEST_FOLDER}*.c} ${LIB}
	./gcov_test
	lcov -t "stest" -o s21_test.info -c -d . -no-external
	genhtml -o report s21_test.info
	open ./report/index.html
	rm gcov_test


check_clang_format:
	mv ../materials/linters/.clang-format .
	clang-format -n functions/additional/*.c
	clang-format -n functions/arithmetic/*.c
	clang-format -n functions/comparison/*.c
	clang-format -n functions/convertors/*.c
	clang-format -n functions/others/*.c
	clang-format -n tests/*.c
	clang-format -n tests/*.h
	clang-format -n s21_decimal.h
	mv .clang-format ../materials/linters/

fix_clang_format:
	mv ../materials/linters/.clang-format .
	clang-format -i functions/additional/*.c
	clang-format -i functions/arithmetic/*.c
	clang-format -i functions/comparison/*.c
	clang-format -i functions/convertors/*.c
	clang-format -i functions/others/*.c
	clang-format -i tests/*.c
	clang-format -i tests/*.h
	clang-format -i s21_decimal.h
	mv .clang-format ../materials/linters/
