.SILENT:

OUTPUT_FOLDER=out
ARGS=-Wall -Wextra -Werror

files = $(wildcard *.c)

all: $(OUTPUT_FOLDER)/main

$(OUTPUT_FOLDER)/main: $(files)
	mkdir -p $(OUTPUT_FOLDER)
	cc $(ARGS) $(files) -o $(OUTPUT_FOLDER)/main

clean:
	rm -f $(OUTPUT_FOLDER)/main

run: all
	./$(OUTPUT_FOLDER)/main