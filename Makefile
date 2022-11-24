CC = g++ -std=c++17
FLAGS = -Wall -Wextra -Werror
GCOV_FLAG = -lgtest -pthread
MODEL_DIR = model
CONTROLLER_DIR = controller
BUILD_DIR = build
VIEW_DIR = view
APP_NAME = Maze
APP_FILE = Maze
APP_SRC_DIR = $(BUILD_DIR)/$(APP_NAME)
APP_DIR = $(HOME)/$(APP_NAME)/
ARCHIVE_NAME = Maze.zip
ARCHIVE_DIR = src/
MAZE_PRO_FILE = Maze.pro
TESTFILE = tests
MODEL_SOURCES=model/*.cpp
MODEL_HEADERS=model/*.h

tests: clean
	$(CC) $(FLAGS) $(MODEL_SOURCES) $(TESTFILE).cpp -o $(TESTFILE) $(GCOV_FLAG)
	./$(TESTFILE)
	@rm -f $(TESTFILE)

clean:
	rm -rf *.out *.o test *.gcno *.gcda *.gcov test.info report *.gch $(TESTFILE)

dvi:
	xdg-open maze_dvi/dvi.html

dist:
	rm -f $(HOME)/$(ARCHIVE_NAME)
	mkdir -p $(ARCHIVE_DIR)
	@cp -r Makefile $(MAZE_PRO_FILE) $(MODEL_DIR) $(VIEW_DIR) $(CONTROLLER_DIR) $(ARCHIVE_DIR)
	tar cvzf $(ARCHIVE_NAME) $(ARCHIVE_DIR)
	mv $(ARCHIVE_NAME) $(HOME)
	rm -rf $(ARCHIVE_DIR)

lcov:
	g++ --coverage $(MODEL_SOURCES) $(TESTFILE).cpp -o $(TESTFILE) $(GCOV_FLAG)
	./$(TESTFILE)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	xdg-open report/index.html

gcov_report: clean lcov

build: clean
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	cp -r $(MAZE_PRO_FILE) main.cpp $(MODEL_DIR) $(VIEW_DIR) $(CONTROLLER_DIR) $(VIEW_DIR)/mainwindow.ui $(BUILD_DIR)
	cd $(BUILD_DIR); qmake $(MAZE_PRO_FILE)
	cd $(BUILD_DIR); make

install: uninstall build
	mkdir -p $(APP_DIR)
	cp -rf $(BUILD_DIR)/$(APP_FILE) $(APP_DIR)
	rm -r $(BUILD_DIR)

uninstall:
	rm -rf $(BUILD_DIR)
	rm -rf $(APP_DIR)


clang:
	cp ../../materials/linters/.clang-format .
	clang-format -i model/*.cpp
	clang-format -i model/*.h

	clang-format -i controller/*.cpp
	clang-format -i controller/*.h

	clang-format -i view/*.cpp
	clang-format -i view/*.h


	clang-format -n model/*.cpp
	clang-format -n model/*.h

	clang-format -n controller/*.cpp
	clang-format -n controller/*.h

	clang-format -n view/*.cpp
	clang-format -n view/*.h
