PROJECT = $(notdir $(CURDIR))
# Replace your toolchain directory here
TOOLCHAINDIR ?= /Users/mac/tools/gcc-arm-none-eabi-5_4-2016q3/
COMPILER ?= $(TOOLCHAINDIR)bin/arm-none-eabi-
CC      = $(COMPILER)gcc
CP      = $(COMPILER)objcopy
AS      = $(COMPILER)as
LD      = $(COMPILER)ld
OD      = $(COMPILER)objdump
DEF+=STM32F4XX
# DEF+=USE_FULL_ASSERT
DEF+=USE_STDPERIPH_DRIVER
# DEF+=USB_OTG_HS_CORE
# DEF+=USE_ULPI_PHY
DEF+=USE_USB_OTG_FS
DEF+=MEDIA_USB_KEY
DEF+=__FPU_PRESENT=0
# DEF+=MEDIA_IntFLASH
LIBRARY= /Users/mac/git/portable-music-player/firmware/

PERIPH_DRIVER= $(LIBRARY)/Libraries/STM32F4xx_StdPeriph_Driver
USB_OTG_DRIVER= $(LIBRARY)/Libraries/STM32_USB_OTG_Driver
FAT_FS_DRIVER= $(LIBRARY)/Utilities/Third_Party/fat_fs
USB_HOST_LIBRARY= $(LIBRARY)/Libraries/STM32_USB_HOST_Library
INC+= $(USB_OTG_DRIVER)/inc
INC+= inc
INC+= $(LIBRARY)/Libraries/CMSIS/Include
INC+= .
INC+= $(PERIPH_DRIVER)/inc
INC+= $(LIBRARY)/Libraries/CMSIS/ST/STM32F4xx/Include
INC+= $(LIBRARY)/Utilities/STM32F4-Discovery
INC+= $(FAT_FS_DRIVER)/inc
INC+= $(USB_HOST_LIBRARY)/Core/inc
INC+= $(USB_HOST_LIBRARY)/Class/MSC/inc

SRC+= src/system_stm32f4xx.c
SRC+= src/main.c
SRC+= src/stm32f4xx_it.c
# SRC+= src/audio_sample.c
SRC+= src/usb_bsp.c
SRC+= src/usbh_usr.c

SRC+= src/waveplayer.c
SRC+= src/waverecorder.c

SRC+= $(PERIPH_DRIVER)/src/misc.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_gpio.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_rcc.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_syscfg.c
SRC+= $(PERIPH_DRIVER)/src/misc.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_adc.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_dac.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_dma.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_exti.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_flash.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_gpio.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_i2c.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_rcc.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_spi.c
SRC+= $(PERIPH_DRIVER)/src/stm32f4xx_tim.c

SRC+= $(FAT_FS_DRIVER)/src/ff.c
SRC+= $(FAT_FS_DRIVER)/src/fattime.c

SRC+= $(USB_HOST_LIBRARY)/Class/MSC/src/usbh_msc_scsi.c
SRC+= $(USB_HOST_LIBRARY)/Class/MSC/src/usbh_msc_bot.c
SRC+= $(USB_HOST_LIBRARY)/Class/MSC/src/usbh_msc_core.c
SRC+= $(USB_HOST_LIBRARY)/Class/MSC/src/usbh_msc_fatfs.c
SRC+= $(USB_HOST_LIBRARY)/Core/src/usbh_stdreq.c
SRC+= $(USB_HOST_LIBRARY)/Core/src/usbh_core.c
SRC+= $(USB_HOST_LIBRARY)/Core/src/usbh_hcs.c
SRC+= $(USB_HOST_LIBRARY)/Core/src/usbh_ioreq.c

SRC+= $(LIBRARY)/Utilities/STM32F4-Discovery/stm32f4_discovery.c
SRC+= $(LIBRARY)/Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.c
SRC+= $(LIBRARY)/Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.c

SRC+= $(USB_OTG_DRIVER)/src/usb_core.c
SRC+= $(USB_OTG_DRIVER)/src/usb_hcd_int.c
SRC+= $(USB_OTG_DRIVER)/src/usb_hcd.c

STARTUP= $(LIBRARY)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s
LINKER= -TTrueSTUDIO/MEDIA_USB_KEY/stm32_flash.ld
INCLUDE= $(patsubst %,-I%,$(INC))
DEFINE= $(patsubst %,-D%,$(DEF))
$(shell mkdir -p Output)
$(shell mkdir -p Deps)
OUTPUT=Output
DEPDIR = Deps
df = $(DEPDIR)/$(*F)
OBJS+=$(patsubst %.c,%.o,$(SRC))
OBJS+=$(patsubst %.s,%.o,$(STARTUP))
OBJECTS = $(addprefix $(OUTPUT)/, $(OBJS))
CFLAGS+=$(INCLUDE)
CFLAGS+=$(DEFINE)
CFLAGS+=-g
CFLAGS+=-mcpu=cortex-m4 -mthumb
CFLAGS+=-MD
LDFLAGS+= -L $(LIBRARY)/Utilities/STM32F4-Discovery/
LDFLAGS+= -lPDMFilter_GCC
LDFLAGS+=$(LINKER)
LDFLAGS+=$(CFLAGS)
LDFLAGS+=-lc
LDFLAGS+=-lrdimon
ASFLAGS+=-g
ASFLAGS+=-mcpu=cortex-m4 -mthumb
$(OUTPUT)/%.o: %.s Makefile
	@mkdir -p $(@D)
	@$(AS) $(ASFLAGS) -mthumb $< -o $@
	@echo "AS ${@}"
$(OUTPUT)/%.o: %.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC ${@}"
	@cp $(OUTPUT)/$*.d $(df).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(OUTPUT)/$*.d >> $(df).P; \
	rm -f $(OUTPUT)/$*.d
-include $(SRCS:%.c=$(DEPDIR)/%.P)
all: $(PROJECT).elf $(PROJECT).bin
$(PROJECT).elf : $(OBJECTS)
	@mkdir -p $(@D)
	@$(CC) $^ $(LDFLAGS) $(LIBS) -o $@
	@echo "CC ${@}"
$(PROJECT).bin : $(PROJECT).elf
	@mkdir -p $(@D)
	$(CP) -O binary $(PROJECT).elf $(PROJECT).bin
	
clean: 
	@rm -f $(OBJECTS) $(PROJECT).bin $(DEPDIR)/*.P $(PROJECT).elf
	@rm -R $(OUTPUT) $(DEPDIR)
flash:
	@st-flash write $(PROJECT).bin 0x8000000