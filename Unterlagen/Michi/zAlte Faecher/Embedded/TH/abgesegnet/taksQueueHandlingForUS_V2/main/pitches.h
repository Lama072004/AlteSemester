/*
 * pitches.h
 *
 *  Created on: 30.11.2022
 *      Author: GEM
 *
 *      Constants copied from Arduino IDE Example Sketch
 */

#ifndef MAIN_PITCHES_H_
#define MAIN_PITCHES_H_

/*************************************************
   Public Constants
 *************************************************/

#define REST 	 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//entry numbers for pitches array
#define TONE_IDX_B0  0
#define TONE_IDX_C1  1
#define TONE_IDX_CS1 2
#define TONE_IDX_D1  3
#define TONE_IDX_DS1 4
#define TONE_IDX_E1  5
#define TONE_IDX_F1  6
#define TONE_IDX_FS1 7
#define TONE_IDX_G1  8
#define TONE_IDX_GS1 9
#define TONE_IDX_A1  10
#define TONE_IDX_AS1 11
#define TONE_IDX_B1  12
#define TONE_IDX_C2  13
#define TONE_IDX_CS2 14
#define TONE_IDX_D2  15
#define TONE_IDX_DS2 16
#define TONE_IDX_E2  17
#define TONE_IDX_F2  18
#define TONE_IDX_FS2 19
#define TONE_IDX_G2  20
#define TONE_IDX_GS2 21
#define TONE_IDX_A2  22
#define TONE_IDX_AS2 23
#define TONE_IDX_B2  24
#define TONE_IDX_C3  25
#define TONE_IDX_CS3 26
#define TONE_IDX_D3  27
#define TONE_IDX_DS3 28
#define TONE_IDX_E3  29
#define TONE_IDX_F3  30
#define TONE_IDX_FS3 31
#define TONE_IDX_G3  32
#define TONE_IDX_GS3 33
#define TONE_IDX_A3  34
#define TONE_IDX_AS3 35
#define TONE_IDX_B3  36
#define TONE_IDX_C4  37
#define TONE_IDX_CS4 38
#define TONE_IDX_D4  39
#define TONE_IDX_DS4 40
#define TONE_IDX_E4  41
#define TONE_IDX_F4  42
#define TONE_IDX_FS4 43
#define TONE_IDX_G4  44
#define TONE_IDX_GS4 45
#define TONE_IDX_A4  46
#define TONE_IDX_AS4 47
#define TONE_IDX_B4  48
#define TONE_IDX_C5  49
#define TONE_IDX_CS5 50
#define TONE_IDX_D5  51
#define TONE_IDX_DS5 52
#define TONE_IDX_E5  53
#define TONE_IDX_F5  54
#define TONE_IDX_FS5 55
#define TONE_IDX_G5  56
#define TONE_IDX_GS5 57
#define TONE_IDX_A5  58
#define TONE_IDX_AS5 59
#define TONE_IDX_B5  60
#define TONE_IDX_C6  61
#define TONE_IDX_CS6 62
#define TONE_IDX_D6  63
#define TONE_IDX_DS6 64
#define TONE_IDX_E6  65
#define TONE_IDX_F6  66
#define TONE_IDX_FS6 67
#define TONE_IDX_G6  68
#define TONE_IDX_GS6 69
#define TONE_IDX_A6  70
#define TONE_IDX_AS6 71
#define TONE_IDX_B6  72
#define TONE_IDX_C7  73
#define TONE_IDX_CS7 74
#define TONE_IDX_D7  75
#define TONE_IDX_DS7 76
#define TONE_IDX_E7  77
#define TONE_IDX_F7  78
#define TONE_IDX_FS7 79
#define TONE_IDX_G7  80
#define TONE_IDX_GS7 81
#define TONE_IDX_A7  82
#define TONE_IDX_AS7 83
#define TONE_IDX_B7  84
#define TONE_IDX_C8  85
#define TONE_IDX_CS8 86
#define TONE_IDX_D8  87
#define TONE_IDX_DS8 88





#endif /* MAIN_PITCHES_H_ */
