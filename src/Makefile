OUT = s21_matrix_oop.a
OUT_DIR = build
TEST = test

all: $(OUT) $(TEST)

$(OUT):
	mkdir -p $(OUT_DIR)
	cmake . -B $(OUT_DIR)
	$(MAKE) -C $(OUT_DIR) s21_matrix_oop

$(TEST): $(OUT)
	$(MAKE) -C $(OUT_DIR) tests
	cd $(OUT_DIR) && ./tests

gcov_report:
ifeq ($(OS), Darwin)
	g++ --coverage tests/test_matrix.cc tests/test_runner.cc -o s21_matrix_tests s21_matrix_oop.cc `pkg-config --cflags --libs check -lgtest`
	./s21_matrix_tests
	gcov s21_matrix_tests-s21_matrix_oop.gcda
	lcov -t "s21_matrix_tests" -o s21_matrix_tests.info -c -d ./ --no-external
	genhtml -o report s21_matrix_tests.info
	open ./report/index.html
else
	g++ --coverage tests/test_matrix.cc tests/test_runner.cc -o s21_matrix_tests s21_matrix_oop.cc -lgtest -lcheck -pthread -lrt -lm -lsubunit -s
	./s21_matrix_tests
	gcov s21_matrix_tests-s21_matrix_oop.gcda
	lcov -t "s21_matrix_tests" -o s21_matrix_tests.info -c -d ./ --no-external
	genhtml -o report s21_matrix_tests.info
	xdg-open ./report/index.html
endif

clean:
	rm -rf $(OUT_DIR)
	-rm -rf *.o && rm -rf *.gcno && rm -rf *.exec
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/