// TASKING VX-toolset for TriCore
// Eclipse project linker script file
// 
#if defined(__PROC_TC27XC__)
#include "tc27xc.lsl"
derivative my_tc27xc extends tc27xc
{
}
#else
#include <cpu.lsl>
#endif
