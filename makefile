# MCU name
MCU = atmega328p

# Target file name (without extension).
TARGET = project
#Path build dir
BUILD_DIR = build
COMPONENTS_DIR = components
FreeRTOS_DIR = FreeRTOS



SRC = main.c \
$(COMPONENTS_DIR)\usart.c \
$(COMPONENTS_DIR)\config.c \
$(FreeRTOS_DIR)\tasks.c \
$(FreeRTOS_DIR)\queue.c \
$(FreeRTOS_DIR)\list.c \
$(FreeRTOS_DIR)\port.c \
$(FreeRTOS_DIR)\heap_1.c \



INCLUDES = \
-I c:\msys64\mingw64\avr\include \
-I $(COMPONENTS_DIR)\ \
-I $(FreeRTOS_DIR)\include\ 

# Optional compiler flags.
#  -g:        generate debugging information (for GDB, or for COFF conversion)
#  -O*:       optimization level
#  -f...:     tuning, see gcc manual and avr-libc documentation
#  -Wall...:  warning level
#  -Wa,...:   tell GCC to pass this to the assembler.
#    -ahlms:  create assembler listing

WARNINGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare \
		-Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wunused

CFLAGS = -D GCC_MEGA_AVR $(INCLUDES) \
-O$(OPT) \
-fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
$(WARNINGS) \
-Wa,-adhlns=$(<:.c=.lst) 

# Set a "language standard" compiler flag.
#   Unremark just one line below to set the language standard to use.
#   gnu99 = C99 + GNU extensions. See GCC manual for more information.
#CFLAGS += -std=c89
#CFLAGS += -std=gnu89
#CFLAGS += -std=c99
CFLAGS += -std=c17

# Optional assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs



# Optional linker flags.
#  -Wl,...:   tell GCC to pass this to linker.
#  -Map:      create map file
#  --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref 

# Define programs and commands.
SHELL = sh

CC = avr-gcc

OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVR_SIZE = avr-size
AVR_READ_ELF = avr-readelf

# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:

all: begin $(TARGET).elf $(TARGET).hex $(TARGET).lss $(TARGET).sym $(TARGET).bin \
	finished clean_move gccversion INFO end
begin:
	@echo 
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo

# Display compiler version information.
gccversion :
	@$(CC) --version

# Convert ELF to COFF for use in debugging / simulating in
# AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
	--change-section-address .data-0x800000 \
	--change-section-address .bss-0x800000 \
	--change-section-address .noinit-0x800000 \
	--change-section-address .eeprom-0x810000

coff: $(TARGET).elf
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $(BUILD_DIR)\$< $(TARGET).cof 


# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $(BUILD_DIR)\$< $(BUILD_DIR)\$@


# Create extended listing file from ELF output file.
%.lss: %.elf
	$(OBJDUMP) -h -S $(BUILD_DIR)\$< > $(BUILD_DIR)\$@

# Create a symbol table from ELF output file.
%.sym: %.elf
	avr-nm -n $(BUILD_DIR)\$< > $(BUILD_DIR)\$@

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf 
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $(BUILD_DIR)\$@ $(LDFLAGS)

#
%.bin:$(OBJ)
	$(OBJCOPY) -I ihex $(BUILD_DIR)\$(TARGET).hex -O binary $(BUILD_DIR)\$@

# Compile: create object files from C source files.
%.o : %.c

	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


#%.d: %.c
#	set -e; $(CC) -MM $(ALL_CFLAGS) $< \
	sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@


# Remove the '-' if you want to see the dependency files generated.
-include $(SRC:.c=.d)

clean_move: _move_lst _move_map _clean

_clean:
	del $(COMPONENTS_DIR)\*.o 
	del $(FreeRTOS_DIR)\*.o 
	del *.o 
	
_move_lst:
	move *.lst $< $(BUILD_DIR)
	move $(COMPONENTS_DIR)\*.lst $< $(BUILD_DIR) 
	move $(FreeRTOS_DIR)\*.lst $< $(BUILD_DIR)

_move_map:
	move *.map $< $(BUILD_DIR)

Clean_project:
	del $(BUILD_DIR)\*.*

INFO: info_size info_readelf

info_size:
	$(AVR_SIZE) -C --mcu=MCU $(BUILD_DIR)\$(TARGET).elf

info_readelf:
	del $(BUILD_DIR)\*.txt
	$(AVR_READ_ELF) --all $(BUILD_DIR)\$(TARGET).elf > $(BUILD_DIR)\info_$(TARGET)_ELF.txt


# Listing of phony targets.
.PHONY : all begin finish end  gccversion coff extcoff \
	_clean clean_move _move_lst _move_map info_readelf info_size \
	INFO Clean_project

