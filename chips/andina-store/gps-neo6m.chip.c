  // For information and examples see:
  // https://link.wokwi.com/custom-chips-alpha
  //
  // SPDX-License-Identifier: MIT
  // Copyright (C) 2022 Uri Shaked / wokwi.com

  // https://wokwi.com/makers/urish

  // original project https://wokwi.com/projects/333785509332517459

  #include "wokwi-api.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>    // contains strlen() function

  #define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))    // macro

  #define SECOND 5000000    // micros

  // A NMEA 0183 sentence can have a maximum of 80 characters plus a
  // carriage return and a line feed

  
 const char gps_tx_data[][80] = { // "$GPGGA,202322.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*60\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202322.603,A,1204.664,S,07659.900,W,000.1,195.1,191124,000.0,W*77\r\n",
    "$GPGGA,202323.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*61\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202323.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*7A\r\n",
    "$GPGGA,202324.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202324.603,A,1204.664,S,07659.900,W,000.1,090.0,191124,000.0,W*74\r\n",
    "$GPGGA,202325.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*67\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202325.603,A,1204.664,S,07659.900,W,000.1,090.0,191124,000.0,W*75\r\n",
    "$GPGGA,202326.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*64\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202326.603,A,1204.664,S,07659.900,W,000.1,270.0,191124,000.0,W*7A\r\n",
    "$GPGGA,202327.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*65\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202327.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*7E\r\n",
    "$GPGGA,202328.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6A\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202328.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*70\r\n",
    "$GPGGA,202329.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6B\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202329.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*71\r\n",
    "$GPGGA,202330.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*63\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202330.603,A,1204.664,S,07659.900,W,000.1,045.0,191124,000.0,W*79\r\n",
    "$GPGGA,202331.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*62\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202331.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*79\r\n",
    "$GPGGA,202332.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*61\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202332.603,A,1204.664,S,07659.900,W,000.1,090.0,191124,000.0,W*73\r\n",
    "$GPGGA,202333.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*60\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202333.603,A,1204.664,S,07659.900,W,000.1,090.0,191124,000.0,W*72\r\n",
    "$GPGGA,202334.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*67\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202334.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*7C\r\n",
    "$GPGGA,202335.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202335.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7C\r\n",
    "$GPGGA,202336.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*65\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202336.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7F\r\n",
    "$GPGGA,202337.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*64\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202337.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7E\r\n",
    "$GPGGA,202338.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6B\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202338.603,A,1204.664,S,07659.900,W,000.1,225.0,191124,000.0,W*75\r\n",
    "$GPGGA,202339.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6A\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202339.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*71\r\n",
    "$GPGGA,202340.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*64\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202340.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*7F\r\n",
    "$GPGGA,202341.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*65\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202341.603,A,1204.664,S,07659.900,W,000.1,000.0,191124,000.0,W*7E\r\n",
    "$GPGGA,202342.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202342.603,A,1204.664,S,07659.900,W,000.2,243.4,191124,000.0,W*7F\r\n",
    "$GPGGA,202343.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*67\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202343.603,A,1204.664,S,07659.900,W,000.2,000.0,191124,000.0,W*7F\r\n",
    "$GPGGA,202344.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*60\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202344.603,A,1204.664,S,07659.900,W,000.2,108.4,191124,000.0,W*75\r\n",
    "$GPGGA,202345.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*61\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202345.603,A,1204.664,S,07659.900,W,000.2,333.4,191124,000.0,W*7E\r\n",
    "$GPGGA,202346.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*62\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202346.603,A,1204.664,S,07659.900,W,000.2,000.0,191124,000.0,W*7A\r\n",
    "$GPGGA,202347.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*63\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202347.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*79\r\n",
    "$GPGGA,202348.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6C\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202348.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*76\r\n",
    "$GPGGA,202349.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6D\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202349.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*77\r\n",
    "$GPGGA,202350.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*65\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202350.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7F\r\n",
    "$GPGGA,202351.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*64\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202351.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7E\r\n",
    "$GPGGA,202352.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*67\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202352.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7D\r\n",
    "$GPGGA,202353.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202353.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7C\r\n",
    "$GPGGA,202354.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*61\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202354.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7B\r\n",
    "$GPGGA,202355.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*60\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202355.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7A\r\n",
    "$GPGGA,202356.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*63\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202356.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*79\r\n",
    "$GPGGA,202357.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*62\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202357.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*78\r\n",
    "$GPGGA,202358.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6D\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202358.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*77\r\n",
    "$GPGGA,202359.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*6C\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202359.603,A,1204.664,S,07659.900,W,000.3,270.0,191124,000.0,W*70\r\n",
    "$GPGGA,202400.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*67\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202400.603,A,1204.664,S,07659.900,W,000.3,000.0,191124,000.0,W*7E\r\n",
    "$GPGGA,202401.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202401.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7C\r\n",
    "$GPGGA,202402.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*65\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202402.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7F\r\n",
    "$GPGGA,202403.603,1204.664,S,07659.900,W,1,12,1.0,0.0,M,0.0,M,,*64\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,202403.603,A,1204.664,S,07659.900,W,000.0,000.0,191124,000.0,W*7E\r\n"
  };

  typedef struct {
    uart_dev_t uart0;
    uint32_t   gps_tx_index;
  } chip_state_t;


  static void chip_timer_event  (void *user_data);


  void chip_init(void) {

    setvbuf(stdout, NULL, _IOLBF, 1024);                // ???     // Disable buffering for debug logs

    chip_state_t *chip = malloc(sizeof(chip_state_t));

    const uart_config_t uart_config = {
      .tx         = pin_init("TX", INPUT_PULLUP),
      .rx         = pin_init("RX", INPUT),
      .baud_rate  = 9600,
      .user_data  = chip,
    };

    chip->uart0        = uart_init(&uart_config);
  
    chip->gps_tx_index = 0;

    const timer_config_t timer_config = {
      .callback  = chip_timer_event,
      .user_data = chip,
    };

    timer_t timer = timer_init(&timer_config);

    timer_start(timer, SECOND, true);

    printf("GPS Chip initialized!\n");         // prints to web browser console (developer tools)

  }

  void chip_timer_event(void *user_data) {

    chip_state_t *chip = (chip_state_t*) user_data;

    printf("chip_timer_event\n");
//  printf ("LEN(gps_tx_data):  %d\n", LEN(gps_tx_data)   );    // number of messages
//  printf ("message length  :  %d\n", strlen(message)    );    // actual message length
//  printf ("gps_tx_index    :  %u\n", chip->gps_tx_index );    // message index

    const char * message = gps_tx_data[chip->gps_tx_index++];

    uart_write(chip->uart0, (uint8_t *) message, strlen(message));

    if (chip->gps_tx_index >= LEN(gps_tx_data)) {       
      chip->gps_tx_index = 0;
    }
  }

