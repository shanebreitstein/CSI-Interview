#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "arduino_freertos.h"
#include "semphr.h"
const int NUM_VOICES = 6;
// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;      //xy=55,480.6262035369873
AudioSynthWaveform       vcfLFO;      //xy=55,480.6262035369873
AudioSynthWaveformDc     pwmDC;            //xy=55,600.2222118377686
AudioMixer4              pwmMix;         //xy=124.88888549804688,758.2222137451172
AudioEffectEnvelope      lfoEnv;      //xy=172.0001106262207,537.4447746276855
AudioEffectEnvelope      vcfLFOEnv;      //xy=172.0001106262207,537.4447746276855
AudioSynthWaveformDc     vcfEnvDC;            //xy=204.00000762939453,676.8283233642578
AudioSynthWaveformModulated pulse[NUM_VOICES]; //xy=299.8888854980469,1225.5555419921875
AudioSynthWaveformModulated saw[NUM_VOICES]; //xy=300.8888854980469,1255.5556030273438
AudioSynthWaveformModulated sub[NUM_VOICES]; //xy=298.88885498046875,1288.555477142334
AudioSynthNoiseWhite     noise[NUM_VOICES]; //xy=299.7979393005371,1319.9191417694092
AudioSynthWaveformDc     vcfEnvDCInv; //xy=316.0000305175781,718.2222442626953
AudioEffectEnvelope      vcfEnv;      //xy=318.8082046508789,627.666669845581
AudioMixer4              oscMixer[NUM_VOICES]; //xy=444.9797668457031,1274.9191074371338
AudioEffectMultiply      vcfMul;      //xy=454.00012969970703,673.2223968505859
AudioMixer4              vcfEnvMix; //xy=581.8889007568359,714.1110992431641
AudioFilterStateVariable hpf[NUM_VOICES]; //xy=607.6060371398926,1276.464765548706
AudioMixer4              vcfModMixer;         //xy=722.7373504638672,617.5758819580078
AudioFilterStateVariable vcf[NUM_VOICES]; //xy=805.9798278808594,1263.8283672332764
AudioEffectEnvelope      envelope[NUM_VOICES]; //xy=963.9799346923828,1269.5556030273438
AudioMixer4              voiceMix;         //xy=1227.555721282959,1063.3333320617676
AudioMixer4              voiceMix1; //xy=1235.888916015625,1297.6666259765625
AudioMixer4              finalMixer; //xy=1344.888916015625,1155.6666259765625
AudioOutputI2S           i2s1;           //xy=1497.0003066062927,1152.0913276672363      

AudioConnection          patchCord1(lfo, lfoEnv);

