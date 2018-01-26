#include <Adafruit_NeoPixel.h>
#include "Wire.h"

#define PIN 6
#define PINZ 2

#define FINGER_HEIGHT_PIN A0
#define MULTIPLEX_PIN A1

#define ROBOT_STATE_PIN 12
#define ROBOT_STATE_PIN_TWO 22
#define ROBOT_STATE_PIN_THREE 28 /*???????????*/

Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripz = Adafruit_NeoPixel(120, PINZ, NEO_GRB + NEO_KHZ800);
bool on = true;
#include "utilities.h"

bool stay_white = false;

void setup() {
	pinMode(PIN,OUTPUT);
        pinMode(PINZ,OUTPUT);
	
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

        stripz.begin();
        stripz.show();
        Serial.begin(9600);
}

#define STATE_TELEOP    0b000
#define STATE_AUTO      0b001
#define STATE_SCORE     0b010
#define STATE_COOP      0b011
#define STATE_BROWNOUT  0b100
#define STATE_LOST_COMM 0b101
#define STATE_FULL      0b110
#define STATE_DISABLED  0b111

uint16_t finger_height;
bool elevator_auto;
bool stabilizer_on;
bool finger_on;
uint8_t robot_state, old_state, first_loop;

void loop() {

  
  finger_height = map(analogRead(FINGER_HEIGHT_PIN), 0, 1024, 22, 90); //convert 0-1024 ADC read to 0-127
  uint8_t multi_read = analogRead(MULTIPLEX_PIN) >> 7; //grab 3 most significant bits
  elevator_auto = (multi_read & 1);
  stabilizer_on = (multi_read >> 1) & 1;
  finger_on = (multi_read >> 2) & 1;
  bool state_pin1 = digitalRead(ROBOT_STATE_PIN);
  bool state_pin2 = digitalRead(ROBOT_STATE_PIN_TWO);
  bool state_pin3 = digitalRead(ROBOT_STATE_PIN_THREE);
  Serial.println();
  Serial.print(state_pin3);
  Serial.print(state_pin2);
  Serial.print(state_pin1);
  robot_state = ((state_pin3 << 2) & 0b100) | ((state_pin2 << 1) & 0b10) | ((state_pin1) & 0b1);
  Serial.println();
  Serial.println(robot_state);
  if(old_state!=robot_state)
  {
    first_loop=true;
    stay_white=false;
    fillStrip(strip.Color(0,0,0),255);
    fillStripZ(stripz.Color(0,0,0),255);
  }
  old_state=robot_state;

  if(robot_state == STATE_AUTO) {
   //auton();
   pixelate();
  } else if (robot_state == STATE_SCORE) {
   rainbowlaser();
  } else if(robot_state == STATE_TELEOP || robot_state == STATE_FULL) {
    fillStrip(strip.Color(0,0,0),255);
  fillStripZ(stripz.Color(0,0,0),255);
    uprights(); 
  } else if (robot_state == STATE_LOST_COMM) {
    fillStrip(strip.Color(255,0,0),255);
    fillStripZ(stripz.Color(255,0,0),255);
  } else if (robot_state == STATE_BROWNOUT) {
    fillStrip(strip.Color(70,25,0),255);
    fillStripZ(strip.Color(70,25,0),255);
  } else if (robot_state == STATE_COOP) {
    coop_rainbowlaser();
  } else {
//    rainbow(0); 
  lavalamp();
    //rainbowlaser();
    //pixelate();
  }
  

  strip.show();
  stripz.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    for(i=0; i<stripz.numPixels(); i++) {
      stripz.setPixelColor(i, Wheel((i+j) & 255));
    }
    
       
    strip.show();
    stripz.show();
    delay(wait);
  }
}

void laser()
{
	uint16_t i, c, w;
	c=strip.Color(0,255,0);
	
	w=7;
	
	for(i=0;i<(strip.numPixels()+w);i++)
	{
		strip.setPixelColor(i,c);
		strip.setPixelColor(i-w,0);
		//strip.setPixelColor(i+5,0);
                stripz.setPixelColor(i,c);
		stripz.setPixelColor(i-w,0);
		//strip.setPixelColor(i+5,0);
		stripz.show();
                strip.show();
		delay(15);
	}
}

