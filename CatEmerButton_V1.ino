/*
 *  緊急求救按紐 BW16 -> For Home
 *
 *  按下按鈕，傳資料到NodeRED，並讓蜂鳴器運作，按鈕燈亮
 *  NodeRED傳送Line Notify Infomation到家庭群組
 *  ----------------------------------------
 *	PinMap:
 *  PA12 -> LED
 *  PA30 -> BTN
 */

#define LED_PIN	PA12
#define BTN_PIN PA30

enum {FREE, BUSY} btnState = FREE;

void btnPressHandler(uint32_t id, uint32_t event)
{
	if(btnState == FREE)
	{
		btnState = BUSY;
		digitalWrite(LED_PIN, 0x01);
	}
}

void setup()
{
  	// put your setup code here, to run once:
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0x00);

	pinMode(BTN_PIN, INPUT_PULLUP);
	digitalSetIrqHandler(BTN_PIN, btnPressHandler);
}

void loop()
{
	
}
