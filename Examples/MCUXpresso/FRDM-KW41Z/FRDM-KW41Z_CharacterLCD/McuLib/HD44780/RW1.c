/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : RW1.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : SDK_BitIO
**     Version     : Component 01.025, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-01-25, 05:31, # CodeGen: 405
**     Abstract    :
**          GPIO component usable with NXP SDK
**     Settings    :
**          Component name                                 : RW1
**          SDK                                            : McuLib
**          GPIO Name                                      : GPIOA
**          PORT Name                                      : PORTA
**          Pin Number                                     : 0
**          Pin Symbol                                     : LED_RED
**          Do Pin Muxing                                  : no
**          Init Direction                                 : Output
**          Pull Resistor                                  : no pull resistor
**          Init Value                                     : 0
**     Contents    :
**         GetDir    - bool RW1_GetDir(void);
**         SetDir    - void RW1_SetDir(bool Dir);
**         SetInput  - void RW1_SetInput(void);
**         SetOutput - void RW1_SetOutput(void);
**         GetVal    - bool RW1_GetVal(void);
**         PutVal    - void RW1_PutVal(bool Val);
**         ClrVal    - void RW1_ClrVal(void);
**         SetVal    - void RW1_SetVal(void);
**         NegVal    - void RW1_NegVal(void);
**         Init      - void RW1_Init(void);
**         Deinit    - void RW1_Deinit(void);
**
** * Copyright (c) 2015-2019, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file RW1.h
** @version 01.00
** @brief
**          GPIO component usable with NXP SDK
*/         
/*!
**  @addtogroup RW1_module RW1 module documentation
**  @{
*/         

/* MODULE RW1. */

#include "RW1.h"
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if RW1_CONFIG_DO_PIN_MUXING
  #include "fsl_port.h" /* include SDK header file for port muxing */
  #endif
  #include "fsl_gpio.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  #include "fsl_gpio_driver.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  #include "pins_gpio_hw_access.h"
  #include "pins_driver.h" /* include SDK header file for GPIO */
#else
  #error "Unsupported SDK!"
#endif