void rainbowlaser()
{
	uint32_t ii, c, w, r,o,y,g,b,i,v;
	r=strip.Color(255,0,0);
	o=strip.Color(255,128,0);
	y=strip.Color(255,255,0);
	
	g=strip.Color(0,255,0);
	
	b=strip.Color(0,0,255);
	ii=strip.Color(128,0,255);
	v=strip.Color(255,0,255);
	
	w=32;

uint32_t iii, cz, wz, rz,oz,yz,gz,bz,iz,vz;
	rz=stripz.Color(255,0,0);
	oz=stripz.Color(255,128,0);
	yz=stripz.Color(255,255,0);
	
	gz=stripz.Color(0,255,0);
	
	bz=stripz.Color(0,0,255);
	iii=stripz.Color(128,0,255);
	vz=stripz.Color(255,0,255);
	
if(!stay_white)
{
	for(i=strip.numPixels()+w;i>0;i--)
	{
                strip.setPixelColor(i,strip.Color(120,120,120));
		strip.setPixelColor(i-4,v);
		strip.setPixelColor(i-8,ii);
		strip.setPixelColor(i-12,b);
		strip.setPixelColor(i-16,g);
		strip.setPixelColor(i-20,y);
		strip.setPixelColor(i-24,o);
		strip.setPixelColor(i-28,r);
		strip.setPixelColor(i-w,strip.Color(120,120,120));

                stripz.setPixelColor(i,strip.Color(120,120,120));
		stripz.setPixelColor(i-4,vz);
		stripz.setPixelColor(i-8,iii);
		stripz.setPixelColor(i-12,bz);
		stripz.setPixelColor(i-16,gz);
		stripz.setPixelColor(i-20,yz);
		stripz.setPixelColor(i-24,oz);
		stripz.setPixelColor(i-28,rz);
		//stripz.setPixelColor(i-w,strip.Color(120,120,120));
		
                strip.show();
                stripz.show();
		//delay(15);
	}
        stay_white=true;
}
else
{
fillStrip(strip.Color(120,120,120),255);
fillStripZ(stripz.Color(120,120,120),255);
strip.show();
stripz.show();
}
}

void coop_rainbowlaser()
{
	uint32_t ii, c, w, r,o,y,g,b,i,v;
	r=strip.Color(255,0,0);
	o=strip.Color(255,128,0);
	y=strip.Color(255,255,0);
	
	g=strip.Color(0,255,0);
	
	b=strip.Color(0,0,255);
	ii=strip.Color(128,0,255);
	v=strip.Color(255,0,255);
	
	w=32;

uint32_t iii, cz, wz, rz,oz,yz,gz,bz,iz,vz;
	rz=stripz.Color(255,0,0);
	oz=stripz.Color(255,128,0);
	yz=stripz.Color(255,255,0);
	
	gz=stripz.Color(0,255,0);
	
	bz=stripz.Color(0,0,255);
	iii=stripz.Color(128,0,255);
	vz=stripz.Color(255,0,255);
	
if(!stay_white)
{
	for(i=strip.numPixels()+w;i>0;i--)
	{
                strip.setPixelColor(i,y);
		strip.setPixelColor(i-4,v);
		strip.setPixelColor(i-8,ii);
		strip.setPixelColor(i-12,b);
		strip.setPixelColor(i-16,g);
		strip.setPixelColor(i-20,y);
		strip.setPixelColor(i-24,o);
		strip.setPixelColor(i-28,r);
		strip.setPixelColor(i-w,y);

                stripz.setPixelColor(i,y);
		stripz.setPixelColor(i-4,vz);
		stripz.setPixelColor(i-8,iii);
		stripz.setPixelColor(i-12,bz);
		stripz.setPixelColor(i-16,gz);
		stripz.setPixelColor(i-20,yz);
		stripz.setPixelColor(i-24,oz);
		stripz.setPixelColor(i-28,rz);
		//stripz.setPixelColor(i-w,strip.Color(120,120,120));
		
                strip.show();
                stripz.show();
		//delay(15);
	}
        stay_white=true;
}
else
{
fillStrip(y,255);
fillStripZ(y,255);
strip.show();
stripz.show();
}
}

