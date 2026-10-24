.PHONY: build dev clean format lint test test-wayland

build:
	uv build

dev:
	uv pip install .

clean:
	rm -rf build dist

format:
	clang-format -i $$(find core tests -name '*.cpp' -o -name '*.hpp')

lint:
	clang-format --dry-run --Werror $$(find core tests -name '*.cpp' -o -name '*.hpp')

test:
	meson setup build
	meson test -C build --print-errorlogs

test-wayland:
	scripts/test-wayland.sh
