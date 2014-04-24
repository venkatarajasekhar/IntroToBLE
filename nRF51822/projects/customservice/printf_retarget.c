/**************************************************************************/
/*!
    @file     printf_retarget.c
*/
/**************************************************************************/
#include "common.h"
#include "app_uart.h"

/* Printf retargeting for GNU/GCC */
#if defined __GNUC__
/**************************************************************************/
/*!

*/
/**************************************************************************/
int puts(const char * str)
{
  while(*str)
  {
    if (CFG_PRINTF_NEWLINE[0] == '\r' && (*str) == '\n')
    {
      (void) app_uart_put('\r');
    }

    (void) app_uart_put(*str++);
  }

  return 0;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
//int getc ( FILE * stream )
//int getchar ( void )
//{
//  uint8_t c;
//
//  return ( NRF_SUCCESS == app_uart_get(&c) ) ? ((int) c) : 0;
//}
#endif

/* Printf retargeting for Keil uVision */
#ifdef __CC_ARM
/**************************************************************************/
/*!

*/
/**************************************************************************/
struct __FILE 
{
  uint32_t handle;
};

/**************************************************************************/
/*!

*/
/**************************************************************************/
int fgetc(FILE *f)
{
  uint8_t c;

  return ( NRF_SUCCESS == app_uart_get(&c) ) ? ((int) c) : 0;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
int fputc(int ch, FILE *f)
{
  if (CFG_PRINTF_NEWLINE[0] == '\r' &&
      ch == '\n')
  {
    (void) app_uart_put('\r');
  }

  (void) app_uart_put(ch);
  return ch;
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void _ttywrch(int ch)
{
  if (CFG_PRINTF_NEWLINE[0] == '\r' &&
      ch == '\n')
  {
    (void) app_uart_put('\r');
  }

  (void) app_uart_put(ch);
}
#endif
