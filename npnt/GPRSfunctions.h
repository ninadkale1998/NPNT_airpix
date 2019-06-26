

/**************************************************************************************************************************/

void ShowSerialData(){
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}

/**************************************************************************************************************************/


/**************************************************************************************************************************/
void Initgprs(){
  
  Serial.println("init_gprs:");
  
  SIM900.println("AT"); /* Check Communication */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  /* Configure bearer profile 1 */
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  /* Connection type GPRS */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");  /* APN of the provider */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+HTTPINIT"); /* Initialize HTTP service */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+HTTPPARA=\"CID\",1");  /* Set parameters for HTTP session */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  SIM900.println("AT+HTTPPARA=\"URL\",\"npntairpix.herokuapp.com/api/flightPermission/arm?droneId=5d023d85884430c198a246cf\"");  /* Set parameters for HTTP session */
  delay(1000);
  ShowSerialData();
  delay(1000);
  
  Serial.println("done");
  
  }

String ReadSerialData(){

  //for(int i = 0; i < 7 ; i++){ SIM900.read(); }
   return String (SIM900.readString());
}

/**************************************************************************************************************************/

void Ping_server(){
  
  timer = millis()-prevtime;
  if(case_no ==0 ){
    SIM900.println("AT+HTTPACTION=0");  /* Start GET session */
    case_no++;
    prevtime = millis();
      //SIM900.print("AT+CMGDA=\""); 
      //SIM900.println("DEL ALL\"");
      SIM900.flush();
      
    }
    
 switch(case_no){

  case 1:if(timer > 15000){
            data = ReadSerialData();
            case_no++;
             
            prevtime = millis();
            }
            break; 
  case 2: if(timer > 2000){
               SIM900.println("AT+HTTPREAD"); 
               case_no++;
                
               prevtime = millis();
            }
            break;   
  case 3: if(timer > 200){
              
              data1 = ReadSerialData();
              Serial.println("************");
              Serial.println(data1);
              Serial.println("************");
              case_no++;
              Serial.println("3"); 
              prevtime = millis();
              
              index_of_arm = data1.indexOf('arm');
              index_of_rtl = data1.indexOf('rtl');
              //Serial.println(index_of_rtl);
              //Serial.println(index_of_arm);
              if (index_of_arm  != -1){
                arm = true;
                rtl = false;
                Serial.println("arm");
              }
              
              else if (index_of_rtl  != -1){
                arm = false;
                rtl = true; 
               Serial.println("rtl");
              }
          
              else{
                arm = false;
                rtl = false;
                Serial.println("wait");
                
                }
              case_no = 0; 
              prevtime = millis();
              //SIM900.print("AT+CMGDA=\""); 
              //SIM900.println("DEL ALL\"");
              
              
          }
          break;
   default: case_no=0;
            break;      
 }
}

 
