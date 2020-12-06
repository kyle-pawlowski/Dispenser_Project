################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs" --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1560459505: ../pwmled2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs/ccs/utils/sysconfig_1.6.0/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_4_30_00_06/.metadata/product.json" -o "syscfg" --compiler ccs "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1560459505 ../pwmled2.syscfg
syscfg/ti_drivers_config.h: build-1560459505
syscfg/ti_utils_build_linker.cmd.genlibs: build-1560459505
syscfg/syscfg_c.rov.xs: build-1560459505
syscfg/ti_utils_runtime_model.gv: build-1560459505
syscfg/ti_utils_runtime_Makefile: build-1560459505
syscfg/: build-1560459505

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs" --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/source" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_4_30_00_06/kernel/nortos/posix" --include_path="C:/ti/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Kyle/Documents/Senior Design/project_workspace/pwmled2_CC3220SF_LAUNCHXL_nortos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


