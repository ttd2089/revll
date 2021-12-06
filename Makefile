BIN ?= revll

SOURCES ::= $(wildcard *.c)

.PHONY: phony
phony:
run-%: $(BIN) phony
	@./$(BIN) $*

memcheck: $(BIN)
	@1>/dev/null valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN)

$(BIN): $(SOURCES)
	@gcc -Wall -Werror -o $@ $^
