class RFID_Command{
private:
  unsigned char buf[30],rebuf[30];
  unsigned char invent[30];
  unsigned char reinvent[30];

public:
  RFID_Command();
  ~RFID_Command();
  void Initialize(int );
  void GetConfig(int );
  void SetConfig(int );
  void BuzzerOn(int );
  void BuzzerOff(int );
  void RWPowerOff(int );
  char GetNoiseLevel(int );
  char* INVENTORY(int );
  char WRITE(int );
  char STAYQUIET(int );
};
