#ifndef _status_data_h_
#define _status_data_h_

struct Status {
  float probe_temperature;
  float ambient_temperature;
  float battery_voltage;
  float battery_soc;
  char ip_address[16];
};

#endif