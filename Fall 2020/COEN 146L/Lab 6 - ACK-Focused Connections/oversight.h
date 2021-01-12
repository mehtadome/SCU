#define PBADCKSUM 5
#define PLEN 10     // packet length of 10

typedef struct {
    int seq_ack;
    int len;
    int cksum;
} Header;

typedef struct {
    Header header;
    char data [PLEN];
} Packet;

int getChecksum(Packet packet);
void logPacket(Packet packet);
