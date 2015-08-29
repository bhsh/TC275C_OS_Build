/*
 * DemoApp.h
 *
 *  Created on: Mar 31, 2014
 *      Author: lisherry
 */

#ifndef DEMOAPP_H_
#define DEMOAPP_H_

#include "Cpu\Std\Ifx_Types.h"
#include "Port\Io\IfxPort_Io.h"
#include "Dsadc/Dsadc/IfxDsadc_Dsadc.h"

void Appli_DsadcInit(void);
void Appli_DsadcDemoInit(void);
void Appli_DsadcDemoDeInit(void);
void Appli_DsadcCyclic(void);

#endif /* DEMOAPP_H_ */
