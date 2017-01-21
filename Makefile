MODULE		?= libusb_stm32
MOUT		?= $(MODULE).a
MTOOLS		?= arm-none-eabi-

SOURCES		= $(wildcard src/*.c) $(wildcard src/*.S)
OBJECTS		= $(addsuffix .o, $(basename $(SOURCES)))

CFLAGS		?= -mthumb -Os -std=gnu99
ARFLAGS		?= -cvq

module: $(MOUT)

doc:
	doxygen

.INTERMEDIATE $(MOUT): $(OBJECTS)
	@$(MTOOLS)gcc-ar -cq $(MOUT) $(OBJECTS)

%.o: %.c
	@$(MTOOLS)gcc $(CFLAGS) $(MCFLAGS) $(addprefix -D, $(MDEFS)) $(addprefix -I, $(MINCS)) -c $< -o $@

%.o: %.S
	@$(MTOOLS)gcc $(CFLAGS) $(MCFLAGS) $(addprefix -D, $(MDEFS)) $(addprefix -I, $(MINCS)) -c $< -o $@

.PHONY: module doc
