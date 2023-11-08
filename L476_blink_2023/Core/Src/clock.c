/*Author: Alexandre Boyer
 * Date: 26 Sept 2023
 */

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_rtc.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_system.h"
#include "clock.h"

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config_exp1(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_4)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_LSI_Enable();

   /* Wait till LSI is ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  LL_RCC_MSI_SetCalibTrimming(0);
//  LL_PWR_EnableBkUpAccess();
//  LL_RCC_ForceBackupDomainReset();
//  LL_RCC_ReleaseBackupDomainReset();
//  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
//  LL_RCC_EnableRTC();
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  //update global variable SystemCoreClock --> give access to CPU clock frequency.
  LL_SetSystemCoreClock(80000000);

}
void SystemClock_Config_exp2(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_LSI_Enable();

   /* Wait till LSI is ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_PWR_EnableBkUpAccess();
  //LL_RCC_ForceBackupDomainReset();
  //LL_RCC_ReleaseBackupDomainReset();
  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  LL_RCC_EnableRTC();

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  //update global variable SystemCoreClock --> give access to CPU clock frequency.
  LL_SetSystemCoreClock(24000000);
}
void SystemClock_Config_exp2_blue(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  //LL_RCC_ForceBackupDomainReset();
  LL_RCC_LSE_Enable();
   /* Wait till LSI is ready */
  while(LL_RCC_LSE_IsReady() != 1)
  {

  }
  //LL_RCC_ReleaseBackupDomainReset();
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_PWR_EnableBkUpAccess();

  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
  LL_RCC_EnableRTC();

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  //update global variable SystemCoreClock --> give access to CPU clock frequency.
  LL_SetSystemCoreClock(24000000);
}
void SystemClock_Config_exp3(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
  LL_RCC_LSI_Enable();

   /* Wait till LSI is ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_PWR_EnableBkUpAccess();
  //LL_RCC_ForceBackupDomainReset();
  //LL_RCC_ReleaseBackupDomainReset();
  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  LL_RCC_EnableRTC();

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  //update global variable SystemCoreClock --> give access to CPU clock frequency.
  LL_SetSystemCoreClock(24000000);
}
void RTC_Init(void)
{
  // Enable LSE oscillator

	 // Reset backup domain
	  LL_RCC_ForceBackupDomainReset();
	  LL_RCC_ReleaseBackupDomainReset();
  LL_RCC_LSE_Enable();
  while (LL_RCC_LSE_IsReady() != 1)
  {
  }



  // Configure RTC prescalers
  LL_RTC_DisableWriteProtection(RTC);
  LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
  LL_RTC_SetSynchPrescaler(RTC, 0xFF);
  LL_RTC_EnableWriteProtection(RTC);

  LL_RCC_EnableRTC();
}
void SystemClock_Config_exp5(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
	  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
	  {
	  }
	  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
	  LL_RCC_LSI_Enable();

	   /* Wait till LSI is ready */
	  while(LL_RCC_LSI_IsReady() != 1)
	  {

	  }
	  LL_RCC_MSI_Enable();

	   /* Wait till MSI is ready */
	  while(LL_RCC_MSI_IsReady() != 1)
	  {

	  }
	  LL_RCC_MSI_EnableRangeSelection();
	  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
	  LL_RCC_MSI_SetCalibTrimming(0);
	  LL_PWR_EnableBkUpAccess();
	  //LL_RCC_ForceBackupDomainReset();
	  //LL_RCC_ReleaseBackupDomainReset();
	  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
	  LL_RCC_EnableRTC();

	  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	  //update global variable SystemCoreClock --> give access to CPU clock frequency.
	  LL_SetSystemCoreClock(24000000);
}

/*
// partie commune a toutes les utilisations du wakeup timer
void RTC_wakeup_init( int delay )
{
LL_RTC_DisableWriteProtection( RTC );
LL_RTC_WAKEUP_Disable( RTC );
while	( !LL_RTC_IsActiveFlag_WUTW( RTC ) )
	{ }
// connecter le timer a l'horloge 1Hz de la RTC
LL_RTC_WAKEUP_SetClock( RTC, LL_RTC_WAKEUPCLOCK_CKSPRE );
// fixer la duree de temporisation
LL_RTC_WAKEUP_SetAutoReload( RTC, delay );	// 16 bits
LL_RTC_ClearFlag_WUT(RTC);
LL_RTC_EnableIT_WUT(RTC);
LL_RTC_WAKEUP_Enable(RTC);
LL_RTC_EnableWriteProtection(RTC);
}

// Dans le cas des modes STANDBY et SHUTDOWN, le MPU sera reveille par reset
// causé par 1 wakeup line (interne ou externe) (le NVIC n'est plus alimenté)
void RTC_wakeup_init_from_standby_or_shutdown( int delay )
{
RTC_wakeup_init( delay );
// enable the Internal Wake-up line
LL_PWR_EnableInternWU();	// ceci ne concerne que Standby et Shutdown, pas STOPx
}

// Dans le cas des modes STOPx, le MPU sera reveille par interruption
// le module EXTI et une partie du NVIC sont encore alimentes
// le contenu de la RAM et des registres étant préservé, le MPU
// reprend l'execution après l'instruction WFI
void RTC_wakeup_init_from_stop( int delay )
{
RTC_wakeup_init( delay );
// valider l'interrupt par la ligne 20 du module EXTI, qui est réservée au wakeup timer
LL_EXTI_EnableIT_0_31( LL_EXTI_LINE_20 );
LL_EXTI_EnableRisingTrig_0_31( LL_EXTI_LINE_20 );
// valider l'interrupt chez NVIC
NVIC_SetPriority( RTC_WKUP_IRQn, 1 );
NVIC_EnableIRQ( RTC_WKUP_IRQn );
}

// wakeup timer interrupt Handler (inutile mais doit etre defini)
void RTC_WKUP_IRQHandler()
{
LL_EXTI_ClearFlag_0_31( LL_EXTI_LINE_20 );
}
*/
