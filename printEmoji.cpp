#include<fcntl.h>
#include<io.h>
#include<stdio.h>
#include<locale.h>
#include<utility>


int main(){
    // setmode(_fileno(stdout),0x00040000);
    // wprintf(L"");
    // setlocale(LC_ALL, "en_US.utf8");
    _setmode(_fileno(stdout), 0x00020000); // _O_U16TEXT
    // wprintf(L"\x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd  \xF0\x9F\x8D\xB8 \n");
    const char martini[5] = {0xF0, 0x9F, 0x8D, 0xB8, '\0'};
    printf("Let's go drink some %s\n\n", martini);

    std::pair<int,int> p;

    return 0;
}