#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspProcess.h"

#define N 250 //number of coeffiecients

short nfir = 0; // number of filter
short h[8][N]; // filter

const short Xlow[250] = {
        6,     24,     -2,     -1,     -7,     -7,     -3,      4,     10,
        9,      2,     -7,    -12,    -10,      0,     11,     15,     10,
       -2,    -15,    -18,    -10,      6,     20,     21,      9,    -11,
      -25,    -24,     -6,     17,     31,     25,      2,    -24,    -37,
      -25,      4,     33,     42,     24,    -12,    -43,    -47,    -21,
       22,     53,     51,     15,    -34,    -64,    -54,     -7,     48,
       75,     54,     -5,    -64,    -85,    -51,     20,     82,     94,
       44,    -38,   -101,   -101,    -34,     61,    121,    105,     18,
      -87,   -142,   -106,      3,    118,    162,    102,    -31,   -152,
     -181,    -91,     66,    190,    197,     73,   -109,   -232,   -210,
      -45,    162,    278,    217,      6,   -228,   -329,   -218,     49,
      308,    385,    209,   -126,   -411,   -449,   -186,    235,    548,
      527,    140,   -400,   -748,   -632,    -52,    679,   1085,    808,
     -135,  -1272,  -1860,  -1246,    751,   3677,   6568,   8360,   8360,
     6568,   3677,    751,  -1246,  -1860,  -1272,   -135,    808,   1085,
      679,    -52,   -632,   -748,   -400,    140,    527,    548,    235,
     -186,   -449,   -411,   -126,    209,    385,    308,     49,   -218,
     -329,   -228,      6,    217,    278,    162,    -45,   -210,   -232,
     -109,     73,    197,    190,     66,    -91,   -181,   -152,    -31,
      102,    162,    118,      3,   -106,   -142,    -87,     18,    105,
      121,     61,    -34,   -101,   -101,    -38,     44,     94,     82,
       20,    -51,    -85,    -64,     -5,     54,     75,     48,     -7,
      -54,    -64,    -34,     15,     51,     53,     22,    -21,    -47,
      -43,    -12,     24,     42,     33,      4,    -25,    -37,    -24,
        2,     25,     31,     17,     -6,    -24,    -25,    -11,      9,
       21,     20,      6,    -10,    -18,    -15,     -2,     10,     15,
       11,      0,    -10,    -12,     -7,      2,      9,     10,      4,
       -3,     -7,     -7,     -1,     -2,     24,      6
};
const short Clow[250] = {
       -4,    -25,     -4,     -7,     -7,     -6,     -5,     -3,     -1,
        2,      4,      7,     10,     12,     14,     15,     15,     14,
       12,      9,      6,      1,     -4,     -9,    -14,    -19,    -23,
      -26,    -27,    -27,    -25,    -22,    -16,    -10,     -2,      7,
       16,     25,     33,     40,     44,     46,     46,     42,     36,
       26,     15,      1,    -13,    -28,    -42,    -55,    -65,    -72,
      -74,    -73,    -66,    -55,    -40,    -21,      0,     23,     46,
       68,     87,    102,    112,    115,    112,    101,     83,     59,
       29,     -4,    -39,    -75,   -108,   -137,   -160,   -174,   -178,
     -172,   -154,   -126,    -88,    -41,     11,     67,    123,    176,
      221,    257,    279,    286,    276,    247,    201,    138,     60,
      -28,   -123,   -220,   -313,   -396,   -463,   -509,   -528,   -515,
     -469,   -386,   -265,   -109,     80,    299,    541,    800,   1068,
     1336,   1596,   1839,   2056,   2240,   2384,   2483,   2533,   2533,
     2483,   2384,   2240,   2056,   1839,   1596,   1336,   1068,    800,
      541,    299,     80,   -109,   -265,   -386,   -469,   -515,   -528,
     -509,   -463,   -396,   -313,   -220,   -123,    -28,     60,    138,
      201,    247,    276,    286,    279,    257,    221,    176,    123,
       67,     11,    -41,    -88,   -126,   -154,   -172,   -178,   -174,
     -160,   -137,   -108,    -75,    -39,     -4,     29,     59,     83,
      101,    112,    115,    112,    102,     87,     68,     46,     23,
        0,    -21,    -40,    -55,    -66,    -73,    -74,    -72,    -65,
      -55,    -42,    -28,    -13,      1,     15,     26,     36,     42,
       46,     46,     44,     40,     33,     25,     16,      7,     -2,
      -10,    -16,    -22,    -25,    -27,    -27,    -26,    -23,    -19,
      -14,     -9,     -4,      1,      6,      9,     12,     14,     15,
       15,     14,     12,     10,      7,      4,      2,     -1,     -3,
       -5,     -6,     -7,     -7,     -4,    -25,     -4
};
const short Dlow[250] = {
       -1,     24,      8,      7,      7,      6,      4,      2,      0,
       -3,     -6,     -9,    -11,    -13,    -14,    -14,    -13,    -10,
       -7,     -3,      2,      8,     13,     17,     21,     24,     25,
       24,     21,     16,      9,      2,     -7,    -16,    -24,    -31,
      -37,    -40,    -40,    -37,    -31,    -22,    -11,      2,     16,
       29,     42,     52,     59,     62,     61,     55,     44,     29,
       11,    -10,    -31,    -51,    -69,    -83,    -91,    -94,    -89,
      -77,    -58,    -34,     -6,     25,     56,     85,    110,    128,
      138,    137,    127,    106,     75,     37,     -7,    -53,    -99,
     -140,   -174,   -197,   -207,   -202,   -181,   -145,    -95,    -34,
       34,    105,    174,    235,    283,    314,    324,    310,    271,
      208,    123,     20,    -96,   -216,   -332,   -437,   -520,   -573,
     -589,   -561,   -485,   -359,   -183,     39,    302,    597,    915,
     1243,   1570,   1882,   2165,   2408,   2600,   2733,   2801,   2801,
     2733,   2600,   2408,   2165,   1882,   1570,   1243,    915,    597,
      302,     39,   -183,   -359,   -485,   -561,   -589,   -573,   -520,
     -437,   -332,   -216,    -96,     20,    123,    208,    271,    310,
      324,    314,    283,    235,    174,    105,     34,    -34,    -95,
     -145,   -181,   -202,   -207,   -197,   -174,   -140,    -99,    -53,
       -7,     37,     75,    106,    127,    137,    138,    128,    110,
       85,     56,     25,     -6,    -34,    -58,    -77,    -89,    -94,
      -91,    -83,    -69,    -51,    -31,    -10,     11,     29,     44,
       55,     61,     62,     59,     52,     42,     29,     16,      2,
      -11,    -22,    -31,    -37,    -40,    -40,    -37,    -31,    -24,
      -16,     -7,      2,      9,     16,     21,     24,     25,     24,
       21,     17,     13,      8,      2,     -3,     -7,    -10,    -13,
      -14,    -14,    -13,    -11,     -9,     -6,     -3,      0,      2,
        4,      6,      7,      7,      8,     24,     -1
};
const short Elow[250] = {
       11,    -18,    -12,     -9,     -8,     -7,     -6,     -4,     -1,
        2,      5,      8,     11,     13,     13,     13,     12,      9,
        5,      0,     -6,    -11,    -16,    -20,    -22,    -23,    -21,
      -18,    -12,     -4,      4,     13,     22,     29,     34,     36,
       35,     31,     24,     13,      1,    -13,    -26,    -38,    -47,
      -53,    -55,    -51,    -42,    -29,    -12,      7,     28,     47,
       63,     74,     80,     78,     69,     53,     31,      5,    -24,
      -52,    -78,    -98,   -111,   -114,   -107,    -90,    -63,    -29,
       11,     52,     92,    125,    150,    162,    161,    144,    113,
       70,     16,    -42,   -101,   -155,   -199,   -228,   -238,   -226,
     -193,   -140,    -69,     14,    103,    189,    266,    325,    359,
      363,    333,    270,    175,     53,    -87,   -234,   -378,   -503,
     -598,   -649,   -646,   -580,   -448,   -248,     16,    335,    698,
     1089,   1491,   1885,   2250,   2569,   2824,   3002,   3093,   3093,
     3002,   2824,   2569,   2250,   1885,   1491,   1089,    698,    335,
       16,   -248,   -448,   -580,   -646,   -649,   -598,   -503,   -378,
     -234,    -87,     53,    175,    270,    333,    363,    359,    325,
      266,    189,    103,     14,    -69,   -140,   -193,   -226,   -238,
     -228,   -199,   -155,   -101,    -42,     16,     70,    113,    144,
      161,    162,    150,    125,     92,     52,     11,    -29,    -63,
      -90,   -107,   -114,   -111,    -98,    -78,    -52,    -24,      5,
       31,     53,     69,     78,     80,     74,     63,     47,     28,
        7,    -12,    -29,    -42,    -51,    -55,    -53,    -47,    -38,
      -26,    -13,      1,     13,     24,     31,     35,     36,     34,
       29,     22,     13,      4,     -4,    -12,    -18,    -21,    -23,
      -22,    -20,    -16,    -11,     -6,      0,      5,      9,     12,
       13,     13,     13,     11,      8,      5,      2,     -1,     -4,
       -6,     -7,     -8,     -9,    -12,    -18,     11
};
const short Flow[250] = {
       23,      3,      2,      1,     -1,     -4,     -6,     -9,    -10,
      -12,    -12,    -11,     -9,     -6,     -2,      2,      7,     11,
       15,     17,     18,     16,     13,      8,      1,     -6,    -13,
      -20,    -25,    -29,    -29,    -27,    -21,    -13,     -3,      8,
       19,     30,     38,     42,     43,     40,     32,     20,      5,
      -12,    -28,    -43,    -55,    -62,    -63,    -58,    -46,    -29,
       -8,     16,     40,     61,     78,     88,     90,     82,     66,
       42,     12,    -22,    -55,    -86,   -109,   -123,   -126,   -116,
      -93,    -60,    -18,     29,     76,    119,    152,    173,    177,
      163,    132,     85,     26,    -40,   -107,   -168,   -217,   -247,
     -254,   -236,   -193,   -126,    -41,     56,    156,    248,    323,
      372,    388,    365,    302,    201,     68,    -87,   -251,   -410,
     -547,   -645,   -690,   -669,   -573,   -398,   -146,    177,    559,
      982,   1425,   1867,   2282,   2648,   2942,   3149,   3256,   3256,
     3149,   2942,   2648,   2282,   1867,   1425,    982,    559,    177,
     -146,   -398,   -573,   -669,   -690,   -645,   -547,   -410,   -251,
      -87,     68,    201,    302,    365,    388,    372,    323,    248,
      156,     56,    -41,   -126,   -193,   -236,   -254,   -247,   -217,
     -168,   -107,    -40,     26,     85,    132,    163,    177,    173,
      152,    119,     76,     29,    -18,    -60,    -93,   -116,   -126,
     -123,   -109,    -86,    -55,    -22,     12,     42,     66,     82,
       90,     88,     78,     61,     40,     16,     -8,    -29,    -46,
      -58,    -63,    -62,    -55,    -43,    -28,    -12,      5,     20,
       32,     40,     43,     42,     38,     30,     19,      8,     -3,
      -13,    -21,    -27,    -29,    -29,    -25,    -20,    -13,     -6,
        1,      8,     13,     16,     18,     17,     15,     11,      7,
        2,     -2,     -6,     -9,    -11,    -12,    -12,    -10,     -9,
       -6,     -4,     -1,      1,      2,      3,     23
};
const short Glow[250] = {
        7,    -21,    -11,     -8,     -7,     -5,     -3,      0,      4,
        7,     10,     11,     12,     11,      8,      4,     -1,     -6,
      -11,    -16,    -18,    -19,    -18,    -13,     -7,      0,      9,
       17,     24,     28,     29,     27,     21,     11,      0,    -12,
      -24,    -34,    -40,    -42,    -39,    -30,    -17,     -1,     17,
       34,     48,     57,     59,     55,     43,     25,      2,    -22,
      -46,    -65,    -78,    -82,    -76,    -60,    -36,     -5,     28,
       61,     88,    105,    111,    104,     83,     50,      9,    -36,
      -80,   -117,   -142,   -151,   -142,   -114,    -71,    -15,     46,
      106,    158,    193,    207,    196,    160,    101,     25,    -60,
     -144,   -217,   -268,   -290,   -278,   -230,   -149,    -42,     80,
      204,    313,    394,    434,    422,    357,    238,     75,   -118,
     -322,   -512,   -664,   -754,   -761,   -670,   -472,   -169,    231,
      707,   1235,   1782,   2312,   2789,   3181,   3458,   3603,   3603,
     3458,   3181,   2789,   2312,   1782,   1235,    707,    231,   -169,
     -472,   -670,   -761,   -754,   -664,   -512,   -322,   -118,     75,
      238,    357,    422,    434,    394,    313,    204,     80,    -42,
     -149,   -230,   -278,   -290,   -268,   -217,   -144,    -60,     25,
      101,    160,    196,    207,    193,    158,    106,     46,    -15,
      -71,   -114,   -142,   -151,   -142,   -117,    -80,    -36,      9,
       50,     83,    104,    111,    105,     88,     61,     28,     -5,
      -36,    -60,    -76,    -82,    -78,    -65,    -46,    -22,      2,
       25,     43,     55,     59,     57,     48,     34,     17,     -1,
      -17,    -30,    -39,    -42,    -40,    -34,    -24,    -12,      0,
       11,     21,     27,     29,     28,     24,     17,      9,      0,
       -7,    -13,    -18,    -19,    -18,    -16,    -11,     -6,     -1,
        4,      8,     11,     12,     11,     10,      7,      4,      0,
       -3,     -5,     -7,     -8,    -11,    -21,      7
};
const short Alow[250] = {
      -21,      3,      4,      6,      8,     10,     10,     10,      9,
        6,      2,     -3,     -7,    -11,    -13,    -13,    -12,     -8,
       -2,      4,     11,     16,     20,     21,     19,     13,      5,
       -4,    -14,    -23,    -28,    -30,    -28,    -20,     -9,      4,
       18,     30,     39,     42,     40,     30,     16,     -2,    -22,
      -39,    -52,    -58,    -55,    -44,    -25,     -1,     25,     49,
       67,     77,     75,     62,     38,      7,    -28,    -60,    -86,
     -101,   -101,    -85,    -56,    -16,     29,     73,    109,    131,
      134,    117,     81,     31,    -28,    -87,   -137,   -169,   -178,
     -160,   -117,    -52,     25,    104,    173,    221,    239,    221,
      169,     86,    -16,   -124,   -223,   -295,   -329,   -315,   -251,
     -143,     -2,    153,    300,    417,    481,    478,    400,    250,
       41,   -204,   -452,   -668,   -814,   -855,   -767,   -534,   -158,
      348,    953,   1614,   2282,   2901,   3420,   3794,   3990,   3990,
     3794,   3420,   2901,   2282,   1614,    953,    348,   -158,   -534,
     -767,   -855,   -814,   -668,   -452,   -204,     41,    250,    400,
      478,    481,    417,    300,    153,     -2,   -143,   -251,   -315,
     -329,   -295,   -223,   -124,    -16,     86,    169,    221,    239,
      221,    173,    104,     25,    -52,   -117,   -160,   -178,   -169,
     -137,    -87,    -28,     31,     81,    117,    134,    131,    109,
       73,     29,    -16,    -56,    -85,   -101,   -101,    -86,    -60,
      -28,      7,     38,     62,     75,     77,     67,     49,     25,
       -1,    -25,    -44,    -55,    -58,    -52,    -39,    -22,     -2,
       16,     30,     40,     42,     39,     30,     18,      4,     -9,
      -20,    -28,    -30,    -28,    -23,    -14,     -4,      5,     13,
       19,     21,     20,     16,     11,      4,     -2,     -8,    -12,
      -13,    -13,    -11,     -7,     -3,      2,      6,      9,     10,
       10,     10,      8,      6,      4,      3,    -21
};
const short Blow[250] = {
      -12,     17,     12,     10,      8,      6,      3,     -1,     -5,
       -9,    -11,    -11,     -9,     -5,      0,      6,     11,     15,
       17,     15,     10,      3,     -5,    -14,    -20,    -23,    -23,
      -17,     -8,      3,     15,     25,     31,     32,     27,     16,
        2,    -15,    -30,    -40,    -44,    -40,    -28,    -10,     12,
       32,     49,     57,     56,     44,     22,     -5,    -33,    -57,
      -72,    -75,    -64,    -40,     -7,     29,     63,     88,     98,
       90,     65,     26,    -20,    -66,   -103,   -123,   -122,    -97,
      -53,      4,     64,    117,    151,    160,    140,     92,     23,
      -55,   -128,   -183,   -207,   -195,   -145,    -65,     34,    134,
      217,    266,    269,    222,    129,      5,   -132,   -255,   -342,
     -373,   -336,   -232,    -74,    115,    304,    456,    539,    530,
      418,    210,    -69,   -379,   -666,   -875,   -952,   -857,   -565,
      -79,    576,   1350,   2173,   2966,   3649,   4150,   4415,   4415,
     4150,   3649,   2966,   2173,   1350,    576,    -79,   -565,   -857,
     -952,   -875,   -666,   -379,    -69,    210,    418,    530,    539,
      456,    304,    115,    -74,   -232,   -336,   -373,   -342,   -255,
     -132,      5,    129,    222,    269,    266,    217,    134,     34,
      -65,   -145,   -195,   -207,   -183,   -128,    -55,     23,     92,
      140,    160,    151,    117,     64,      4,    -53,    -97,   -122,
     -123,   -103,    -66,    -20,     26,     65,     90,     98,     88,
       63,     29,     -7,    -40,    -64,    -75,    -72,    -57,    -33,
       -5,     22,     44,     56,     57,     49,     32,     12,    -10,
      -28,    -40,    -44,    -40,    -30,    -15,      2,     16,     27,
       32,     31,     25,     15,      3,     -8,    -17,    -23,    -23,
      -20,    -14,     -5,      3,     10,     15,     17,     15,     11,
        6,      0,     -5,     -9,    -11,    -11,     -9,     -5,     -1,
        3,      6,      8,     10,     12,     17,    -12
};
// implements an fir filter using fir coefficients defined in fdacoefs.h
// in fixed-point
short fir_filter(buffer *xn){
	int j,i;
	int yn = 0;
	
	// fill the h array with all the different note filters
	for(i=0; i<N; i++){
	h[0][i] = Xlow[i];
	h[1][i] = Clow[i];
	h[2][i] = Dlow[i];
	h[3][i] = Elow[i];
	h[4][i] = Flow[i];
	h[5][i] = Glow[i];
	h[6][i] = Alow[i];
	h[7][i] = Blow[i];
	}

	// performs the convolution of xn with B
	for(j=0; j < N; j++){
		//yn += readn(xn,j)*B[j];
		  yn += readn(xn,j)*h[nfir][j]; //use the chosed filter (nfir)
	}
	yn = (yn >> 15) & 0xffff; //converts from Q30 to Q15 fixed point
	return (short)yn; // must cast to a 16-bit short for output to ALSA
}

// core dsp block processing
int dspBlockProcess(short *outputBuffer, short *inputBuffer, buffer *xnL, buffer *xnR, int samples, int * filter_on, double * volume, int * cnote, short * avgpwr){
	int i;
	int a=0,na=0;
	nfir = *cnote; //assign nfir the cnote variable value
	if(*filter_on == 0) {
		memcpy((char *)outputBuffer, (char *)inputBuffer, 2*samples); // passthru		
	}
	else if(*filter_on == 1) {
		for (i=0; i < samples; i+=2){
			push(xnL,inputBuffer[i]); // stores the most recent sample in the circular buffer xn
			push(xnR,inputBuffer[i+1]);
			outputBuffer[i] = (short)(*volume*fir_filter(xnL)); // filters the input and stores it in the left output channel
			outputBuffer[i+1] = (short)(*volume*fir_filter(xnR)); // zeros out the right output channel
			a = abs(outputBuffer[i]/samples); //absolute value of output/sample (avg)
			
			if (a >= na){
				na = a; //assign na the highest value of a
				*avgpwr = na; //pass na into *avgpwr
			}
			//*avgpwr = abs(sqrt(outputBuffer[i])/2);
		}

	}
	return DSP_PROCESS_SUCCESS,nfir;
}

