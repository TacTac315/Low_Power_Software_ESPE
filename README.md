# Low_Power_Software_ESPE

## EXPE 1
Sleep mode : 
CPU alimenté, ne recoit plus la clock

Bouton bleu appuyé -> Activation mode Sleep ; Reset pour en sortir
1/ Voir réglage SLEEP
WFI -> Transition en mode sleep
Interruption débordement systick utilisé pour sortir du sleep mode
Vérifiation de l'état bouton dans SysTick_handler()