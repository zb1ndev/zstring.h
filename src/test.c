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

    start_test("Append String to String");
    string_append(&from, ", and Joh");
    check_test(from.content, "Hello World, and Joh");

    start_test("Append Character to String");
    string_append_c(&from, 'n');
    check_test(from.content, "Hello World, and John");

    start_test("Create String from C string until Index");
    String from_until = string_from_until("Hello World", 3);
    check_test(from_until.content, "Hel");

    start_test("Flip String around");
    string_flip(&from_until);
    check_test(from_until.content, "leH");
    string_drop(&from_until);

    start_test("Create String from Integer");
    String string_as_int = int_to_string(-10);
    check_test(string_as_int.content, "-10");
    string_drop(&string_as_int);

    start_test("Create String from Unigned Integer");
    String string_as_uint = uint_to_string(10u);
    check_test(string_as_uint.content, "10");
    string_drop(&string_as_uint);

    start_test("Create String from Float");
    String string_as_float = float_to_string(10.5f);
    check_test(string_as_float.content, "10.500000");
    string_drop(&string_as_float);

    start_test("Create String from Format");
    String from_format = string_from_format("%%, %d, %u, %f, %s", -10, 10, 10.5, "Hello World");
    check_test(from_format.content, "%, -10, 10, 10.500000, Hello World");

    start_test("Trim Spaces from String");
    string_trim(&from_format);
    check_test(from_format.content, "%,-10,10,10.500000,HelloWorld");

    string_drop(&from_format);

    start_test("Split String at index 5");
    String lh = string_split(&from, 5);
    check_test(from.content, "World, and John");
    string_drop(&from);

    return 0; 

}