PRESET ?= debug

BUILD_DIR = build/$(PRESET)
BINARY = $(BUILD_DIR)/renderer.exe

all: build

configure:
	cmake --preset $(PRESET)

build:
	cmake --build --preset $(PRESET)

run:
	echo "Running SceneKeeper Renderer..."
	$(BINARY)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean configure build

presets:
	cmake --list-presets

test:
	ctest --preset $(PRESET) || true

.PHONY: all configure build run clean rebuild test presets