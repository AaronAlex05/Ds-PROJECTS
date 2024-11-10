#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main() {
    // Set the locale to support Unicode
    setlocale(LC_CTYPE, "");

    // Use wide characters for Unicode
    wchar_t emoji[] = L"\U0001F60A"; // Smiling face emoji

    // Print the emoji
    wprintf(L"Here is a smiley emoji: %ls\n", emoji);

    return 0;
}