#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "usbd_cdc_if.h"
// #include "stm32f4xx.h"  // CMSIS-compliant header file for the MCU used
// #include "stm32f4xx_hal_usart.h" 

extern char _end;  // Defined in the linker script
// static char *heap_end = &_end;  // Current end of the heap
// static char *heap_limit = &_end + 0x1000; // Set a heap limit (adjust as needed)

// extern UART_HandleTypeDef huart2;


int _write(int file, char *data, int len) {
    for (volatile int i = 0; i < len; i++) {
        // // Wait until the transmit buffer is empty
        // while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        // // Send the character
        // USART_SendData(USART2, data[i]);
        // HAL_UART_Transmit(&huart2, (uint8_t *)&data, 1, HAL_MAX_DELAY);
        while (CDC_Transmit_FS((uint8_t*)data, len) != USBD_OK) {
            // HAL_Delay(4);  
        }
    }
    return len;  // Return the length of the transmitted string
}

// int __io_putchar(int ch) {
//     HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//     return ch;
// }



// int _close(int file) {
//     return -1;  // Not supported
// }

// int _fstat(int file, struct stat *st) {
//     st->st_mode = S_IFCHR;  // Character device
//     return 0;
// }

// int _isatty(int file) {
//     return 1;  // Assuming output is always to a terminal
// }

// off_t _lseek(int file, off_t offset, int whence) {
//     return 0;  // Not supported
// }

// int _read(int file, char *data, int len) {
//     errno = EIO;
//     return -1;  // Not supported
// }


// void *_sbrk(ptrdiff_t incr) {
//     char *prev_heap_end = heap_end;

//     // Check if the heap limit is exceeded
//     if (heap_end + incr > heap_limit) {
//         errno = ENOMEM; // Out of memory
//         return (void *)-1; // Indicate allocation failure
//     }

//     heap_end += incr;
//     return (void *)prev_heap_end; // Return the previous heap end
// }