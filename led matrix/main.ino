// C++ code
//

int statesFirst[][4]{
  {0, 0, 0, 0}, // 0
  {1, 0, 0, 1}, // 1
  {1, 0, 1, 0}, // 2
  {0, 1, 0, 1}, // 3
  {0, 1, 1, 0}, // 4
  {1, 0, 0, 0}, // 1,2
  {0, 1, 0, 0}, // 3,4
  {1, 1, 0, 1}, // 1,3
  {1, 1, 1, 0}, // 2,4
};

int sS[][2][4]{
  {{1, 0, 0, 1},{0, 1, 1, 0}}, // 1,4
  {{1, 0, 1, 0},{0, 1, 0, 1}}, // 2,3
  {{1, 0, 0, 0},{0, 1, 0, 1}}, // 1,2,3
  {{1, 0, 1, 0},{0, 1, 0, 0}}, // 2,3,4
  {{1, 0, 0, 1},{0, 1, 0, 0}}, // 3,4,1
  {{1, 0, 0, 0},{0, 1, 1, 0}}, // 4,1,2
  {{1, 0, 0, 0},{0, 1, 0, 0}}, // 1,2,3,4
  {{0, 0, 0, 0},{0, 0, 0, 0}}, // 0_0
};

void setup()
{
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
   
}


void dw(int a, int b, int c, int d) {
	digitalWrite(7, a);
  	digitalWrite(8, b);
  	digitalWrite(11, c);
  	digitalWrite(12, d);
}

void reset() {
	dw(0, 0, 1, 1);
}

void loop() {
  for (int i = 0; i < sizeof(statesFirst) / sizeof(statesFirst[0]); i++) {
    reset();
 	dw(statesFirst[i][0], statesFirst[i][1], statesFirst[i][2], statesFirst[i][3]);
    delay(1000);
  }
  reset();
  for (int i = 0; i < sizeof(sS) / sizeof(sS[0]); i++) {
  	for (int j = 0; j < 1000; j++) {
   		reset();
       	dw(sS[i][0][0], sS[i][0][1], sS[i][0][2], sS[i][0][3]);
        delay(1);
        reset();
       	dw(sS[i][1][0], sS[i][1][1], sS[i][1][2], sS[i][1][3]);
        delay(1);
  	}
    reset();
  }
}