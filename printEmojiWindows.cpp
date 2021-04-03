#include<fcntl.h>
#include<io.h>
#include<stdio.h>
#include<string>
using namespace std;
int main(void) {

    // _O_U16TEXT=0x00020000 and _O_U8TEXT=0x00040000
    _setmode(_fileno(stdout), 0x00020000);
    wprintf(L"\x263a ");
    return 0;
}