################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./system_msp432p401r.obj" \
"./Communication/IIC.obj" \
"./Communication/uart_to_pc.obj" \
"./Communication/vofa.obj" \
"./Hardware/Tim32.obj" \
"./Hardware/led.obj" \
"./Hardware/timA.obj" \
"./Question/calibration_angle.obj" \
"./Question/follow_line.obj" \
"./Question/follow_rect.obj" \
"./Question/follow_rect_new.obj" \
"./Question/go_center.obj" \
"./Question/go_to_center.obj" \
"./Question/k210_follow.obj" \
"./System/delay.obj" \
"./System/sysinti.obj" \
"./algorithm/angle_math.obj" \
"./algorithm/pid.obj" \
"./ccs/startup_msp432p401r_ccs.obj" \
"./external_devices/RL.obj" \
"./external_devices/Red_line.obj" \
"./external_devices/csb.obj" \
"./external_devices/duoji.obj" \
"./external_devices/fmq.obj" \
"./external_devices/getAngle.obj" \
"./external_devices/motor.obj" \
"./external_devices/oled.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432p401x.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Communication/subdir_vars.mk
-include Hardware/subdir_vars.mk
-include Question/subdir_vars.mk
-include System/subdir_vars.mk
-include algorithm/subdir_vars.mk
-include ccs/subdir_vars.mk
-include external_devices/subdir_vars.mk
-include subdir_rules.mk
-include Communication/subdir_rules.mk
-include Hardware/subdir_rules.mk
-include Question/subdir_rules.mk
-include System/subdir_rules.mk
-include algorithm/subdir_rules.mk
-include ccs/subdir_rules.mk
-include external_devices/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
self_MSP_EXP432P401R_nortos_ccs2.out \

EXE_OUTPUTS__QUOTED += \
"self_MSP_EXP432P401R_nortos_ccs2.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "self_MSP_EXP432P401R_nortos_ccs2.out"

# Tool invocations
self_MSP_EXP432P401R_nortos_ccs2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"self_MSP_EXP432P401R_nortos_ccs2.map" --stack_size=512 -i"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="self_MSP_EXP432P401R_nortos_ccs2_linkInfo.xml" --rom_model -o "self_MSP_EXP432P401R_nortos_ccs2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "system_msp432p401r.obj" "Communication\IIC.obj" "Communication\uart_to_pc.obj" "Communication\vofa.obj" "Hardware\Tim32.obj" "Hardware\led.obj" "Hardware\timA.obj" "Question\calibration_angle.obj" "Question\follow_line.obj" "Question\follow_rect.obj" "Question\follow_rect_new.obj" "Question\go_center.obj" "Question\go_to_center.obj" "Question\k210_follow.obj" "System\delay.obj" "System\sysinti.obj" "algorithm\angle_math.obj" "algorithm\pid.obj" "ccs\startup_msp432p401r_ccs.obj" "external_devices\RL.obj" "external_devices\Red_line.obj" "external_devices\csb.obj" "external_devices\duoji.obj" "external_devices\fmq.obj" "external_devices\getAngle.obj" "external_devices\motor.obj" "external_devices\oled.obj" 
	-$(RM) "main.d" "system_msp432p401r.d" "Communication\IIC.d" "Communication\uart_to_pc.d" "Communication\vofa.d" "Hardware\Tim32.d" "Hardware\led.d" "Hardware\timA.d" "Question\calibration_angle.d" "Question\follow_line.d" "Question\follow_rect.d" "Question\follow_rect_new.d" "Question\go_center.d" "Question\go_to_center.d" "Question\k210_follow.d" "System\delay.d" "System\sysinti.d" "algorithm\angle_math.d" "algorithm\pid.d" "ccs\startup_msp432p401r_ccs.d" "external_devices\RL.d" "external_devices\Red_line.d" "external_devices\csb.d" "external_devices\duoji.d" "external_devices\fmq.d" "external_devices\getAngle.d" "external_devices\motor.d" "external_devices\oled.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

