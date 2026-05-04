CC      = gcc
CFLAGS  = -O2 -fopenmp -Wall
SRC     = shallow_water_simulation.c

# Schedules to build. Use ":" for chunk size, e.g. static:64
# (avoids clashing with make's argument-separator comma).
SCHEDULES = static static:1 static:64 dynamic dynamic:64 dynamic:256 guided guided:64

comma := ,

# "static:64" -> binary name "sw_static_64"
target_name = sw_$(subst :,_,$(1))

BINS = $(foreach s,$(SCHEDULES),$(call target_name,$(s)))

.PHONY: all clean run

all: $(BINS)

# Build sw_<sched>[_<chunk>] -> -DSCHED=<sched>[,<chunk>]
sw_%: $(SRC)
	$(CC) $(CFLAGS) -DSCHED="$(subst _,$(comma),$*)" $< -o $@

# Run all binaries (set OMP_NUM_THREADS via env, default 8)
run: all
	@echo "OMP_NUM_THREADS=$${OMP_NUM_THREADS:-8}"
	@for b in $(BINS); do \
	    OMP_NUM_THREADS=$${OMP_NUM_THREADS:-8} ./$$b; \
	done

clean:
	rm -f $(BINS) output.txt
