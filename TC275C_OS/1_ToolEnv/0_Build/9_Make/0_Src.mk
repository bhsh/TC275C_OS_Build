###############################################################################
#                                                                             #
#        Copyright © 2011 Infineon Technologies AG. All rights reserved.      #
#                                                                             #
#                                                                             #
#                              IMPORTANT NOTICE                               #
#                                                                             #
#                                                                             #
# Infineon Technologies AG (Infineon) is supplying this file for use          #
# exclusively with Infineon’s microcontroller products. This file can be      #
# freely distributed within development tools that are supporting such        #
# microcontroller products.                                                   #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED #
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF          #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.#
# INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,#
# OR CONSEQUENTIAL DAMAGES, FOR	ANY REASON WHATSOEVER.                        #
#                                                                             #
###############################################################################
# Subdir make file for 0_Src
# This is for core type MAIN and Gnuc compiler !!!!
###############################################################################

include 1_ToolEnv/0_Build/1_Config/CfgCompiler_Gnuc.mk								
include 1_ToolEnv/0_Build/1_Config/ConfigPrj.mk			
														
														
PROJ_C_INCLUDES:= -I./0_Src/0_AppSw -I./0_Src/0_AppSw/Config -I./0_Src/0_AppSw/Config/Common -I./0_Src/0_AppSw/Tricore -I./0_Src/1_SrvSw -I./0_Src/1_SrvSw/If -I./0_Src/1_SrvSw/If -I./0_Src/1_SrvSw/If/Ccu6If -I./0_Src/1_SrvSw/StdIf -I./0_Src/1_SrvSw/StdIf -I./0_Src/1_SrvSw/SysSe -I./0_Src/1_SrvSw/SysSe/Bsp -I./0_Src/1_SrvSw/SysSe/Comm -I./0_Src/1_SrvSw/SysSe/General -I./0_Src/1_SrvSw/SysSe/Math -I./0_Src/1_SrvSw/SysSe/Time -I./0_Src/1_SrvSw/Tricore -I./0_Src/1_SrvSw/Tricore/Compilers -I./0_Src/1_SrvSw/_Utilities -I./0_Src/1_SrvSw/_Utilities -I./0_Src/4_McHal -I./0_Src/4_McHal/Tricore -I./0_Src/4_McHal/Tricore/Asclin/Asc -I./0_Src/4_McHal/Tricore/Asclin/Lin -I./0_Src/4_McHal/Tricore/Asclin/Spi -I./0_Src/4_McHal/Tricore/Asclin/Std -I./0_Src/4_McHal/Tricore/Ccu6/Icu -I./0_Src/4_McHal/Tricore/Ccu6/PwmBc -I./0_Src/4_McHal/Tricore/Ccu6/Std -I./0_Src/4_McHal/Tricore/Ccu6/TPwm -I./0_Src/4_McHal/Tricore/Ccu6/Timer -I./0_Src/4_McHal/Tricore/Cif/Cam -I./0_Src/4_McHal/Tricore/Cif/Std -I./0_Src/4_McHal/Tricore/Cpu/CStart -I./0_Src/4_McHal/Tricore/Cpu/Irq -I./0_Src/4_McHal/Tricore/Cpu/Std -I./0_Src/4_McHal/Tricore/Cpu/Trap -I./0_Src/4_McHal/Tricore/Dma/Dma -I./0_Src/4_McHal/Tricore/Dma/Std -I./0_Src/4_McHal/Tricore/Dsadc/Dsadc -I./0_Src/4_McHal/Tricore/Dsadc/Std -I./0_Src/4_McHal/Tricore/Dts/Dts -I./0_Src/4_McHal/Tricore/Dts/Std -I./0_Src/4_McHal/Tricore/Emem/Std -I./0_Src/4_McHal/Tricore/Eray/Eray -I./0_Src/4_McHal/Tricore/Eray/Std -I./0_Src/4_McHal/Tricore/Eth/Phy_Pef7071 -I./0_Src/4_McHal/Tricore/Eth/Std -I./0_Src/4_McHal/Tricore/Fce/Crc -I./0_Src/4_McHal/Tricore/Fce/Std -I./0_Src/4_McHal/Tricore/Flash/Std -I./0_Src/4_McHal/Tricore/Gtm/Atom/PwmHl -I./0_Src/4_McHal/Tricore/Gtm/Atom/Timer -I./0_Src/4_McHal/Tricore/Gtm/Std -I./0_Src/4_McHal/Tricore/Gtm/Tom/PwmHl -I./0_Src/4_McHal/Tricore/Gtm/Tom/Timer -I./0_Src/4_McHal/Tricore/Gtm/Trig -I./0_Src/4_McHal/Tricore/Hssl/Hssl -I./0_Src/4_McHal/Tricore/Hssl/Std -I./0_Src/4_McHal/Tricore/I2c/I2c -I./0_Src/4_McHal/Tricore/I2c/Std -I./0_Src/4_McHal/Tricore/Iom/Iom -I./0_Src/4_McHal/Tricore/Iom/Std -I./0_Src/4_McHal/Tricore/Msc/Msc -I./0_Src/4_McHal/Tricore/Msc/Std -I./0_Src/4_McHal/Tricore/Mtu/Std -I./0_Src/4_McHal/Tricore/Multican/Can -I./0_Src/4_McHal/Tricore/Multican/Std -I./0_Src/4_McHal/Tricore/Port/Io -I./0_Src/4_McHal/Tricore/Port/Std -I./0_Src/4_McHal/Tricore/Psi5/Psi5 -I./0_Src/4_McHal/Tricore/Psi5/Std -I./0_Src/4_McHal/Tricore/Psi5s/Psi5s -I./0_Src/4_McHal/Tricore/Psi5s/Std -I./0_Src/4_McHal/Tricore/Qspi/SpiMaster -I./0_Src/4_McHal/Tricore/Qspi/SpiSlave -I./0_Src/4_McHal/Tricore/Qspi/Std -I./0_Src/4_McHal/Tricore/Scu/Std -I./0_Src/4_McHal/Tricore/Sent/Sent -I./0_Src/4_McHal/Tricore/Sent/Std -I./0_Src/4_McHal/Tricore/Src/Std -I./0_Src/4_McHal/Tricore/Stm/Std -I./0_Src/4_McHal/Tricore/Vadc/Adc -I./0_Src/4_McHal/Tricore/Vadc/Std -I./0_Src/4_McHal/Tricore/_Impl -I./0_Src/4_McHal/Tricore/_Lib/DataHandling -I./0_Src/4_McHal/Tricore/_Lib/Math -I./0_Src/4_McHal/Tricore/_PinMap -I./0_Src/4_McHal/Tricore/_Reg 					
PROJ_ASM_INCLUDES:=  				

