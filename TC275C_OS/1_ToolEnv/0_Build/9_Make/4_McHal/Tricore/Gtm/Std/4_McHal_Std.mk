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
# Subdir make file for 0_Src/4_McHal/Tricore/Gtm/Std
# This is for core type MAIN and Gnuc compiler !!!!
###############################################################################




# current directory relative to project
L_DIR:=0_Src/4_McHal/Tricore/Gtm/Std								
														
OBJ_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Atom.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Cmu.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Dpll.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tbu.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tim.o 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tom.o				
DEP_FILES_MAIN+=2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Atom.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Cmu.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Dpll.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tbu.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tim.d 2_Out/Gnuc/0_Src/4_McHal/Tricore/Gtm/Std/IfxGtm_Tom.d				
														
$(OUT_DIR)/0_Src/4_McHal/Tricore/Gtm/Std/%.o: 0_Src/4_McHal/Tricore/Gtm/Std/%.c	
	@mkdir -p $(@D)										
	@rm -f $(ELF_BIN_MAIN) $(HEX_BIN_MAIN) $(MAP_FILE_MAIN) (LIB_OBJ_MAIN)					
	@echo 'Compiling $<'								
	$(CC) $(CC_OPTS) -c $< -o $@ -save-temps=obj -MMD	
	@echo ' '											
														



