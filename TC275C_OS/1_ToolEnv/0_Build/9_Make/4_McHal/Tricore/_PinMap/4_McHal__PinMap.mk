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
# Subdir make file for 0_Src/4_McHal/Tricore/_PinMap
# This is for core type MAIN and Gnuc compiler !!!!
###############################################################################




# current directory relative to project
L_DIR:=0_Src/4_McHal/Tricore/_PinMap								
														
OBJ_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxAsclin_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxCcu6_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxCif_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxDsadc_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxEray_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxEth_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxGpt12_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxGtm_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxI2c_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxMsc_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxMultican_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPort_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPsi5s_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPsi5_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxQspi_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxScu_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxSent_PinMap.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxVadc_PinMap.o				
DEP_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxAsclin_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxCcu6_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxCif_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxDsadc_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxEray_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxEth_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxGpt12_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxGtm_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxI2c_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxMsc_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxMultican_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPort_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPsi5s_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxPsi5_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxQspi_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxScu_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxSent_PinMap.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_PinMap/IfxVadc_PinMap.d				
														
$(OUT_DIR)/0_Src/4_McHal/Tricore/_PinMap/%.o: 0_Src/4_McHal/Tricore/_PinMap/%.c	
	@mkdir -p $(@D)										
	@rm -f $(ELF_BIN_MAIN) $(HEX_BIN_MAIN) $(MAP_FILE_MAIN) (LIB_OBJ_MAIN)					
	@echo 'Compiling $<'								
	$(CC) $(CC_OPTS) -c $< -o $@ -save-temps=obj -MMD	
	@echo ' '											
														