#if McuLib_CONFIG_NXP_SDK_2_0_USED

  static const gpio_pin_config_t RW1_configOutput = {
    kGPIO_DigitalOutput,  /* use as output pin */
    RW1_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };

  static const gpio_pin_config_t RW1_configInput = {
    kGPIO_DigitalInput,  /* use as input pin */
    RW1_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  const gpio_output_pin_user_config_t RW1_OutputConfig[] = {
    {
      .pinName = RW1_CONFIG_PIN_SYMBOL,
      .config.outputLogic = RW1_CONFIG_INIT_PIN_VALUE,
    #if FSL_FEATURE_PORT_HAS_SLEW_RATE
      .config.slewRate = kPortSlowSlewRate,
    #endif
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
      .config.isOpenDrainEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
      .config.driveStrength = kPortLowDriveStrength,
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };

  const gpio_input_pin_user_config_t RW1_InputConfig[] = {
    {
      .pinName = RW1_CONFIG_PIN_SYMBOL,
    #if FSL_FEATURE_PORT_HAS_PULL_ENABLE
      #if RW1_CONFIG_PULL_RESISTOR==0 /* 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
      .config.isPullEnable = false,
      #else
      .config.isPullEnable = true,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PULL_SELECTION
      #if RW1_CONFIG_PULL_RESISTOR==1
      .config.pullSelect = kPortPullUp,
      #else
      .config.pullSelect = kPortPullDown,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
      .config.isPassiveFilterEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
      .config.isDigitalFilterEnabled = true,
    #endif
    #if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
      .config.interrupt = kPortIntDisabled
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };
#endif

static bool RW1_isOutput = false;
/*
** ===================================================================
**     Method      :  ClrVal (component SDK_BitIO)
**
**     Description :
**         Clears the pin value (sets it to a low level)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_ClrVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_ClearPinsOutput(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortClear(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_ClearPinOutput(RW1_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, 0);
#endif
}

/*
** ===================================================================
**     Method      :  SetVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value to a high value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_SetVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_SetPinsOutput(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortSet(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinOutput(RW1_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, 1);
#endif
}

/*
** ===================================================================
**     Method      :  NegVal (component SDK_BitIO)
**
**     Description :
**         Toggles/negates the pin value
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_NegVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_SDK_VERSION < 250
  GPIO_TogglePinsOutput(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortToggle(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_TogglePinOutput(RW1_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsOutput(RW1_CONFIG_PORT_NAME);
  if (val&(1<<RW1_CONFIG_PIN_NUMBER)) {
    PINS_GPIO_WritePin(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, 0);
  } else {
    PINS_GPIO_WritePin(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, 1);
  }
#endif
}

/*
** ===================================================================
**     Method      :  GetVal (component SDK_BitIO)
**
**     Description :
**         Returns the pin value
**     Parameters  : None
**     Returns     :
**         ---             - Returns the value of the pin:
**                           FALSE/logical level '0' or TRUE/logical
**                           level '1'
** ===================================================================
*/
bool RW1_GetVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  return GPIO_ReadPinInput(RW1_CONFIG_GPIO_NAME, RW1_CONFIG_PIN_NUMBER)!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  return GPIO_DRV_ReadPinInput(RW1_CONFIG_PIN_SYMBOL)!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  return (PINS_DRV_ReadPins(RW1_CONFIG_PORT_NAME)&(1<<RW1_CONFIG_PIN_NUMBER))!=0;
#else
  return FALSE;
#endif
}

/*
** ===================================================================
**     Method      :  GetDir (component SDK_BitIO)
**
**     Description :
**         Return the direction of the pin (input/output)
**     Parameters  : None
**     Returns     :
**         ---             - FALSE if port is input, TRUE if port is
**                           output
** ===================================================================
*/
bool RW1_GetDir(void)
{
  return RW1_isOutput;
}

/*
** ===================================================================
**     Method      :  SetDir (component SDK_BitIO)
**
**     Description :
**         Sets the direction of the pin (input or output)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Dir             - FALSE: input, TRUE: output
**     Returns     : Nothing
** ===================================================================
*/
void RW1_SetDir(bool Dir)
{
  if (Dir) {
    RW1_SetOutput();
  } else {
    RW1_SetInput();
  }
}

/*
** ===================================================================
**     Method      :  SetInput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as input
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_SetInput(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(RW1_CONFIG_GPIO_NAME, RW1_CONFIG_PIN_NUMBER, &RW1_configInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(RW1_CONFIG_PIN_SYMBOL, kGpioDigitalInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(RW1_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val &= ~(1<<RW1_CONFIG_PIN_NUMBER); /* clear bit ==> input */
  PINS_DRV_SetPinsDirection(RW1_CONFIG_PORT_NAME, val);
#endif
  RW1_isOutput = false;
}

/*
** ===================================================================
**     Method      :  SetOutput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as output
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_SetOutput(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(RW1_CONFIG_GPIO_NAME, RW1_CONFIG_PIN_NUMBER, &RW1_configOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(RW1_CONFIG_PIN_SYMBOL, kGpioDigitalOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(RW1_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val |= (1<<RW1_CONFIG_PIN_NUMBER); /* set bit ==> output */
  PINS_DRV_SetPinsDirection(RW1_CONFIG_PORT_NAME, val);
#endif
  RW1_isOutput = true;
}

/*
** ===================================================================
**     Method      :  PutVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Value to set. FALSE/logical '0' or
**                           TRUE/logical '1'
**     Returns     : Nothing
** ===================================================================
*/
void RW1_PutVal(bool Val)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  if (Val) {
    GPIO_SetPinsOutput(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  } else {
    GPIO_ClearPinsOutput(RW1_CONFIG_GPIO_NAME, 1<<RW1_CONFIG_PIN_NUMBER);
  }
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_WritePinOutput(RW1_CONFIG_PIN_SYMBOL, Val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_DRV_WritePin(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, Val);
#endif
}

/*
** ===================================================================
**     Method      :  Init (component SDK_BitIO)
**
**     Description :
**         Driver initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_Init(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if RW1_CONFIG_DO_PIN_MUXING
  PORT_SetPinMux(RW1_CONFIG_PORT_NAME, RW1_CONFIG_PIN_NUMBER, kPORT_MuxAsGpio); /* mux as GPIO */
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  /*! \todo Pin Muxing not implemented */
  GPIO_DRV_Init(RW1_InputConfig, RW1_OutputConfig);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  /* the following needs to be called in the application first:
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  */
#endif
#if RW1_CONFIG_INIT_PIN_DIRECTION == RW1_CONFIG_INIT_PIN_DIRECTION_INPUT
  RW1_SetInput();
#elif RW1_CONFIG_INIT_PIN_DIRECTION == RW1_CONFIG_INIT_PIN_DIRECTION_OUTPUT
  RW1_SetOutput();
#endif
}

/*
** ===================================================================
**     Method      :  Deinit (component SDK_BitIO)
**
**     Description :
**         Driver de-initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RW1_Deinit(void)
{
  /* nothing needed */
}

/* END RW1. */

/*!
** @}
*/
