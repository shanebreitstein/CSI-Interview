#include <Wire.h>
#include <unordered_map>
#include <array>
#define ADAU_ADDR 0x34
const int NUM_CHANNELS = 2;
const int FS = 48000;
uint16_t dspControlReg = 0x081C;

uint16_t PanLeftAddr[]= {0x0004, 0x0008};
uint16_t PanRightAddr[] = {0x0006, 0x000A};
uint16_t faderAddr[] = {0x0002, 0x0003};
int potPins[] = {A0, A1, A2, A3};

struct Channel {
    float gain = 1;

    float HF_gain = 1;
    float HF_freq = 12000.0;
    float HF_Q = 1.41;

    float MF_gain = 1;
    float MF_freq = 4000.0;
    float MF_Q = 1.41;

    float LF_gain = 1;
    float LF_freq = 80.0;
    float LF_Q = 1.41;

    //float filterCoeff[5] = {1, 0, 0, 0, 0};
    float fader = 1;
    float pan = 45.0; // in degrees [0 to 90] where 0 is hardpanned left
    // float panCoeff[2] = {sin(M_PI/4), sin(M_PI/4)}; // [0] = L, [1] = R
};

struct Channel_Addrs {
    uint16_t gain;
    std::array<uint16_t, 5> HF;
    std::array<uint16_t, 5> MF;
    std::array<uint16_t, 5> LF;
    uint16_t fader;
    std::array<uint16_t, 2> pan;

};

struct Channel channels[NUM_CHANNELS];
struct Channel_Addrs ch_addrs[NUM_CHANNELS];

