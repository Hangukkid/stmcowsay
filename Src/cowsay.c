#include "cowsay.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "string.h"

void drawTextBox (uint8_t *message, int size) {

  uint8_t end_of_line[] = "\n\r";
  
  uint8_t top_of_textbox[] = " ___________________________________________\n\r";  
  uint8_t bottom_of_textbox[] = " ------------------------------------------\n\r";
  
  uint8_t top_line[] = "/ ";                              //You have Egyptian flu: you're going to \\ \n\r";
  uint8_t bottom_line[] = "\\ ";                          //be a mummy.                            / \n\r";
  
  uint8_t top_text[43];
  uint8_t bottom_text[43];
  
  for (int i = 0; i < 43; i++) {
    top_text[i] = ' ';
  }
  for (int i = 0; i < 43; i++) {
    bottom_text[i] = ' ';
  }
  
  for (int i = 0; i < size; i++) {
    if (i < 40) {
      top_text[i] = message[i];
    } else if (i < 80 && i >= 40) {
      bottom_text[i-40] = message[i];
    }
  }
  
  top_text[42] = '\\';
  bottom_text[42] = '/';
  
  HAL_UART_Transmit(&huart2, top_of_textbox, sizeof(top_of_textbox), 100);
  
  HAL_UART_Transmit(&huart2, top_line, sizeof(top_line), 100);
  HAL_UART_Transmit(&huart2, top_text, sizeof(top_text), 100);
  
  HAL_UART_Transmit(&huart2, end_of_line, sizeof(end_of_line), 100);
  
  HAL_UART_Transmit(&huart2, bottom_line, sizeof(bottom_line), 100);
  HAL_UART_Transmit(&huart2, bottom_text, sizeof(bottom_text), 100);
  
  HAL_UART_Transmit(&huart2, end_of_line, sizeof(end_of_line), 100);
  
  HAL_UART_Transmit(&huart2, bottom_of_textbox, sizeof(bottom_of_textbox), 100);
}


void drawCow () {
  uint8_t cow1[] = "        \\  ^__^ \n\r";
  uint8_t cow2[] = "         \\ (oo)\\_______ \n\r";
  uint8_t cow3[] = "           (__)\\      )\\/\\ \n\r";
  uint8_t cow4[] = "               ||----w | \n\r";
  uint8_t cow5[] = "               ||     || \n\r";
  HAL_UART_Transmit(&huart2, cow1, sizeof(cow1), 100);
  HAL_UART_Transmit(&huart2, cow2, sizeof(cow2), 100);
  HAL_UART_Transmit(&huart2, cow3, sizeof(cow3), 100);
  HAL_UART_Transmit(&huart2, cow4, sizeof(cow4), 100);
  HAL_UART_Transmit(&huart2, cow5, sizeof(cow5), 100);
}

void receiveInput (uint8_t *message, int size) {
  clearString(message, size);
  
  uint8_t temp[1] = "`";
  uint8_t end_of_line[] = "\n\r";
  
  uint8_t welcome[] = "What does the cow say?: ";
  HAL_UART_Transmit(&huart2, welcome, sizeof(welcome), 100);
  
  int count = 0;
  while (1) {
    HAL_UART_Receive(&huart2, temp, sizeof(temp), 100);
    if (temp[0] != '`') {
      if (temp[0] == '\r') {
        HAL_UART_Transmit(&huart2, end_of_line, sizeof(end_of_line), 100);
        HAL_UART_Transmit(&huart2, temp, sizeof(temp), 100);
        break;
      } else {
        message[count] = temp[0];
        count++;
        HAL_UART_Transmit(&huart2, temp, sizeof(temp), 100);
        temp[0] = '`';
      }
    }
  }
}

void clearString (uint8_t *message, int size) {
  for (int i = 0; i < size; i++) {
    message[i] = ' ';
  }
}