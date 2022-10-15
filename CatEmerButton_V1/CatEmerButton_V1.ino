/*
 *  緊急求救紐 BW16 -> For Home
 *
 *  作用：按下按鈕，讓蜂鳴器運作，按鈕燈亮，並傳送UDP封包至NodeRED Server。
 *
 *  <2S         : No Operaion                       (Foolproof / 防呆機制)
 *  >2S & <20S  : One Shot Message                  (Normal Emergency / 一般嚴重狀態)
 *  <20S        : 3 Shot Message & Call 119 API     (Very Emergency / 緊急嚴重狀態)
 *
 *  ----------------------------------------
 *	PinMap:
 *  | PA12 -> LED
 *  | PA30 -> BTN
 *  | PA14 -> BEEP
 */

#include <wdt_api.h>
#include <GTimer.h>

#define COUNT_MS(x)     x * 1000
#define COUNT_US(x)     COUNT_MS(x) * 1000

#define LED_PIN	        PA12        // LED      : Output
#define BTN_PIN         PA30        // Button   : Input
#define BEEP_PIN        PA14        // Beep     : Output 

enum {FREE, BUSY} btnState = FREE;

void timeoutHandler(uint32_t data);
void btnPressHandler(uint32_t id, uint32_t event);

void setup()
{
    // Stop WatchDog
    watchdog_stop();

    // Led & Beep
	pinMode(LED_PIN, OUTPUT);
    pinMode(BEEP_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0x00);
    digitalWrite(BEEP_PIN, 0x00);

    // Button
	pinMode(BTN_PIN, INPUT_IRQ_RISE);

	// Set Button Interrupt Handler
    digitalSetIrqHandler(BTN_PIN, btnPressHandler);
}

void loop()
{
	// No Operation, Just Empty.
}

void btnPressHandler(uint32_t id, uint32_t event)
{
    // Clear Button Interrupt Handler 
    digitalClearIrqHandler(BTN_PIN);

    GTimer.begin(0, COUNT_US(1), timeoutHandler, false, 0);
}

void timeoutHandler(uint32_t data)
{
    // Get Button State And Set it to LED And BEEP.
    bool state = digitalRead(BTN_PIN);
    digitalWrite(LED_PIN, state);

    // Set Button Interrupt Handler 
    digitalSetIrqHandler(BTN_PIN, btnPressHandler); 
}