void setPan(float angle, int channel) { // angle is from 0 to 90, 0 is hardpanned left
    float angle_R = angle * M_PI / 180.0;

    float leftAmp = cos(angle_R);
    float rightAmp = sin(angle_R);
    uint32_t panInts[2];
    panInts[0] = floatToInt32(leftAmp);
    panInts[1] = floatToInt32(rightAmp);
    // Serial.print("0x");
    // Serial.println(panInts[0], HEX);
    // Serial.print("0x");
    // Serial.println(panInts[1], HEX);

    uint16_t addrs [] = {ch_addrs[channel].pan[0], ch_addrs[channel].pan[1]};
    safeloadWriteN(addrs, panInts, 2);
}
void setChAddrs() {
  // in future, will scan file using regex.. hardcoded for now
  ch_addrs[0].gain = 1;
  ch_addrs[0].HF = {19, 20, 21, 22, 23};
  ch_addrs[0].MF = {25, 26, 27, 28, 29};
  ch_addrs[0].LF = {33, 34, 35, 36, 37};
  ch_addrs[0].fader = 38;
  ch_addrs[0].pan  = {46, 48};
  
  ch_addrs[1].gain = 2;
  ch_addrs[1].HF  = {4, 5, 6, 7, 8};
  ch_addrs[1].MF  = {9, 10, 11, 12, 13};
  ch_addrs[1].LF  = {14, 15, 16, 17, 18};
  ch_addrs[1].fader = 24;
  ch_addrs[1].pan  = {42, 44};
}
void resetChannels() {
  for(int i = 0; i < NUM_CHANNELS; i++) {
    channels[i] = Channel();
  }
  for(int i = 0; i < NUM_CHANNELS; i++) {
    setGain(channels[i].gain, i); // set gain

    setFilter(0,channels[i].HF_freq,channels[i].HF_gain,1.41,i); // reset HF
    setFilter(1,channels[i].MF_freq,channels[i].MF_gain,1.41,i); // 
    setFilter(2,channels[i].LF_freq,channels[i].LF_gain,1.41,i);

    setGain(channels[i].fader, i); // set faders

    setPan(channels[i].pan, i);
  }
}
void setFilter(uint8_t filterType, float frequency, float gain, float Q, int channel) {
  // ** in future, compare quality of float vs double values
  uint32_t filtInts [5];
  float omega_0 = 2 * M_PI * (frequency/FS);   
  float alpha = sin(omega_0) / (2 * Q);
  float A = pow(10,(gain/40.0));
  uint16_t filtAddrs[5];
  float a_0, a_1, a_2, b_0, b_1, b_2;

    switch (filterType) {
    case 0:
      a_0 = (A + 1) + (A - 1) * cos(omega_0) - (2 * sqrt(A) * alpha);
      
      b_2 = (A * ((A+1) - (A-1)*cos(omega_0) - (2*sqrt(A)*alpha))) / a_0;
      if (b_2 == 1.0) {
        // if b_2 = 1, there is no gain applied and no need to calculate values
        for(int i = 0; i < 5; i++ ) {
          filtInts[i] = 0;
        }
        filtInts[2] = floatToInt32(b_2);
      }
      else {
         b_0 = ((A*((A+1) - (A-1) * cos(omega_0) + (2*sqrt(A)*alpha)))/ a_0);
         b_1 = 2*A*((A-1) - (A+1) * cos(omega_0))/a_0;
         a_1 = 2*A*((A-1) + (A+1) * cos(omega_0))/a_0;
         a_2 = ((-(A+1) - (A-1) * cos(omega_0) + (2*sqrt(A)*alpha))/ a_0);

        filtInts[0] = floatToInt32(b_0);
        filtInts[1] = floatToInt32(b_1);
        filtInts[2] = floatToInt32(b_2);
        filtInts[3] = floatToInt32(a_1);
        filtInts[4] = floatToInt32(b_1);
      }
      memcpy(filtAddrs,ch_addrs[channel].HF.data(),sizeof(filtAddrs));
      break;
    case 1:
       a_0 = 1 + alpha / A;

       b_0 = (1 + alpha * A) / a_0;
      filtInts[0] = floatToInt32(b_0);
      if (b_0 == 1.0) {
        // if b_0 = 1, there is no gain applied and no need to calculate values
        
        for(int i = 1; i < 5; i++ ) {
          filtInts[i] = 0;
        }
      }
      else {
       b_1 = -1 * ((2 * cos(omega_0))/ a_0);
       b_2 = ((1 - alpha * A) / a_0);
       a_1 = ((2*cos(omega_0)) / a_0);
       a_2 = (((alpha/A) - 1)/ a_0);

      filtInts[1] = floatToInt32(b_1);
      filtInts[2] = floatToInt32(b_2);
      filtInts[3] = floatToInt32(a_1);
      filtInts[4] = floatToInt32(b_1);
      }
      memcpy(filtAddrs,ch_addrs[channel].MF.data(),sizeof(filtAddrs));
      break;
    case 2:// NEEDS TO BE DONE
       a_0 = (A + 1) + (A - 1) * cos(omega_0) - (2 * sqrt(A) * alpha);
      
       b_2 = (A * ((A+1) - (A-1)*cos(omega_0) - (2*sqrt(A)*alpha))) / a_0;
      if (b_2 == 1.0) {
        // if b_2 = 1, there is no gain applied and no need to calculate values
        for(int i = 0; i < 5; i++ ) {
          filtInts[i] = 0;
        }
        filtInts[2] = floatToInt32(b_2);
      }
      else {
         b_0 = ((A*((A+1) - (A-1) * cos(omega_0) + (2*sqrt(A)*alpha)))/ a_0);
         b_1 = (2*A*((A-1) - (A+1) * cos(omega_0)))/a_0;
         a_1 = (2*A*((A-1) + (A+1) * cos(omega_0)))/a_0;
         a_2 = ((-(A+1) - (A-1) * cos(omega_0) + (2*sqrt(A)*alpha))/ a_0);

        filtInts[0] = floatToInt32(b_0);
        filtInts[1] = floatToInt32(b_1);
        filtInts[2] = floatToInt32(b_2);
        filtInts[3] = floatToInt32(a_1);
        filtInts[4] = floatToInt32(a_2);
      }

      memcpy(filtAddrs,ch_addrs[channel].LF.data(),sizeof(filtAddrs));
      break;
      default:
        return;
  } 
  safeloadWriteN(filtAddrs, filtInts, 5);

}