void bouncelaser()
{
	uint16_t i, c, w;
	c=strip.Color(0,255,0);
	
	w=12;
	
	for(i=0;i<(strip.numPixels()+(w-6));i++)
	{
		strip.setPixelColor(i,c);
		strip.setPixelColor(i-w,0);
		//strip.setPixelColor(i+5,0);
		strip.show();
		delay(15);
	}
	
	for(i=strip.numPixels()-(w-6);(i+6)>0;i--)
	{
		strip.setPixelColor(i,c);
		strip.setPixelColor(i+w,0);
		//strip.setPixelColor(i+5,0);
		strip.show();
		delay(15);
	}
	
}

void auton() 
{
  fillStrip(strip.Color(0, 255, 0), 255);
  fillStripZ(strip.Color(0,255,0), 255);
}

/*void score()
{
 fillStrip(strip.Color(255,80,80), 255);
 fillStrip(strip.Color(255,80, 80);
 }*/
 
 void score()
 {
  for(byte i=0; i<64; i++) {
   byte whiteness = i*4;
   fillStrip(strip.Color(whiteness, 255, whiteness), 255);
   fillStripZ(strip.Color(whiteness, 255, whiteness), 255);
   strip.show();
   stripz.show();
  } 
 }

void uprights()
{
  if(robot_state == STATE_FULL) {
    fillStrip(strip.Color(0, 60, 0), 255);
    fillStripZ(strip.Color(0, 60, 0), 255);
  }
	//STABILIZER
	if(stabilizer_on)
	{
		for(uint16_t i=strip.numPixels(); i>4*strip.numPixels()/5; i--)
		{
			strip.setPixelColor(i,strip.Color(0,0,255));
                        stripz.setPixelColor(i,stripz.Color(0,0,255));
		}
	}
	
	//ELEVATOR
	if(elevator_auto)
	{
		for(uint16_t iii=0; iii<22; iii++)
		{
			strip.setPixelColor(iii,strip.Color(0,255,0));
                        stripz.setPixelColor(iii,stripz.Color(0,255,0));
		}
	}
	else
	{
		for(uint16_t iii=0; iii<22; iii++)
		{
			strip.setPixelColor(iii,strip.Color(255,0,0));
                        stripz.setPixelColor(iii,stripz.Color(255,0,0));
		}
	}
	
	//FINGER 
        
	for(uint16_t f=finger_height; f<finger_height+10;f++)
	{
                if(finger_on)
                {
                  strip.setPixelColor(f,strip.Color(0,255,0));
                  stripz.setPixelColor(f,stripz.Color(0,255,0));
                }
                else
                {
                  strip.setPixelColor(f,strip.Color(255,255,255));
                  stripz.setPixelColor(f,stripz.Color(255,255,255));
                }
	}
	
	//ROLLERS
	
}

void strobe()
{
	uint16_t i, c;
	c=strip.Color(0,255,0);
	
	if(on)
	{
		fillStrip(c, 255);
                //fillStripZ(c, 255);
		on = false;
	}
	else
	{
		fillStrip(strip.Color(0,0,0), 255);
		on=true;
	}
	delay(300);
	strip.show();
}


