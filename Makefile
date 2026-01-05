SRC_FILES := $(wildcard src/*)
BUILD_DEPS := CMakeLists.txt Makefile $(SRC_FILES)
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
RESET := \033[0m

reset:
	@stty -F /dev/ttyACM0 115200 raw -echo || true
	@printf 'r' > /dev/ttyACM0 || true

build: $(BUILD_DEPS)
	mkdir -p build && \
	cd build && \
	cmake -DPICO_BOARD=pico_w .. && \
	if bear --append -- make -j8; then \
	    echo ""; \
	else \
	    make -j8; \
	    echo -e "$(YELLOW)<< WARN >> Built without compile_commands.json$(RESET)"; \
	fi && \
	cd .. && echo -e "$(GREEN) $$(du -h build/main.uf2)$(RESET)"

flash: reset build
	sleep '2s'
	picotool load build/main.uf2
	picotool reboot
