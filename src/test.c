#include <stdio.h>
#include <string.h>

#define Z_STRING_IMPLEMENTATION
#include "include/zstring.h"

#define start_test(message) printf("[TEST] %s... ", message)
#define check_test(value, expected) printf("[%s] : %s\n", ((strcmp(value, expected) == 0) ? "PASS" : "FAIL"), value)

int main(void) { 

    start_test("Create string from C string");
    String from = string_from("Hello World");
    check_test(from.content, "Hello World");

    /* Needs Fixing - maybe definition order? */
    // start_test("Create string from format");
    // String from_format = string_from_format("%%, %s, %d, %u, %f", "Hello World", (int)69, (unsigned int)420, 0.5f);
    // check_test(from_format.content, "%, Hello World, 69, 420, 0.5");

    // string_drop(&from_format);

    /* Needs Fixing - maybe definition order? */
    start_test("Create string from C string, until index");
    String from_untill = string_from_until("Hello World", 3);
    check_test(from.content, "Hello");
    string_drop(&from_untill);

    start_test("Append C string to string");
    string_append(&from, ", Hol");
    check_test(from.content, "Hello World, Hol");

    start_test("Append char to string");
    string_append_c(&from, 'a');
    check_test(from.content, "Hello World, Hola");

    start_test("Trim the string");
    string_trim(&from);
    check_test(from.content, "HelloWorld,Hola");

    /* Needs Fixing - maybe definition order? */
    // start_test("Tokenize the string");
    // String token = string_tokenize(&from, "W");
    // check_test(token.content, "Hello");

    start_test("Flip the string");
    string_flip(&from);
    check_test(from.content, "aloH,dlroWolleH");

    /* Needs Fixing - maybe definition order? */
    start_test("Split the string");
    String lh = string_split(&from, 4);
    check_test(lh.content, "aloH");
    string_drop(&lh);

    /* Needs Fixing - maybe definition order? */
    start_test("Insert a c string into a string at index");
    string_insert(&from, "( :-) )", 3);
    check_test(from.content, ",dl( :-) )roWolleH");

    start_test("Remove a c string from a string");
    string_remove(&from, "( :-) )", "");
    check_test(from.content, ",dlroWolleH");

    start_test("Remove a character from a string");
    string_remove_c(&from, 'l', 2);
    check_test(from.content, ",droWoleH");

    string_drop(&from);
    return 0; 

}