/*void strobepulse()
{
	uint32_t i, c,cc;
	
	c=strip.Color(0,255,0);
cc=stripz.Color(0,255,0);
	
	if(alliance==RED_ALLIANCE)
	{
		c=strip.Color(255,0,0);
cc=stripz.Color(255,0,0);
	}
	else if(alliance==BLUE_ALLIANCE)
	{
		c=strip.Color(0,0,255);
cc=stripz.Color(0,0,255);
	}
	else
	{
		c=strip.Color(0,255,0);
cc=stripz.Color(0,255,0);
	}
	
	for(i=0;i<=255;i+=5)
	{
		fillStrip(c, i);
                fillStripZ(cc, i);
		strip.show();
                stripz.show();
		delay(10);
	}
	
	for(i=255;i>0;i-=5)
	{
		fillStrip(c, i);
                fillStripZ(cc, i);
		strip.show();
                stripz.show();
		delay(10);
	} 

	
}*/
void sixtwofour()
{
	uint16_t i, c, s, t, f;
	c=strip.Color(0,255,0);
	
	s=6;
	t=2;
	f=4;
	
	for(i=0;i<(strip.numPixels()+s+t+f+15);i++)
	{
		strip.setPixelColor(i,c);
		strip.setPixelColor(i-s,0);
		strip.setPixelColor(i-s-5,c);
		strip.setPixelColor(i-s-5-t,0);
		strip.setPixelColor(i-s-5-t-5,c);
		strip.setPixelColor(i-s-5-t-5-f,0);
		strip.setPixelColor(i-s-5-t-5-f-5,0);
		//strip.setPixelColor(i+5,0);
		strip.show();
		delay(50);
	}
}

void win()
{
	uint32_t i,u,s,a;
	u=strip.Color(255,0,0);
	s=strip.Color(255,255,255);
	a=strip.Color(0,0,255);
	
	for(i=0;i<(strip.numPixels()+1+3+3+3+3+5+1+3+1+5+3+3+1);i++)
	{
		strip.setPixelColor(i,u);//dot
		strip.setPixelColor(i-1,0); //space
		strip.setPixelColor(i-1-3,u);//dash
		strip.setPixelColor(i-1-3-3,0);//space
		strip.setPixelColor(i-1-3-3-3,u);//dash
		strip.setPixelColor(i-1-3-3-3-3,0);//space W
		strip.setPixelColor(i-1-3-3-3-3-5,s);//dot
		strip.setPixelColor(i-1-3-3-3-3-5-1,0);//space
		strip.setPixelColor(i-1-3-3-3-3-5-1-3,s);//dot
		strip.setPixelColor(i-1-3-3-3-3-5-1-3-1,0);//space I
		strip.setPixelColor(i-1-3-3-3-3-5-1-3-1-5,a);//dash
		strip.setPixelColor(i-1-3-3-3-3-5-1-3-1-5-3,0);//space
		strip.setPixelColor(i-1-3-3-3-3-5-1-3-1-5-3-3,a);//dot N
		strip.setPixelColor(i-1-3-3-3-3-5-1-3-1-5-3-3-1,0);//space
		//strip.setPixelColor(i+5,0);
		strip.show();
		delay(200);
	}
} 

void scanner()
{
	uint16_t i, c, w;
	uint8_t distance,divisor,pulseHead;
	c=strip.Color(0,255,0);
	pulseHead=0;
	while(pulseHead<=strip.numPixels())
	{
		for(uint8_t i=0; i<strip.numPixels(); ++i) 
		{
			uint8_t divisor = 0;
			uint8_t distance = abs(i - pulseHead);
			if      (distance <= 2) divisor = 1;
			else if (distance <= 4) divisor = 2;
			else if (distance <= 6) divisor = 4;
			else if (distance <= 8) divisor = 6;
			else if (distance <= 10) divisor = 8;
			else if (distance <= 12) divisor = 10;
			else if (distance <= 14) divisor = 12;
			else divisor = 16; 
			strip.setPixelColor(i, 0, 255/divisor, 0);
		}
		pulseHead++;
		strip.show();
		delay(100);
	}
	
	
	
}

