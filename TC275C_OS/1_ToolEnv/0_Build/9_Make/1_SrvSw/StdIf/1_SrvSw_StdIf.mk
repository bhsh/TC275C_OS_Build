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
# Subdir make file for 0_Src/1_SrvSw/StdIf
# This is for core type MAIN and Gnuc compiler !!!!
###############################################################################




# current directory relative to project
L_DIR:=0_Src/1_SrvSw/StdIf								
														
OBJ_FILES_MAIN+=2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_DPipe.o 2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_PwmHl.o 2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_Timer.o				
DEP_FILES_MAIN+=2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_DPipe.d 2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_PwmHl.d 2_Out/Gnuc/0_Src/1_SrvSw/StdIf/IfxStdIf_Timer.d				
														
$(OUT_DIR)/0_Src/1_SrvSw/StdIf/%.o: 0_Src/1_SrvSw/StdIf/%.c	
	@mkdir -p $(@D)										
	@rm -f $(ELF_BIN_MAIN) $(HEX_BIN_MAIN) $(MAP_FILE_MAIN) (LIB_OBJ_MAIN)					
	@echo 'Compiling $<'								
	$(CC) $(CC_OPTS) -c $< -o $@ -save-temps=obj -MMD	
	@echo ' '											
														



