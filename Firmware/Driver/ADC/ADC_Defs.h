/**
 * @file ADC_Defs.h
 * @author Kunal Salvi (kunalsalviusu@gmail.com)
 * @brief  The variables used to configure the ADC are declared in this file.
 *         Use these configurations only.
 *         
 * @version 0.1
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ADC_DEFS_H_
#define ADC_DEFS_H_

#include "main.h"
#include "ADC.h"

/**
 * @brief Enable/Disable configuration for an ADC channel.
 * 
 * This struct is used in the `_ADC_Channel_` struct. It allows enabling
 * or disabling a particular channel of the ADC.
 * 
 * @see _ADC_Channel_
 */
typedef struct _ADC_Channel_Enable_Disable_{
    bool Enable;   /**< Enable the ADC channel */
    bool Disable;  /**< Disable the ADC channel */
}_ADC_Channel_Enable_Disable_;

/**
 * @brief Sequence number configuration for ADC channels.
 * 
 * This struct is used in the `_ADC_Channel_` struct to set the sequence
 * numbers for multiple ADC channels.
 * 
 * @see _ADC_Channel_
 */
typedef struct _ADC_Channel_Sequence_Number_{
    uint8_t Sequence_1;   /**< Sequence number for ADC channel 1 */
    uint8_t Sequence_2;   /**< Sequence number for ADC channel 2 */
    uint8_t Sequence_3;   /**< Sequence number for ADC channel 3 */
    uint8_t Sequence_4;   /**< Sequence number for ADC channel 4 */
    uint8_t Sequence_5;   /**< Sequence number for ADC channel 5 */
    uint8_t Sequence_6;   /**< Sequence number for ADC channel 6 */
    uint8_t Sequence_7;   /**< Sequence number for ADC channel 7 */
    uint8_t Sequence_8;   /**< Sequence number for ADC channel 8 */
    uint8_t Sequence_9;   /**< Sequence number for ADC channel 9 */
    uint8_t Sequence_10;  /**< Sequence number for ADC channel 10 */
    uint8_t Sequence_11;  /**< Sequence number for ADC channel 11 */
    uint8_t Sequence_12;  /**< Sequence number for ADC channel 12 */
    uint8_t Sequence_13;  /**< Sequence number for ADC channel 13 */
    uint8_t Sequence_14;  /**< Sequence number for ADC channel 14 */
    uint8_t Sequence_15;  /**< Sequence number for ADC channel 15 */
    uint8_t Sequence_16;  /**< Sequence number for ADC channel 16 */
}_ADC_Channel_Sequence_Number_;

/**
 * @brief Sample time configuration for an ADC channel.
 *
 * This struct provides an easy way to set the sample time of an ADC channel.
 * All options selected will have an additional 12 cycles added to them in
 * hardware. For example, if `_3_Cycles` is selected, the total cycles taken
 * to complete one conversion of that channel will be 3 + 12 = 15 cycles.
 * 
 * This struct is used in the `_ADC_Channel_` struct.
 * 
 * @see _ADC_Channel_
 */
typedef struct _ADC_Channel_Sample_Time_{
    uint8_t _3_Cycles;    /**< 3 cycles + 12 additional cycles */
    uint8_t _15_Cycles;   /**< 15 cycles + 12 additional cycles */
    uint8_t _28_Cycles;   /**< 28 cycles + 12 additional cycles */
    uint8_t _56_Cycles;   /**< 56 cycles + 12 additional cycles */
    uint8_t _84_Cycles;   /**< 84 cycles + 12 additional cycles */
    uint8_t _112_Cycles;  /**< 112 cycles + 12 additional cycles */
    uint8_t _144_Cycles;  /**< 144 cycles + 12 additional cycles */
    uint8_t _480_Cycles;  /**< 480 cycles + 12 additional cycles */
}_ADC_Channel_Sample_Time_;

/**
 * @brief ADC channel configuration structure.
 *
 * This struct encapsulates all the necessary configurations needed for any ADC channel.
 * 
 * @param Enable         Enable/Disable settings for the ADC channel.
 * @param Sequence_Number Sequence number settings for the ADC channel.
 * @param Sample_Time    Sample time settings for the ADC channel.
 * 
 * @see _ADC_Channel_Enable_Disable_
 * @see _ADC_Channel_Sequence_Number_
 * @see _ADC_Channel_Sample_Time_
 */
