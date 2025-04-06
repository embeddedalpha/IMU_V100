 #include "main.h"
#include "Console/Console.h"
#include "WSHP.h"




int main(void)
{
	MCU_Clock_Setup();
	Console_Init(115200);
	Delay_Config();

//	DIP_Switches_and_SSD_Init();
//	Enforce_DIP_Switch_States();


	Thermostat_Pin_Init();
	Output_Relay_Signals_Init();
	Fault_Switch_Init();
	Sensor_Init();
//	Error_Code_Init();
//	OD_Fan_PWM_Output_Init();




	uint8_t status_buffer[10];



	for(;;)
	{
		Current_State = Get_State();

				switch (Current_State){
					case HEATING_MODE_1:
					{
						if(DEFROST_FLAG == ON)
						{
							RV_Relay_ON();
							OD_FAN_1_Relay_OFF();
							HEATER_1_Relay_ON();
							Compressor_ON();
							status_buffer[0] = 1; //HEATING MODE 1
							status_buffer[1] = 2; //DEFROST MODE
							status_buffer[2] = 1; //ELECTRIC HEATER 1 = ON
							status_buffer[3] = 0; //ELECTRIC HEATER 2 = OFF
							status_buffer[4] = 1; //ID_FAN 1 = ON
							status_buffer[5] = 0; //ID_FAN 2 = OFF
							status_buffer[6] = 0; //ID_FAN 3 = OFF
							status_buffer[7] = 0; //ID_FAN 4 = OFF
							status_buffer[8] = 0; //ID_FAN 5 = OFF
							status_buffer[9] = 1; //Reversing Valve = ON
							status_buffer[10] = 0; //Re-heat Valve = OFF
							status_buffer[11] = 1; //Bleed-off Valve = ON

							printf("\r\n");
						}
						else
						{
							OD_FAN_1_Relay_ON();

							RV_Relay_OFF();

							Reheat_Valve_Relay_OFF();

							BleedOFF_Valve_Relay_ON();

							ID_FAN_1_Relay_ON();
							ID_FAN_2_Relay_ON();

							Compressor_ON();

							status_buffer[0] = 1; //HEATING MODE 1
							status_buffer[1] = 2; //DEFROST MODE
							status_buffer[2] = 1; //ELECTRIC HEATER 1 = ON
							status_buffer[3] = 0; //ELECTRIC HEATER 2 = OFF
							status_buffer[4] = 1; //ID_FAN 1 = ON
							status_buffer[5] = 0; //ID_FAN 2 = OFF
							status_buffer[6] = 0; //ID_FAN 3 = OFF
							status_buffer[7] = 0; //ID_FAN 4 = OFF
							status_buffer[8] = 0; //ID_FAN 5 = OFF
							status_buffer[9] = 1; //Reversing Valve = ON
							status_buffer[10] = 0; //Re-heat Valve = OFF
							status_buffer[11] = 1; //Bleed-off Valve = ON

//							printConsole("Current State: Low Heat Mode \r\n ");
//							printConsole("ID_FAN 1 = ON \r\n");
//							printConsole("ID_FAN 2 = ON \r\n");
//							printConsole("Reversing Valve = OFF \r\n");
//							printConsole("Re-heat Valve = OFF \r\n");
//							printConsole("Bleed-off Valve = ON \r\n");
//							if(Compressor_State == ON)
//							{
//								printConsole("Compressor = ON \r\n");
//							}
							printf("\r\n");
						}
					}
						break;

					case HEATING_MODE_2:
					{
						if(DEFROST_FLAG == ON)
						{
							RV_Relay_ON();
							OD_FAN_1_Relay_OFF();
							HEATER_1_Relay_ON();
							HEATER_2_Relay_ON();
							Compressor_ON();

							printConsole("Current State: Defrost Mode \r\n ");
							printConsole("ELECTRIC HEATER 1 = ON \r\n");
							printConsole("ELECTRIC HEATER 2 = ON \r\n");
							printConsole("ID_FAN 1 = OFF \r\n");
							printConsole("ID_FAN 2 = OFF \r\n");
							printConsole("ID_FAN 3 = OFF \r\n");
							printConsole("Reversing Valve = ON \r\n");
							printConsole("Re-heat Valve = OFF \r\n");
							printConsole("Bleed-off Valve = ON \r\n");
							if(Compressor_State == ON)
							{
								printConsole("Compressor = ON \r\n");
							}
							printf("\r\n");
						}
						else
						{
							OD_FAN_1_Relay_ON();

							ID_FAN_1_Relay_ON();
							ID_FAN_2_Relay_ON();
							ID_FAN_3_Relay_ON();

							RV_Relay_OFF();

							Reheat_Valve_Relay_OFF();

							BleedOFF_Valve_Relay_ON();

							Compressor_ON();

							printConsole("Current State: High Heat Mode \r\n ");
							printConsole("ID_FAN 1 = ON \r\n");
							printConsole("ID_FAN 2 = ON \r\n");
							printConsole("ID_FAN 3 = ON \r\n");
							printConsole("Reversing Valve = OFF \r\n");
							printConsole("Re-heat Valve = OFF \r\n");
							printConsole("Bleed-off Valve = ON \r\n");
							if(Compressor_State == ON)
							{
								printConsole("Compressor = ON \r\n");
							}
							printf("\r\n");
						}




					}
						break;

					case COOLING_MODE_1:
					{
						OD_FAN_1_Relay_ON();

						ID_FAN_1_Relay_ON();
						ID_FAN_2_Relay_ON();

						RV_Relay_ON();

						if(DH_Flag == ON)
						{
							printConsole("De-humidification Mode ON \r\n");
							Reheat_Valve_Relay_ON();
							printConsole("Re-heat Valve = ON \r\n");

						}
						else
						{
							printConsole("De-humidification Mode OFF \r\n");
							Reheat_Valve_Relay_OFF();
							printConsole("Re-heat Valve = OFF \r\n");
						}
						BleedOFF_Valve_Relay_ON();
						Compressor_ON();

						status_buffer[0] = 1; //HEATING MODE 1
						status_buffer[1] = 2; //DEFROST MODE
						status_buffer[2] = 1; //ELECTRIC HEATER 1 = ON
						status_buffer[3] = 0; //ELECTRIC HEATER 2 = OFF
						status_buffer[4] = 1; //ID_FAN 1 = ON
						status_buffer[5] = 0; //ID_FAN 2 = OFF
						status_buffer[6] = 0; //ID_FAN 3 = OFF
						status_buffer[7] = 0; //ID_FAN 4 = OFF
						status_buffer[8] = 0; //ID_FAN 5 = OFF
						status_buffer[9] = 1; //Reversing Valve = ON
						status_buffer[10] = 0; //Re-heat Valve = OFF
						status_buffer[11] = 1; //Bleed-off Valve = ON

						printConsole("Current State: Low Cooling Mode \r\n ");
						printConsole("ID_FAN 1 = ON \r\n");
						printConsole("ID_FAN 2 = ON \r\n");
						printConsole("Reversing Valve = ON \r\n");
						printConsole("Re-heat Valve = OFF \r\n");
						printConsole("Bleed-off Valve = ON \r\n");
						if(Compressor_State == ON)
						{
							printConsole("Compressor = ON \r\n");
						}
						printf("\r\n");

					}
						break;

					case COOLING_MODE_2:
					{
						OD_FAN_1_Relay_ON();

						ID_FAN_1_Relay_ON();
						ID_FAN_2_Relay_ON();
						ID_FAN_3_Relay_ON();

//						Delay_s(5);
						RV_Relay_ON();

						if(DH_Flag == ON)
						{
							printConsole("De-humidification Mode ON \r\n");
							Reheat_Valve_Relay_ON();
							printConsole("Re-heat Valve = ON \r\n");

						}
						else
						{
							printConsole("De-humidification Mode OFF \r\n");
							Reheat_Valve_Relay_OFF();
							printConsole("Re-heat Valve = OFF \r\n");
						}
						BleedOFF_Valve_Relay_ON();
						Compressor_ON();

						printConsole("Current State: High Cooling Mode \r\n ");
						printConsole("ID_FAN 1 = ON \r\n");
						printConsole("ID_FAN 2 = ON \r\n");
						printConsole("ID_FAN 3 = ON \r\n");
						printConsole("Reversing Valve = ON \r\n");
						printConsole("Re-heat Valve = OFF \r\n");
						printConsole("Bleed-off Valve = ON \r\n");
						if(Compressor_State == ON)
						{
							printConsole("Compressor = ON \r\n");
						}
						printf("\r\n");
					}
						break;

					case FAN_ONLY:
					{
						ID_FAN_1_Relay_ON();
					}
						break;

					case SOFT_LOCKOUT:
					{
						Sensor_Timer_Stop();
						ID_FAN_1_Relay_OFF();
						ID_FAN_2_Relay_OFF();
						ID_FAN_3_Relay_OFF();
						RV_Relay_OFF();
						Reheat_Valve_Relay_OFF();
						BleedOFF_Valve_Relay_OFF();
						Compressor_OFF();
						Soft_Lockout_Counter++;
						if(Soft_Lockout_Counter >= 3)
						{
							Current_State = HARD_LOCKOUT;
						}

						printConsole("Current State: Soft Lockout \r\n ");
						printConsole("Soft Lockout Counter = %d \r\n ",Soft_Lockout_Counter);
						printConsole("ID_FAN 1 = OFF \r\n");
						printConsole("ID_FAN 2 = OFF \r\n");
						printConsole("ID_FAN 3 = OFF \r\n");
						printConsole("Reversing Valve = OFF \r\n");
						printConsole("Re-heat Valve = OFF \r\n");
						printConsole("Bleed-off Valve = OFF \r\n");
						if(Compressor_State == OFF)
						{
							printConsole("Compressor = OFF \r\n");
						}
						printf("\r\n");

					}
						break;

					case HARD_LOCKOUT:
					{
						printConsole("Current State: Hard Lockout \r\n ");

						Current_State = HARD_LOCKOUT;

						switch (Current_Code) {
							case HP_FAULT:
								printConsole("High Pressure Fault \r\n ");
								break;
							case LP_FAULT:
								printConsole("Low Pressure Fault \r\n ");
								break;
							case CO1_FAULT:
								printConsole("CO1 Fault \r\n ");
								break;
							case CO2_FAULT:
								printConsole("CO2 Fault \r\n ");
								break;
							case CS_OVERFLOW_FAULT:
								printConsole("CS Overflow Fault \r\n ");
								break;
							case SWAPPED_THERMISTOR:
								printConsole("Swapped Thermistor Fault \r\n ");
								break;
							case TEMP_SENSOR_ERROR:
								printConsole("Temperature Sensor Fault \r\n ");
								break;
							case FAULT_RENTRY:
								printConsole("Fault Re-entry Fault \r\n ");
								break;
						}

						printf("\r\n");
					}
					break;

					case STANDBY:
					{
						ID_FAN_1_Relay_OFF();
						ID_FAN_2_Relay_OFF();
						ID_FAN_3_Relay_OFF();
						RV_Relay_OFF();
						Reheat_Valve_Relay_OFF();
						BleedOFF_Valve_Relay_OFF();
						Compressor_OFF();
						Current_Code = NO_FAULT;
						printConsole("Current State: Standby \r\n ");
						printConsole("ID_FAN 1 = OFF \r\n");
						printConsole("ID_FAN 2 = OFF \r\n");
						printConsole("ID_FAN 3 = OFF \r\n");
						printConsole("Reversing Valve = OFF \r\n");
						printConsole("Re-heat Valve = OFF \r\n");
						printConsole("Bleed-off Valve = OFF \r\n");
						printConsole("Compressor = OFF \r\n");

			 			if(CO1 <= 10.00)
			 			{
							Current_State = HARD_LOCKOUT;
							Current_Code = CO1_FAULT;
			 			}

						if(CO2 <= 10.00)
						{
							Current_State = HARD_LOCKOUT;
							Current_Code = CO2_FAULT;
						}

						if(Cond_SW == ON)
						{
							Current_State = HARD_LOCKOUT;
							Current_Code = CS_OVERFLOW_FAULT;
						}



					}
						break;



					case TRANSITION_STATE:
					{
						if((Current_Code == LOW_COOL_CODE))
						{
							Compressor_OFF();

							if(Antishort_Delay_Flag == OFF)
							{
								Current_State = HEATING_MODE_1;
								Current_Code = NO_FAULT;
							}
						}
						else if((Current_Code == LOW_HEAT_CODE))
						{
							Compressor_OFF();

							if(Antishort_Delay_Flag == OFF)
							{
								Current_State = COOLING_MODE_1;
								Current_Code = NO_FAULT;
							}
						}
						else if((Current_Code == HIGH_COOL_CODE))
						{
							Compressor_OFF();

							if(Antishort_Delay_Flag == OFF)
							{
								Current_State = HEATING_MODE_2;
								Current_Code = NO_FAULT;
							}
						}
						else if((Current_Code == HIGH_HEAT_CODE))
						{
							Compressor_OFF();

							if(Antishort_Delay_Flag == OFF)
							{
								Current_State = COOLING_MODE_2;
								Current_Code = NO_FAULT;
							}
						}
						else{
							Current_State = TRANSITION_STATE;
						}
					}
					break;

				}

				printConsole("CO1 Sensor = %f °C\r\n",CO1);
				printConsole("CO2 Sensor = %f °C\r\n",CO2);
				printConsole("CS = %f Ω \r\n",Cond_SW);
				printConsole("LP Switch = %d °C\r\n",LP_Flag);
				printConsole("HP Switch = %d °C\r\n",HP_Flag);
				printConsole("Over Voltage Fault = %d \r\n",OV_Flag);
				printConsole("Under Voltage Fault = %d \r\n",UV_Flag);

	}
}