AudioConnection          patchCord2(pwmDC, 0, pwmMix, 1);
AudioConnection          patchCord3(pwmMix, 0, pulse[0], 1);
AudioConnection          patchCord4(vcfLFO, vcfLFOEnv);
//AudioConnection          patchCord4(lfoEnv, 0, vcfModMixer, 0);
AudioConnection          patchCord5(lfoEnv, 0, pulse[0], 0);
AudioConnection          patchCord6(lfoEnv, 0, saw[0], 0);
AudioConnection          patchCord7(lfoEnv, 0, sub[0], 0);
AudioConnection          patchCord8(lfoEnv, 0, pwmMix, 0);
AudioConnection          patchCord9(vcfEnvDC, vcfEnv);
AudioConnection          patchCord10(vcfEnvDC, 0, vcfEnvMix, 1);
AudioConnection          patchCord11(sub[3], 0, oscMixer[3], 2);
AudioConnection          patchCord12(sub[5], 0, oscMixer[5], 2);
AudioConnection          patchCord13(sub[2], 0, oscMixer[2], 2);
AudioConnection          patchCord14(pulse[3], 0, oscMixer[3], 0);
AudioConnection          patchCord15(sub[1], 0, oscMixer[1], 2);
AudioConnection          patchCord16(pulse[5], 0, oscMixer[5], 0);
AudioConnection          patchCord17(noise[3], 0, oscMixer[3], 3);
AudioConnection          patchCord18(pulse[2], 0, oscMixer[2], 0);
AudioConnection          patchCord19(noise[5], 0, oscMixer[5], 3);
AudioConnection          patchCord20(noise[2], 0, oscMixer[2], 3);
AudioConnection          patchCord21(sub[4], 0, oscMixer[4], 2);
AudioConnection          patchCord22(pulse[1], 0, oscMixer[1], 0);
AudioConnection          patchCord23(saw[3], 0, oscMixer[3], 1);
AudioConnection          patchCord24(noise[1], 0, oscMixer[1], 3);
AudioConnection          patchCord25(saw[5], 0, oscMixer[5], 1);
AudioConnection          patchCord26(sub[0], 0, oscMixer[0], 2);
AudioConnection          patchCord27(saw[2], 0, oscMixer[2], 1);
AudioConnection          patchCord28(pulse[4], 0, oscMixer[4], 0);
AudioConnection          patchCord29(noise[4], 0, oscMixer[4], 3);
AudioConnection          patchCord30(saw[1], 0, oscMixer[1], 1);
AudioConnection          patchCord31(pulse[0], 0, oscMixer[0], 0);
AudioConnection          patchCord32(noise[0], 0, oscMixer[0], 3);
AudioConnection          patchCord33(saw[4], 0, oscMixer[4], 1);
AudioConnection          patchCord34(saw[0], 0, oscMixer[0], 1);
AudioConnection          patchCord35(vcfEnvDCInv, 0, vcfMul, 1);
AudioConnection          patchCord36(vcfEnv, 0, vcfMul, 0);
AudioConnection          patchCord37(vcfEnv, 0, pwmMix, 2);
AudioConnection          patchCord38(oscMixer[3], 0, hpf[3], 0);
AudioConnection          patchCord39(oscMixer[5], 0, hpf[5], 0);
AudioConnection          patchCord40(oscMixer[2], 0, hpf[2], 0);
AudioConnection          patchCord41(oscMixer[1], 0, hpf[1], 0);
AudioConnection          patchCord42(oscMixer[4], 0, hpf[4], 0);
AudioConnection          patchCord43(oscMixer[0], 0, hpf[0], 0);
AudioConnection          patchCord44(vcfMul, 0, vcfEnvMix, 0);
AudioConnection          patchCord45(vcfEnvMix, 0, vcfModMixer, 1);
AudioConnection          patchCord46(hpf[3], 2, vcf[3], 0);
AudioConnection          patchCord47(hpf[5], 2, vcf[5], 0);
AudioConnection          patchCord48(hpf[2], 2, vcf[2], 0);
AudioConnection          patchCord49(hpf[1], 2, vcf[1], 0);
AudioConnection          patchCord50(hpf[4], 2, vcf[4], 0);
AudioConnection          patchCord51(hpf[0], 2, vcf[0], 0);
AudioConnection          patchCord52(vcfModMixer, 0, vcf[0], 1);
AudioConnection          patchCord53(vcf[3], 0, envelope[3], 0);
AudioConnection          patchCord54(vcf[5], 0, envelope[5], 0);
AudioConnection          patchCord55(vcf[2], 0, envelope[2], 0);
AudioConnection          patchCord56(vcf[1], 0, envelope[1], 0);
AudioConnection          patchCord57(vcf[4], 0, envelope[4], 0);
AudioConnection          patchCord58(vcf[0], 0, envelope[0], 0);
AudioConnection          patchCord59(envelope[3], 0, voiceMix1, 0);
AudioConnection          patchCord60(envelope[5], 0, voiceMix1, 2);
AudioConnection          patchCord61(envelope[2], 0, voiceMix, 2);
AudioConnection          patchCord62(envelope[1], 0, voiceMix, 1);
AudioConnection          patchCord63(envelope[4], 0, voiceMix1, 1);
AudioConnection          patchCord64(envelope[0], 0, voiceMix, 0);
AudioConnection          patchCord65(voiceMix, 0, finalMixer, 0);
AudioConnection          patchCord66(voiceMix1, 0, finalMixer, 1);
AudioConnection          patchCord67(finalMixer, 0, i2s1, 0);
AudioConnection          patchCord68(finalMixer, 0, i2s1, 1);
AudioConnection          patchCord69(vcfLFOEnv, 0, vcfModMixer, 0);
AudioConnection          patchCord70(vcfModMixer, 0, vcf[1], 1);
// AudioConnection          patchCord52(vcfModMixer, 0, vcf[0], 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1005,457
// GUItool: end automatically generated code

const int numAnalogPins = 13;
const int numDigitalPins = 14;
// const int analogPins[] = {A0, A1, A2, A3}; // DEMO CODE ANALOG PINS
// const int digitalPins[] = {0, 1, 2, 3, 4, 5, 9}; // demo code digital pins
const int analogPins[] = {A0, A1, A2, A3, A8, A10, A11, A12, A13, A14, A15, A16, A17}; // all valid analog pins
const int digitalPins[] = {0, 1, 2, 3, 4, 5, 31, 32, 33, 34}; // all valid digital pins
const int envMuxPins[] = {3, 4};
const float VCF_MAX = 14450.0;

