/*Author: Alexandre Boyer
 * Date: 26 Sept 2023
 */

//configuration of the system clock
void SystemClock_Config_exp1(void);
void SystemClock_Config_exp2(void);
void SystemClock_Config_exp3(void);
void SystemClock_Config_exp2_blue(void);
void SystemClock_Config_exp5(void);
void RTC_Init_ColdStart(void);
void RTC_Init_HotStart(void);
void RTC_wakeup_init( int delay );
void RTC_wakeup_init_from_standby_or_shutdown( int delay );
void RTC_wakeup_init_from_stop( int delay );
void RTC_WKUP_IRQHandler();
