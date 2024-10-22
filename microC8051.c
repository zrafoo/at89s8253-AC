// Îáúÿâëåíèå ãëîáàëüíûõ ïåðåìåííûõ
unsigned char received_data = 0; // Ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðèíÿòîãî ñèìâîëà
unsigned char button_pressed = 0xFF; // Ïåðåìåííàÿ äëÿ õðàíåíèÿ ñîñòîÿíèÿ êíîïîê
unsigned char *transmit_buffer = 0;
unsigned char transmit_in_progress = 0;
void UART_Init()
{

        T2CON = 0x34;
        TMOD = 0x20;      
        T2MOD = 0x00;          /* Timer 1, 8-bit auto reload mode */
        TH2 = RCAP2H = 0xff;
        TL2 = RCAP2L = 0xEF;   // 19200 - ffef, 9600 - ffdf
        SCON = 0x50;              /* Mode 1, reception enable */
        PCON = 0x80;
        TR2_bit = 1;
        ES_bit = 1;
        EA_bit = 1;               /* Start timer 1 */

}


void UART_WriteString(unsigned char *str)
{
 if (!transmit_in_progress)
 {
    transmit_buffer = str;
    transmit_in_progress = 1;
    SBUF = *transmit_buffer++;

 }
 
}
/*
void UART_ISR() iv IVT_ADDR_ES ilevel 1 ics ICS_AUTO
{
     if (RI_bit)
     {
         received_data = SBUF;
         RI_bit = 0;
         P1 = received_data;
     }
     if (TI_bit)
     {
         TI_bit = 0;

         if (*transmit_buffer != '\0')
         {
            SBUF = *transmit_buffer++;
         }
         else
         {
            transmit_in_progress = 0;
         }
     }
}
 
*/

void SPI_Init()
{
        SPCR = 0b11010000;

}

void UART_Write1(unsigned char data1)
{
    SBUF = data1;          // Çàãðóçêà äàííûõ â áóôåð ïåðåäà÷è
    while (TI_bit == 0);      // Îæèäàíèå îêîí÷àíèÿ ïåðåäà÷è
    TI_bit = 0;           // Ñáðîñ ôëàãà ïðåðûâàíèÿ ïåðåäà÷è
}

unsigned char SPI_Transfer(unsigned char data1) {
    SPDR = data1;
    while(!(SPSR & 0x80));
    return SPDR;
}

unsigned int SPI_Read_ADC(unsigned char channel) {
    unsigned int adc_value;
    unsigned char msb, lsb;
    unsigned char bufff;

    P2_0_bit = 0;
    SPDR = 0b00000110;//0x06 | ((channel & 0x04) >> 2);
    while (!(SPSR & 0x80));
    bufff = SPDR;
    SPDR = 0x00;//(channel & 0x03) << 6;
    while (!(SPSR & 0x80));
    msb = SPDR & 0x0F;
    SPDR = 0x00;
    while (!(SPSR & 0x80));
    lsb = SPDR;

    P2_0_bit = 1;
    adc_value = (msb << 8) | lsb;
    return adc_value;
}

void Send_ADC_Data(unsigned char channel, unsigned int adc_value) {


    UART_Write1(0xAA);
    UART_Write1((adc_value >> 8) & 0xFF);
    UART_Write1(adc_value & 0xFF);
    UART_Write1(0xBB);
}


void main(void)
{
    unsigned int adc_value;
    unsigned char channel = 0;
    UART_Init();
   /*P1 = 0x00;*/
    SPI_Init();

    while (1)
    {
        adc_value = SPI_Read_ADC(channel);
        Send_ADC_Data(channel, adc_value);

    }
    
}