int dVals[numDigitalPins];
int aVals[numAnalogPins];

// default values
float attack = 50;
float decay = 500;
float sustain = 1;
float release = 100;
bool pulseTog = true, sawTog = true, subTog = true, gateTog = true, lfoTrig = true, pwmCntl1 = false, pwmCntl0 = false;
float gainVal, chGain, subGain, noiseGain = 0.0;
float envPol;
float vcfFreq = 14000.0, vcfRes = 0.7, vcflfoAmp = 0.0, vcfEnvAmp = 0.0, vcfOctCon = 0.0;
//unsigned long startTime, endTime;
float noiseAmp = 0.25;
// read in values
float subAmp;
float lfoAmp, pwmAmp;

float lfoGain, vcfEnvGain, vcfLFOGain;

float lfoFreq, lfoDelay, hpfFreq = 10.0, vcaAmp;
byte pwmControl;
//voice handling
// FreeRTOS 
TaskHandle_t midiReadTask;
TaskHandle_t analogReadTask;
TaskHandle_t digitalReadTask;
TaskHandle_t soundParamTask;
SemaphoreHandle_t synthMutex;
SemaphoreHandle_t paramMutex;
int voicesMIDI[NUM_VOICES]; // holds the MIDI notes of all voices
int voicesOn = 0; // stores number of voices currently on
int voiceIndex;
int wavesOn;

int muxControl = 0;

float freq;
//char control [4];
void setup() {
  AudioMemory(120);

  Serial.begin(115200);
  pinMode(13, arduino::OUTPUT);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  // Initialize digital pins as inputs
  for (int i = 0; i < sizeof(digitalPins) / sizeof(digitalPins[0]); i++) {
    pinMode(digitalPins[i], arduino::INPUT);
  }

  // init analog pins for input
  for (int i = 0; i < numAnalogPins; i++)
  {
    pinMode(analogPins[i], arduino::INPUT);
  }
  // set all voices off
  for(int i = 0; i < NUM_VOICES; i++) {
    //voicesOn[i] = 0;
    voicesMIDI[i] = -1;
    pulse[i].begin(WAVEFORM_PULSE);
    saw[i].begin(WAVEFORM_SAWTOOTH);
    sub[i].begin(WAVEFORM_SQUARE);

   
    pulse[i].amplitude(1);
    saw[i].amplitude(1);
    sub[i].amplitude(1);
    noise[i].amplitude(1);
   
    oscMixer[i].gain(0,0.33);
    oscMixer[i].gain(1,0.33);
    oscMixer[i].gain(2,0.33);
    oscMixer[i].gain(3,0.33);

    envelope[i].attack(attack);
    envelope[i].decay(decay);
    envelope[i].sustain(sustain);
    envelope[i].release(release);

    vcf[i].frequency(vcfFreq);
    vcf[i].resonance(vcfRes);
    vcf[i].octaveControl(vcfOctCon);

    hpf[i].frequency(hpfFreq);


  }
  lfo.begin(WAVEFORM_TRIANGLE);
  lfo.frequency(0.3);
  lfo.amplitude(0.0);

  vcfLFO.begin(WAVEFORM_TRIANGLE);
  vcfLFO.frequency(0.3);
  vcfLFO.amplitude(1.0);

  vcfEnv.attack(attack);
  vcfEnv.decay(decay);
  vcfEnv.sustain(sustain);
  vcfEnv.release(release);

  vcfLFOEnv.attack(attack);
  vcfLFOEnv.decay(decay);
  vcfLFOEnv.sustain(sustain);
  vcfLFOEnv.release(release);

  vcfEnvDC.amplitude(-1.0);
  vcfEnvDCInv.amplitude(-1.0);

  pwmMix.gain(0, 0.0);
  pwmMix.gain(1, 1.0);
  pwmMix.gain(2, 0.0);
  voiceMix.gain(0, 0.33);
  voiceMix.gain(1, 0.33);
  voiceMix.gain(2, 0.33);
  voiceMix1.gain(0, 0.33);
  voiceMix1.gain(1, 0.33);
  voiceMix1.gain(2, 0.33);

 
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  synthMutex = xSemaphoreCreateMutex();
  paramMutex = xSemaphoreCreateMutex();
  xTaskCreate(midi_reader, "MIDI_READ", 1024, NULL, 4, &midiReadTask);
  xTaskCreate(readAnalogPins, "ANALOG_READ", 1024, NULL, 2, &analogReadTask);
  xTaskCreate(readDigitalPins, "DIGITAL_READ", 1024, NULL, 2, &digitalReadTask);
  xTaskCreate(updateSoundParams, "UPDATE_SOUND_PARAMS", 1024, NULL, 3, &soundParamTask);

  // threads.addThread(toggleLED);
  vTaskStartScheduler();
}


