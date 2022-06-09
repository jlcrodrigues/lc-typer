#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

/** @defgroup driver rtc
 * @{
 *
 * Functions related to the real time clock.
 */

/* Registers and IRQ */
#define RTC_IRQ 8
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define DAY_REG 0X7
#define MONTH_REG 0X8
#define YEAR_REG 0X9

/* Register masks */

// Register A
#define UIP BIT(7)

// Register B
#define PIE BIT(6)
#define AIE BIT(5)
#define UIE BIT(4)

// Register C
#define IRQF BIT(7)
#define UF BIT(4)

#define DATE_STR_SIZE 11

/**
 * @brief Subscribe real time clock interrupts.
 * @param bit_no Receives the bit that will be set for rtc interrupts.
 * @return Returns 0 upon success, and 1 otherwise.
 */
int rtc_subscribe_int(uint8_t* bit_no);

/**
 * @brief Unsubscribe RTC interrupts.
 * @return Returns 0 upon success, and 1 otherwise.
 */
int rtc_unsubscribe_int(void);

/**
 * @brief Initializes the RTC. Call this function before starting to use it.
 * 
 * @return Returns 0 upon success, and 1 otherwise.
 */
int rtc_init(void);

/**
 * @brief Handle RTC interrupts.
 * For update interrupts, the data variables are updates and no
 * further action is needed.
 * 
 */
void rtc_ih(void);

/**
 * @brief Update the data variables from the rtc registers.
 * 
 * @return int 0 upon success, non-zero otherwise.
 */
int rtc_read_data_reg(void);

/**
 * @brief Get the current date from the RTC.
 * 
 * @return char* Current date in dd/mm/yyyy string format.
 */
char* rtc_get_date_str(void);

/**
 * @brief Read an rtc register.
 * 
 * @param reg Register number. From 0xA to 0xD.
 * @param byte Pointer variable to store read value.
 * @return int 0 upon success, non-zero otherwise.
 */
int (rtc_read_register)(uint8_t reg, uint8_t* byte);

/**
 * @brief Set an rtc register.
 * 
 * @param reg Register number. From 0xA to 0xD.
 * @param byte Value to be written.
 * @return int 0 upon success, non-zero otherwise.
 */
int (rtc_write_register)(uint8_t reg, uint8_t byte);

/**@}*/

#endif
