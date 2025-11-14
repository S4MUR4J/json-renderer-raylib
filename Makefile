PRESET ?= debug
BINARY = build/$(PRESET)/src/viewer/viewer.exe
SCENE ?= examples/valid_scene.json

all: build

configure:

	cmake --preset $(PRESET)

build:
	cmake --build --preset $(PRESET)

run:
	$(BINARY) $(SCENE)

test:
	ctest --preset $(PRESET) || true

clean:
	rm -rf build

rebuild: clean configure build

.PHONY: all configure build run clean rebuild format lint fix test