void loop() {

}

void OnNoteOn(byte channel, byte note, byte velocity) {
      float noteFreq = midi_to_freq(note);
      xSemaphoreTake(synthMutex, portMAX_DELAY);
      voiceIndex = findOpenVoice(voicesMIDI);


      if (voiceIndex != -1) { // found empty voice
        voicesMIDI[voiceIndex] = (int)note;

        if (voicesOn == 0) {
          vcfLFOEnv.noteOn();
        }
        voicesOn++;
        pulse[voiceIndex].frequency(noteFreq); // incoming pulse[i]
        saw[voiceIndex].frequency(noteFreq);
        sub[voiceIndex].frequency(noteFreq/2.0);
       
        envelope[voiceIndex].noteOn();
        vcfEnv.noteOn();
        lfoEnv.noteOn();
        xSemaphoreGive(synthMutex);
      }
      else {
        xSemaphoreGive(synthMutex);
        return;
      }
}
void OnNoteOff(byte channel, byte note, byte velocity) {
      int i;
      for(i = 0; i < NUM_VOICES; i++) {
        if (voicesMIDI[i] == note) {
          break;
        }
      }

      xSemaphoreTake(synthMutex, portMAX_DELAY);
      if (i != NUM_VOICES) { // found voice turned off
        voicesOn--;
        envelope[i].noteOff();
        voicesMIDI[i] = -1;
      }
      if(voicesOn == 0) {
          Serial.println("VCF LFO Env Note On");

        vcfLFOEnv.noteOff();
        vcfEnv.noteOff();
        lfoEnv.noteOff();
      }
    xSemaphoreGive(synthMutex);
}

int findOpenVoice(int * voices) {
  for(int i = 0; i < NUM_VOICES; i++) {
    Serial.print("Voices[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(voices[i]);
    if (voices[i] == -1) {
      Serial.print("found empty voice at index ");
      Serial.println(i);
      return i;
    }
  }
  // if no empty voices, we'll return -1
  return -1;
}
void printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, arduino::HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}
float midi_to_freq(int note) {
  return 440.0f*pow(2,(note-69)/12.0f);
}