/*bool addTote()
{
	uint16_t i,ii,iii, c, cc;
	uint8_t w, w_n, b;
	c=strip.Color(0,255,0);
	cc=strip.Color(255,255,0);
	//i=0;
	w=(totes-1)*17;
	w_n = totes*17;
	for(i=0; i<w; i++)
	{
		strip.setPixelColor(i,strip.Color(0,255,0));
	}
	b=bins*45;
	for(ii=w; ii<(w+b); ii++)
	{
		strip.setPixelColor(ii,strip.Color(255,255,0));
	}
	strip.show();
	for(iii=(w+b); iii<(w_n+b);iii++)
	{
		strip.setPixelColor(iii,strip.Color(255,255,0));
		strip.setPixelColor(iii-b,0);
		strip.setPixelColor(iii-b,strip.Color(0,255,0));
		strip.setPixelColor(iii-b-w_n,0);
		strip.show();
		delay(50);
	}
	
	//strip.setPixelColor(w,c);
	//strip.setPixelColor(0,0);
	//strip.setPixelColor(i+5,0);
	return false;
}

bool addBin()
{
	uint16_t i,ii,iii, c, cc;
	uint8_t w, b_n, b;
	c=strip.Color(0,255,0);
	cc=strip.Color(255,255,0);
	//i=0;
	w = totes*17;
	for(i=0; i<w; i++)
	{
		strip.setPixelColor(i,strip.Color(0,255,0));
	}
	b=(bins-1)*45;
	b_n = bins*1;
	for(ii=w; ii<(w+b); ii++)
	{
		strip.setPixelColor(ii,strip.Color(255,255,0));
	}
	strip.show();
	for(iii=(w+b); iii<(b_n+w);iii++)
	{
		strip.setPixelColor(iii,strip.Color(255,255,0));
		strip.setPixelColor(iii-b_n,0);
		strip.setPixelColor(iii-b_n,strip.Color(0,255,0));
		strip.setPixelColor(iii-b_n-w,0);
		strip.show();
		delay(50);
	}
	
	//strip.setPixelColor(w,c);
	//strip.setPixelColor(0,0);
	//strip.setPixelColor(i+5,0);
	return false;
	
}*/


void pixelate()
{
	uint8_t i, px,pxs,pxss,pxz,pxsz,pxssz, color;
	uint32_t g, w, b,c;
	g=strip.Color(255,255,49);
	b=strip.Color(255,255,0);
	w=strip.Color(255,255,255);
	c=strip.Color(0,0,0);

uint32_t gz, wz, bz,cz;
	gz=stripz.Color(255,255,49);
	bz=stripz.Color(255,255,0);
	wz=stripz.Color(255,255,255);
	cz=stripz.Color(0,0,0);
	
	
	px = random(0,strip.numPixels());
	pxs = random(0,strip.numPixels());
        pxss = random(0,strip.numPixels());
	color = random(0,4);
	if(color==0)
	{
		strip.setPixelColor(px,g);
		strip.setPixelColor(pxs,g);
                strip.setPixelColor(pxss,g);
                
                stripz.setPixelColor(px,gz);
		stripz.setPixelColor(pxs,gz);
                stripz.setPixelColor(pxss,gz);
	}
	else if(color==1)
	{
		strip.setPixelColor(px,b);
		strip.setPixelColor(pxs,b);
                strip.setPixelColor(pxss,b);
                
                stripz.setPixelColor(px,bz);
		stripz.setPixelColor(pxs,bz);
                stripz.setPixelColor(pxss,bz);
	}
	else if(color==2)
	{
		strip.setPixelColor(px,c);
		strip.setPixelColor(pxs,c);
                strip.setPixelColor(pxss,c);
                
                stripz.setPixelColor(px,cz);
		stripz.setPixelColor(pxs,cz);
                stripz.setPixelColor(pxss,cz);
	} 
	else
	{
		strip.setPixelColor(px,w);
		strip.setPixelColor(pxs,w);
                strip.setPixelColor(pxss,w);
                
                stripz.setPixelColor(px,w);
		stripz.setPixelColor(pxs,w);
                stripz.setPixelColor(pxss,w);
	}

	
        strip.show();
	stripz.show();
	
}



void lavalamp()
{
  uint16_t t = millis() / 40;
  for(uint8_t i=0; i<122; i++) {
   uint8_t brightness = sin((t+i) / 4.0) * 255;
   uint8_t other = cos((t * 1.1 +i) / 3.5) * 255;
   brightness = brightness - other;
   uint8_t rrr = cos((t/1 + i/2) << 8) * 255;
   strip.setPixelColor(i, strip.Color(0, brightness, 0));
   stripz.setPixelColor(i, strip.Color(0, brightness, 0
   ));
  }
  uint32_t g;
  strip.show();
  stripz.show();
}
