/*
 * Drive size calculator!
 */

int drive_gb = 100;
long drive_mb;

void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  
  Serial.print("It can store ");
  Serial.print(drive_mb);
  Serial.println(" Megabytes!");
}

void loop()               // we need this to be here even though its empty
{

}