typedef struct _ADC_Channel_{
    _ADC_Channel_Enable_Disable_ Enable;
    _ADC_Channel_Sequence_Number_ Sequence_Number;
    _ADC_Channel_Sample_Time_ Sample_Time;
}_ADC_Channel_;

/**
 * @brief ADC conversion mode selection.
 *
 * This struct helps select the mode in which the conversions will happen.
 * 
 * @attention When an external trigger is used (i.e., `Regular_External_Trigger_Enable` or
 * `Injected_External_Trigger_Enable` is configured to be enabled), make sure to
 * select "Single" instead of "Continuous".
 * 
 * @see ADC_Configuration
 */
typedef struct ADC_Mode
{
    uint8_t Single;      /**< Single conversion mode */
    uint8_t Continuous;  /**< Continuous conversion mode */
}ADC_Mode;

/**
 * @brief ADC channel type selection.
 *
 * This struct is used to select whether the channel is a regular or injected channel.
 */
typedef struct ADC_Channel_Type{
    uint8_t Regular;    /**< Regular ADC channel */
    uint8_t Injected;   /**< Injected ADC channel */
}ADC_Channel_Type;

static const struct ADC_Configuration{

    struct Port{
        ADC_TypeDef *_ADC1_;  /**< Pointer to ADC1 */
        ADC_TypeDef *_ADC2_;  /**< Pointer to ADC2 */
        ADC_TypeDef *_ADC3_;  /**< Pointer to ADC3 */
    }Port;

    struct Data_Alignment{
        uint8_t Left_Justified;   /**< Left-justified data alignment */
        uint8_t Right_Justified;  /**< Right-justified data alignment */
    }Data_Alignment;

    _ADC_Channel_ Channel;

    struct Conversion_Mode{
        uint8_t Single;       /**< Single conversion mode */
        uint8_t Continuous;   /**< Continuous conversion mode */
    }Conversion_Mode;

    ADC_Channel_Type Channel_Type;

    struct Resolution{
        uint8_t Bit_12;  /**< 12-bit resolution */
        uint8_t Bit_10;  /**< 10-bit resolution */
        uint8_t Bit_8;   /**< 8-bit resolution */
        uint8_t Bit_6;   /**< 6-bit resolution */
    }Resolution;

    struct Regular_External_Trigger_Enable{
        uint8_t Trigger_Disable;          /**< Disable external trigger */
        uint8_t Trigger_On_Rising_Edge;   /**< Trigger on rising edge */
        uint8_t Trigger_On_Falling_Edge;  /**< Trigger on falling edge */
        uint8_t Trigger_On_Both_Edges;    /**< Trigger on both edges */
    }Regular_External_Trigger_Enable;

    struct Regular_External_Trigger_Event{
        uint8_t Timer_1_CC1;  /**< Timer 1 CC1 event */
        uint8_t Timer_1_CC2;  /**< Timer 1 CC2 event */
        uint8_t Timer_1_CC3;  /**< Timer 1 CC3 event */
        uint8_t Timer_2_CC2;  /**< Timer 2 CC2 event */
        uint8_t Timer_2_CC3;  /**< Timer 2 CC3 event */
        uint8_t Timer_2_CC4;  /**< Timer 2 CC4 event */
        uint8_t Timer_2_TRGO; /**< Timer 2 TRGO event */
        uint8_t Timer_3_CC1;  /**< Timer 3 CC1 event */
        uint8_t Timer_3_TRGO; /**< Timer 3 TRGO event */
        uint8_t Timer_4_CC4;  /**< Timer 4 CC4 event */
        uint8_t Timer_5_CC1;  /**< Timer 5 CC1 event */
        uint8_t Timer_5_CC2;  /**< Timer 5 CC2 event */
        uint8_t Timer_5_CC3;  /**< Timer 5 CC3 event */
        uint8_t Timer_8_CC1;  /**< Timer 8 CC1 event */
        uint8_t Timer_8_TRGO; /**< Timer 8 TRGO event */
        uint8_t EXTI_11;      /**< EXTI line 11 event */
    }Regular_External_Trigger_Event;

    struct Injected_External_Trigger_Event{
        uint8_t Timer_1_CC4;  /**< Timer 1 CC4 event */
        uint8_t Timer_1_TRGO; /**< Timer 1 TRGO event */
        uint8_t Timer_2_CC1;  /**< Timer 2 CC1 event */
        uint8_t Timer_2_TRGO; /**< Timer 2 TRGO event */
        uint8_t Timer_3_CC2;  /**< Timer 3 CC2 event */
        uint8_t Timer_3_CC4;  /**< Timer 3 CC4 event */
        uint8_t Timer_4_CC1;  /**< Timer 4 CC1 event */
        uint8_t Timer_4_CC2;  /**< Timer 4 CC2 event */
        uint8_t Timer_4_CC3;  /**< Timer 4 CC3 event */
        uint8_t Timer_4_TRGO; /**< Timer 4 TRGO event */
        uint8_t Timer_5_CC4;  /**< Timer 5 CC4 event */
        uint8_t Timer_5_TRGO; /**< Timer 5 TRGO event */
        uint8_t Timer_8_CC2;  /**< Timer 8 CC2 event */
        uint8_t Timer_8_CC3;  /**< Timer 8 CC3 event */
        uint8_t Timer_8_CC4;  /**< Timer 8 CC4 event */
        uint8_t EXTI_15;      /**< EXTI line 15 event */
    }Injected_External_Trigger_Event;

    struct _Watchdog_Analog_{

        ADC_Channel_Type Channel_Type;

        bool Enable;   /**< Enable the watchdog */
        bool Disable;  /**< Disable the watchdog */

        struct Channel_Scan
        {
            bool All_Channels;     /**< Watchdog monitors all channels */
            bool Single_Channel;   /**< Watchdog monitors a single channel */
        }Channel_Scan;

    }_Watchdog_Analog_;

}ADC_Configuration = {

    .Channel_Type = {
        .Regular = 0,
        .Injected = 1,
    },

    .Data_Alignment = {
        .Left_Justified = 1,
        .Right_Justified = 0,
    },

    .Port = {
        ._ADC1_ = ADC1,
        ._ADC2_ = ADC2,
        ._ADC3_ = ADC3,
    },

    .Conversion_Mode = {
        .Single = 1,
        .Continuous = 2,
    },

    .Regular_External_Trigger_Enable = {
        .Trigger_Disable = 0,
        .Trigger_On_Rising_Edge = 1,
        .Trigger_On_Falling_Edge = 2,
        .Trigger_On_Both_Edges = 3,
    },

    .Regular_External_Trigger_Event = {
        .Timer_1_CC1 = 0,
        .Timer_1_CC2 = 1,
        .Timer_1_CC3 = 2,
        .Timer_2_CC2 = 3,
        .Timer_2_CC3 = 4,
        .Timer_2_CC4 = 5,
        .Timer_2_TRGO = 6,
        .Timer_3_CC1 = 7,
        .Timer_3_TRGO = 8,
        .Timer_4_CC4 = 9,
        .Timer_5_CC1 = 10,
        .Timer_5_CC2 = 11,
        .Timer_5_CC3 = 12,
        .Timer_8_CC1 = 13,
        .Timer_8_TRGO = 14,
        .EXTI_11 = 15,
    },

    .Channel = {
        .Enable = {
            .Enable = 1,
            .Disable = 0,
        },

        .Sequence_Number = {
            .Sequence_1 = 0,
            .Sequence_2 = 1,
            .Sequence_3 = 2,
            .Sequence_4 = 3,
            .Sequence_5 = 4,
            .Sequence_6 = 5,
            .Sequence_7 = 6,
            .Sequence_8 = 7,
            .Sequence_9 = 8,
            .Sequence_10 = 9,
            .Sequence_11 = 10,
            .Sequence_12 = 11,
            .Sequence_13 = 12,
            .Sequence_14 = 13,
            .Sequence_15 = 14,
            .Sequence_16 = 15,
        },
        .Sample_Time = {
            ._3_Cycles = 0,
            ._15_Cycles = 1,
            ._28_Cycles = 2,
            ._56_Cycles = 3,
            ._84_Cycles = 4,
            ._112_Cycles = 5,
            ._144_Cycles = 6,
            ._480_Cycles = 7,
        },
    },

};



#endif /* ADC_DEFS_H_ */