void setGain(float gain, int channel) {
  if (channel < NUM_CHANNELS) {
    uint32_t gainInt = floatToInt32(gain);
    // Serial.print("Fader Int: 0x");
    // Serial.println(gainInt, HEX);
  
    safeloadWrite(2069, ch_addrs[channel].gain, gainInt);
  }


}

float mapToRange(int inputValue, float bottom,float top) {
  return (((float)inputValue / 1023.0) * (top - bottom)) + bottom;
}

bool toggle = false;
uint32_t freqToADAU(float freq) {
    return (uint32_t)((freq/FS) * 16777216.0f);
}
void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(100000);
    setChAddrs();

    resetChannels();

    delay(1000);

    Serial.println("ADAU1701 Toggle Test");
}
uint32_t floatToInt32(float x) {
  return (uint32_t)(x * 0x800000);
}
void loop()
{
  for(int i = 0; i < NUM_CHANNELS; i++) {
    channels[i].gain = -10;
    setGain(channels[i].gain, i); // set gain


    channels[i].pan = 0;
    setPan(channels[i].pan, i);
  }
  delay(1000);
  for(int i = 0; i < NUM_CHANNELS; i++) {
    channels[i].gain = 0;
    setGain(channels[i].gain, i); // set gain


    channels[i].pan = 45.;
    setPan(channels[i].pan, i);
  }
    delay(1000);

  for(int i = 0; i < NUM_CHANNELS; i++) {
    channels[i].gain = 10;
    setGain(channels[i].gain, i); // set gain


    channels[i].pan = 90.;
    setPan(channels[i].pan, i);
  }
    delay(1000);

}
void writeParameter(uint16_t addr, uint32_t data, int n) { 
    // write value of size n bytes to addr 
    Wire.beginTransmission(ADAU_ADDR); 

    // Safeload address
    Wire.write((addr >> 8) & 0xFF);
    Wire.write(addr & 0xFF);
    
    // Write ADDR TO UPDATE to safeload address  register
    for(int i = 8 * (n-1); i >= 0; i-=8) {
        Wire.write((data >> i) & 0xFF);
    }

    byte result = Wire.endTransmission();
    Serial.printf("Addr: %d, Data: %x, Bytes: %d\n",addr,data,n);
    Serial.println(result);
}
void readParamter(uint16_t addr, uint8_t * buffer, int n) {
  Wire.beginTransmission(ADAU_ADDR);
  Wire.write((addr >> 8) & 0xFF);
  Wire.write(addr & 0xFF);
  Wire.endTransmission(false);

  Wire.requestFrom(ADAU_ADDR, n);

  int i = 0;
  while(Wire.available() && i < n) {
    buffer[i] = Wire.read();
    Serial.print(buffer[i]);
  }
  Serial.println();
}
void readAllParameters() {
  
}
void safeloadWrite(uint16_t safeloadAddrReg, uint16_t addr, uint32_t value) {
    // Serial.println("Sending Data to 2064");
    writeParameter((safeloadAddrReg - 5), value, 5);

    // Serial.println("Sending Address to 2069");
    writeParameter(safeloadAddrReg, addr, 2);
    uint16_t initTransfer = 0x003C;
    writeParameter(dspControlReg, initTransfer, 2);
}
void safeloadWriteN(uint16_t addr[], uint32_t value[], int n) {
  // to add: check for n > 5
  uint32_t slAddrReg = 2069;
    for (int i = 0; i < n; i++) {
        writeParameter(slAddrReg - 5, value[i], 5);
        writeParameter(slAddrReg, addr[i], 2);
        slAddrReg++;
    }

    uint16_t initTransfer = 0x003C;
    writeParameter(dspControlReg, initTransfer, 2);
}
