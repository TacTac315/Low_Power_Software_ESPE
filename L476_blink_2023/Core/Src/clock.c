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
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSI);

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
  LL_PWR_EnableBkUpAccess();

  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  LL_RCC_EnableRTC();

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  //update global variable SystemCoreClock --> give access to CPU clock frequency.
  LL_SetSystemCoreClock(24000000);
}
void RTC_Init_ColdStart(void)
{
    // Enable LSE oscillator
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_LSE_Enable();
    while (LL_RCC_LSE_IsReady() != 1)
    {
    }
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
    LL_RCC_EnableRTC();
    // Configure RTC prescalers
    LL_RTC_DisableWriteProtection(RTC);
    LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
    LL_RTC_SetSynchPrescaler(RTC, 0xFF);
    LL_RTC_EnableWriteProtection(RTC);

    // Reset BKP_DR0 to a known initial value (1 in this case)
    LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, 1);


}

void RTC_Init_HotStart(void){
	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
	LL_RCC_EnableRTC();
    // Configure RTC prescalers
    LL_RTC_DisableWriteProtection(RTC);
    LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
    LL_RTC_SetSynchPrescaler(RTC, 0xFF);
    LL_RTC_EnableWriteProtection(RTC);
}
void SystemClock_Config_exp5(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
	  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
	  {
	  }
	  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
	  LL_RCC_MSI_Enable();

	   /* Wait till MSI is ready */
	  while(LL_RCC_MSI_IsReady() != 1)
	  {

	  }
	  LL_RCC_MSI_EnableRangeSelection();
	  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_9);
	  LL_RCC_MSI_SetCalibTrimming(0);
	  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSI);
	  while(LL_RCC_GetSysClkSource()!= LL_RCC_SYS_CLKSOURCE_STATUS_MSI)
	  {

	  }
	  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	  //update global variable SystemCoreClock --> give access to CPU clock frequency.
	  LL_SetSystemCoreClock(24000000);
}

//void enter_stop0_mode(void) {
//    // Configure the system to enter STOP0 mode after
//    // the CPU enters deepsleep mode
//    LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0);
//
//    // Set SLEEPDEEP bit of Cortex System Control Register
//    LL_LPM_EnableDeepSleep();
//
//    // Configure the wakeup timer
//    LL_RTC_DisableWriteProtection(RTC);
//    LL_RTC_WAKEUP_Disable(RTC);
//    while(!LL_RTC_IsActiveFlag_WUTW(RTC)) {}
//    LL_RTC_WAKEUP_SetClock(RTC, LL_RTC_WAKEUPCLOCK_DIV_16);
//    LL_RTC_WAKEUP_SetAutoReload(RTC, 7 * 32768 / 16 - 1);
//    LL_RTC_ClearFlag_WUT(RTC);
//    LL_RTC_EnableIT_WUT(RTC);
//    LL_RTC_WAKEUP_Enable(RTC);
//    LL_RTC_EnableWriteProtection(RTC);
//
//    // Request Wait For Interrupt
//    __WFI();
//}

//void exit_stop_mode(void) {
//    LL_RCC_MSI_Enable();
//    while(LL_RCC_MSI_IsReady() != 1)
//  	  {
//
//  	  }
//
//
//    // Reconfigure peripherals if needed
//    // ...
//
//    // Clear the SLEEPDEEP bit of the Cortex System Control Register
//    LL_LPM_DisableDeepSleep();
//
//    // Clear the PDDS and LPDS bits in the PWR power control register
//    LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0);
//
//    // Disable the wakeup timer
//    LL_RTC_DisableWriteProtection(RTC);
//    LL_RTC_WAKEUP_Disable(RTC);
//    LL_RTC_EnableWriteProtection(RTC);
//}