include 1_ToolEnv/0_Build/9_Make/0_AppSw/0_AppSw.mk 1_ToolEnv/0_Build/9_Make/1_SrvSw/1_SrvSw.mk 1_ToolEnv/0_Build/9_Make/4_McHal/4_McHal.mk  

# current directory relative to project
L_DIR:=0_Src								
																									
PROJ_OBJS_MAIN:=  																	
																									
.PHONY: All_Targets																					
																									
ExeTargets:$(ELF_BIN_MAIN) $(HEX_BIN_MAIN) $(ELF_BIN_SECOND) $(HEX_BIN_SECOND)						
	@echo '...Done'																					
																									
$(ELF_BIN_MAIN) $(HEX_BIN_MAIN):$(OBJ_FILES_SPECIAL) $(OBJ_FILES_MAIN) $(PROJ_OBJS_MAIN) $(LSL_MAIN_FILE) 
	@echo 'Building target: $@'																		
	$(LD) $(LD_OPTS) $(LIB_DIR) $(OBJ_FILES_MAIN) $(OBJ_FILES_SPECIAL) $(PROJ_OBJS_MAIN) $(LIBS) -o $(ELF_BIN_MAIN) 	
	$(HX) $(ELF_BIN_MAIN) -O ihex $(HEX_BIN_MAIN)									
	@echo ' '																																													
																									
Archive: $(LIB_OBJ_MAIN) $(LIB_OBJ_SECOND)															
																									
$(LIB_OBJ_MAIN): $(OBJ_FILES_SPECIAL) $(OBJ_FILES_MAIN) $(PROJ_OBJS_MAIN)				
	@echo 'Building library: $@'														
	$(AR) rcs $@ $(OBJ_FILES_SPECIAL) $(OBJ_FILES_MAIN) $(PROJ_OBJS_MAIN)				


-include $(DEP_FILES_MAIN)																			
-include $(DEP_FILES_SPECIAL)																		