void midi_reader(void* taskParams){
  while (1) {
      while(usbMIDI.read()){
        //callbacks execute automatically
      }
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}
float mapToRange(int inputValue, float bottom,float top) {
  return (((float)inputValue / 1023.0) * (top - bottom)) + bottom;
}
float mapToRangeExp(int inputValue, float bottom, float top) {
  // input = 0-1023
  //output = a number between bottom to top, scaled expontentially
  return (pow(2.0,(inputValue/1023.0)) - 1) * (top - bottom) + bottom;
}
// float log2(float x) {
//   return (log(x)/log(2));
// }
float getOctControl() {
  float octCon = log2(VCF_MAX/vcfFreq);
  // Serial.print("Oct control: ");
  // Serial.println(octCon);
  return (octCon);
}
void updateSoundParams(void* taskParams) {
  while (1) {
    xSemaphoreTake(paramMutex, portMAX_DELAY);
    lfo.amplitude(lfoAmp);
    lfo.frequency(lfoFreq);
    pwmDC.amplitude(pwmAmp);

    vcfModMixer.gain(0,vcflfoAmp);
    vcfModMixer.gain(1,vcfEnvAmp);

    vcfLFO.frequency(lfoFreq);
    vcfLFOEnv.attack(lfoDelay);
    vcfEnvDCInv.amplitude(envPol);
    lfoEnv.attack(lfoDelay);

    vcfOctCon = getOctControl();


    if (gateTog) {
      for(int i = 0; i < NUM_VOICES; i++) {
          envelope[i].attack(0.0);
          envelope[i].decay(0.0);
          envelope[i].sustain(1);
          envelope[i].release(0.0);
      }
    }
    else {
      for (int i = 0; i < NUM_VOICES; i++) {
        envelope[i].attack(attack);
        envelope[i].decay(decay);
        envelope[i].sustain(sustain);
        envelope[i].release(release);
      }
      vcfEnv.attack(attack);
      vcfEnv.decay(decay);
      vcfEnv.sustain(sustain);
      vcfEnv.release(release);
    }
    wavesOn = pulseTog + sawTog + subTog;
    switch (subTog) {
      case 0: // sub is used
        gainVal = wavesOn + noiseAmp;
        noiseGain = noiseAmp / gainVal;
        chGain = 1 / gainVal;
        break;
      case 1:
        gainVal = wavesOn + noiseAmp + subAmp - 1;
        noiseGain = noiseAmp/gainVal;
        subGain = subAmp/gainVal;
        chGain = 1/gainVal;
        break;
      }
  
    for(int i = 0; i < NUM_VOICES; i++) {
      pulse[i].amplitude(pulseTog);
      saw[i].amplitude(sawTog);

      oscMixer[i].gain(0,chGain);
      oscMixer[i].gain(1,chGain);
      oscMixer[i].gain(2,subGain*subTog);
      oscMixer[i].gain(3,noiseGain);

      vcf[i].frequency(vcfFreq);
      vcf[i].resonance(vcfRes);
      vcf[i].octaveControl(vcfOctCon);
      hpf[i].frequency(hpfFreq);
    }
    finalMixer.gain(0, vcaAmp);
    finalMixer.gain(1, vcaAmp);

  xSemaphoreGive(paramMutex);
  vTaskDelay(pdMS_TO_TICKS(10));
  }
   
}
void readAnalogPins(void* taskParams) {
  while(true) {
    for(int i = 0; i < numAnalogPins; i++) {
      aVals[i] = analogRead(analogPins[i]);
    }
    xSemaphoreTake(paramMutex, portMAX_DELAY);
    noiseAmp = mapToRange(aVals[0], 0.0, 1.0);
    subAmp   = mapToRange(aVals[1], 0.0, 1.0);
    pwmAmp  = mapToRange(aVals[2], 0.0, 0.95);
    lfoAmp   = mapToRangeExp(aVals[3], 0, .1); 
    hpfFreq  = mapToRange(aVals[4], 10.0, 5000.0);
    vcflfoAmp = mapToRange(aVals[5], 0, 0.5);
    vcfEnvAmp = mapToRange(aVals[6], 0, 0.5);
    vcfRes  = mapToRangeExp(aVals[7], 0.7, 5.0);
    vcfFreq = mapToRangeExp(aVals[8], 750, 14000.0);
    lfoFreq  = mapToRangeExp(aVals[9], 0.3, 20.0);
    vcaAmp = mapToRange(aVals[11], 0.0, 0.5);
    lfoDelay  = mapToRangeExp(aVals[12], 0.0, 1500.0);

    if (!gateTog) { // envelope update is only necessary if gate control is off
      switch (muxControl) {
        case 0: 
          attack = mapToRangeExp(aVals[10], 1.0, 3000.0);
          break;
        case 1:
          decay  = mapToRangeExp(aVals[10], 2.0, 12000.0);
          break;
        case 2:
          sustain = mapToRange(aVals[10], 0, 1.0);
          break;
        case 3:
          release = mapToRangeExp(aVals[10], 2.0, 12000.0);
          break;
        default:
          break;
      }
      
    }
    muxControl = (muxControl + 1) % 4;

    // update mux control pins
    digitalWrite(envMuxPins[0], (muxControl & 0b01));
    digitalWrite(envMuxPins[1], ((muxControl & 0b10) >> 1));

    xSemaphoreGive(paramMutex);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
void readDigitalPins(void* taskParams) {
  while(true) {
    xSemaphoreTake(paramMutex, portMAX_DELAY);
    // unsigned long startTime = millis();
    for(int i = 0; i < numDigitalPins; i++) {
      dVals[i] = digitalRead(digitalPins[i]);
    }
    subTog = (dVals[0]) ? 1 : 0;
    sawTog = (dVals[1]) ? 1 : 0;
    pulseTog = (dVals[2]) ? 1 : 0;

    pwmCntl1 = (dVals[3]) ? 1 : 0;
    pwmCntl0 = (dVals[4]) ? 1 : 0;

    envPol = (dVals[5]) ? 1.0 : -1.0;
    lfoTrig = (dVals[6]) ? 1 : 0;
    gateTog = (dVals[7]) ? 1 : 0;
    xSemaphoreGive(paramMutex);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
