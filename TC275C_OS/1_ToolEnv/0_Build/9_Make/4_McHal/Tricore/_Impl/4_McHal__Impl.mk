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
# Subdir make file for 0_Src/4_McHal/Tricore/_Impl
# This is for core type MAIN and Gnuc compiler !!!!
###############################################################################




# current directory relative to project
L_DIR:=0_Src/4_McHal/Tricore/_Impl								
														
OBJ_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxAsclin_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxCcu6_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxCpu_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDma_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDsadc_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDts_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxEray_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxEth_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxFce_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxFlash_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxGtm_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxHssl_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxI2c_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxIom_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMsc_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMtu_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMultican_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPort_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPsi5s_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPsi5_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxQspi_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxSent_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxSrc_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxStm_cfg.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxVadc_cfg.o				
DEP_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxAsclin_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxCcu6_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxCpu_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDma_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDsadc_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxDts_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxEray_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxEth_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxFce_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxFlash_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxGtm_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxHssl_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxI2c_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxIom_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMsc_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMtu_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxMultican_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPort_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPsi5s_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxPsi5_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxQspi_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxSent_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxSrc_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxStm_cfg.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/_Impl/IfxVadc_cfg.d				
														
$(OUT_DIR)/0_Src/4_McHal/Tricore/_Impl/%.o: 0_Src/4_McHal/Tricore/_Impl/%.c	
	@mkdir -p $(@D)										
	@rm -f $(ELF_BIN_MAIN) $(HEX_BIN_MAIN) $(MAP_FILE_MAIN) (LIB_OBJ_MAIN)					
	@echo 'Compiling $<'								
	$(CC) $(CC_OPTS) -c $< -o $@ -save-temps=obj -MMD	
	@echo ' '											
														



