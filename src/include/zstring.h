/* zstring.h - v1.1.1 - MIT License - https://github.com/zb1ndev/zstring.h 

    MIT License
    Copyright (c) 2025 Joel Zbinden

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.


    Version 1.1 Change-Log :
    - Added string_split.
    - Added string_insert.
    - Removed string_append_n.
    - Added string_append_format.

    Version 1.1.1 Change-Log :
    - string -> String

*/

#if !defined(Z_STRING_H)
#define  Z_STRING_H

    #include <stdlib.h> // realloc
    #include <string.h> // memcpy
    #include <stdarg.h> // va_args
    
    typedef struct String {
        
        char* content;
        size_t length;
        size_t capacity;

    } String;

    // String Createion

    /** A function that initializes a String structure with a value.
     * @param src The value you want the result to be initialized with.
     * @returns A String with the provided value as it's content.
     */
    String string_from(char* src);

    /** A function that initializes a String structure from a format.
     * @param format The format in which you want your String to be formed.
     * @param __VA_ARGS__ The items specifified by the specifiers in ```format```.
     * @returns A String with the provided format as it's content.
     * @note Implemented specifiers : ```%%```, ```%s```, ```%d```, ```%u```.
     */
    String string_from_format(const char* format, ...);

    // String Manipulation

    /** A function that appends a value to a string.
     * @param ptr The String you to append to.
     * @param src The value you want to append.
     * @returns Whether the function has succeded ```0 = success```.
     */
    int string_append(String* ptr, char* src); 

    /** A macro that appends a formated value to a string.
     * @param format The format in which you want your String to be formed.
     * @param __VA_ARGS__ The items specifified by the specifiers in ```format```.
     * @returns Whether the macro has succeded ```0 = success```.
     */
    #define string_append_format(ptr, format, ...) string_append(ptr, string_from_format(format, __VA_ARGS__).content)

    /** A function that appends a character to a string.
     * @param ptr The String you to append to.
     * @param src The character you want to append.
     * @returns Whether the function has succeded ```0 = success```.
     */
    int string_append_c(String* ptr, char src);

    /** A function that removes the spaces from a string.
     * @param ptr The String you want to trim.
     * @returns A pointer to the String provided.
     */
    String* string_trim(String* ptr);

    /** A function that compares two strings.
     * @param lh The left hand of the expression.
     * @param rh The right hand of the expression.
     * @returns Whether the function has succeded ```0 = success```.
     */
    int string_compare(String* lh, String* rh);

    /** A function that finds the first index of ```delimiter```.
     * @param ptr The String you want to check for delimiter.
     * @param delimiter The character you want to get the index of.
     * @returns The index of the first occurence of ```delimiter```.
     */
    ssize_t string_index_of(String* ptr, char delimiter);

    /** A function that creates a String from ```ptr``` with a length of ```index```.
     * @param ptr The String you want to pull from.
     * @param index The index where you want to stop copying.
     * @returns A String with the length of ```index``` containing ```ptr```.
     */
    String string_from_until(char* ptr, size_t index);

    /** A function that checks for delimiter.
     * @param ptr The String you want to check for ```delimiter```.
     * @param delimiter The character you want check for.
     * @returns Whether the ```delimiter``` occurs or not.
     */
    int string_has_char(String* ptr, char delimiter);

    /** A function that tokenizes a string.
     * @param ptr The String you want to tokenize, this value is set as the content after the delimiter.
     * @param delimiter The characters you want to separate the String by.
     * @returns The String content before the ```delimiter```.
     */
    String string_tokenize(String* ptr, char* delimiters); 

    /** A function that flips the String around.
     * @param ptr The String you want to flip.
     */
    void string_flip(String* ptr);
    
    /** A function that frees the contents of a string.
     * @param ptr The String you want to free.
     */
    void string_drop(String* ptr);

    /** A function that splits the String in two at ```index```. Puts left half in ```return``` and right half in ```ptr```.
     * @param ptr The String you want to split.
     * @param index The index you want to split at.
     * @returns The left half of the string.
     */
    String string_split(String* ptr, size_t index);

    /** A function inserts ```src``` into ```ptr``` at ```index```.
     * @param ptr The String you want to insert into.
     * @param src The String you want to insert.
     * @param index The index you want to insert to.
     * @returns Whether the function has succeded ```0 = success```.
     */
    void string_insert(String* ptr, char* src, size_t index);

    // Utilities

    /** A function that gets the length of a null terminated c-string.
     * @param str The Stringyou want to check to length of.
     * @returns The length of the Stringprovided.
     */
    size_t c_strlen(const char *str);

     /** A function that turns an integer into a string.
     * @param number The number you want to turn into a string.
     * @returns ```number``` as a string.
     */
    String int_to_string(ssize_t number);

    /** A function that turns an unsigned integer into a string.
     * @param number The number you want to turn into a string.
     * @returns ```number``` as a string.
     */
    String uint_to_string(size_t number);

#if defined(Z_STRING_IMPLEMENTATION)
    
#pragma region String Creation

    String string_from(char* src) {

        String return_value = { 0 };
        if (string_append(&return_value, src) == 0)
            return return_value;
        return (String){ 0 };

    }
    
    String string_from_format(const char* format, ...) {

        va_list args; 
        va_start(args, format); 
        String return_value = string_from("");

        for (size_t c = 0; format[c] != '\0'; c++) {
            if (format[c] == '%') {
                if (format[c+1] == '%') {
                    string_append(&return_value, "%");
                    c+=1;
                } else {
                    switch (format[c+=1]) {
                        case 's':
                            string_append(&return_value, va_arg(args, char*));
                            break;
                        case 'd':
                            string_append(&return_value, int_to_string(va_arg(args, size_t)).content);
                            break;
                        case 'u':
                            string_append(&return_value, uint_to_string(va_arg(args, ssize_t)).content);
                            break;
                        default:
                            break;
                    }
                }
            } else {
                string_append_c(&return_value, format[c]);
            }    
        }

        return return_value;

    }
    
#pragma endregion
#pragma region String Manipulation

    int string_append(String* ptr, char* src) {
        
        size_t src_length = c_strlen(src);
        if (src_length <= 0) return 0;

        size_t new_length = src_length + ptr->length;
        if (new_length > ptr->capacity)
            ptr->capacity += (src_length * 2);
    
        ptr->content = (char*)realloc(ptr->content, ptr->capacity); 
        if (ptr->content == NULL) return 1;

        memcpy(ptr->content + ptr->length, src, src_length);
        ptr->content[(ptr->length += src_length)] = '\0';

        return 0;
        
    }

    int string_append_c(String* ptr, char src) {
        
        if (ptr->length+1 > ptr->capacity)
            ptr->capacity += 4;
    
        ptr->content = (char*)realloc(ptr->content, ptr->capacity); 
        if (ptr->content == NULL) return 1;

        ptr->content[(ptr->length += 1) - 1] = src;
        ptr->content[ptr->length] = '\0';

        return 0;
        
    }

    String* string_trim(String* ptr) {

        char* buffer = (char*)malloc(ptr->length);
        size_t l = 0;
        for (size_t c = 0; c < ptr->length; c++)
            if (ptr->content[c] != ' ') 
            buffer[l++] = ptr->content[c];
        
        ptr->length = l;
        ptr->content = memcpy(ptr->content, buffer, l);
        ptr->content[ptr->length] = '\0';
        
        free(buffer);

        return ptr;

    }

    int string_compare(String* lh, String* rh) {

        if (lh->length != rh->length)
            return -1;
        
        for (size_t c = 0; c < lh->length; c++)
            if (lh->content[c] != rh->content[c])
                return -1;
                
        return 0;

    }

    ssize_t string_index_of(String* ptr, char delimiter) {

        for (size_t c = 0; c < ptr->length; c++)
            if (ptr->content[c] == delimiter)
                return c;

        return -1;

    }

    String string_from_until(char* ptr, size_t index) {

        if (index >= c_strlen(ptr)) {
            return string_from(ptr);
        }

        char* buffer = (char*)malloc(index+1);

        for (size_t i = 0; i < index+1; i++)
            buffer[i] = ptr[i];
        buffer[index+1] = '\0';

        return string_from(buffer);

    }

    int string_has_char(String* ptr, char delimiter) {

        for (size_t c = 0; c < ptr->length; c++)
            if (ptr->content[c] == delimiter)
                return 0;

        return -1;

    }

    String string_tokenize(String* ptr, char* delimiters) {

        ssize_t index = -1;
        String delimiters_as_string = string_from(delimiters);

        printf("%s\n", delimiters_as_string.content);

        for (size_t c = 0; c < ptr->length; c++) {
            if (string_has_char(&delimiters_as_string, ptr->content[c]) == 0) {
                index = c;
                break;
            }
        }
        if (index < 0 || index >= ptr->length) 
            return string_from(ptr->content);

        String return_value = string_from_until(ptr->content, index);
        *ptr = string_from(ptr->content + index + 1);

        return return_value;

    }

    void string_flip(String* ptr) {

        for (int j = 0, k = ptr->length - 1; j < k; j++, k--) {
            char temp = ptr->content[j];
            ptr->content[j] = ptr->content[k];
            ptr->content[k] = temp;
        }

    }

    String string_split(String* ptr, size_t index) {

        if (index == 0)
            return string_from("");

        if (index >= ptr->length) {
            String return_value = string_from(ptr->content); 
            ptr->content = ptr->content + ptr->length;
            return return_value;
        }

        String return_value = string_from_until(ptr->content, index-1);
        ptr->content = ptr->content+index;

        return return_value;

    }

    void string_insert(String* ptr, char* src, size_t index) {

        String left = string_split(ptr, index);
        String result = string_from_format("%s%s%s", left.content, src, ptr->content);
        *ptr = result;

    }

#pragma endregion
#pragma region Utilities

    void string_drop(String* ptr) {
        if (ptr->content)
            free(ptr->content);
    }

    size_t c_strlen(const char *str) {

        const char *_p = str;
        while (*_p) _p++;
        return _p - str;

    }

    String int_to_string(ssize_t number) {

        String return_value = string_from("");
        ssize_t sign = number;

        if (number < 0 )
            number = -number;
        while (number > 0) {
            string_append_c(&return_value, number%10+'0');
            number/=10;
        }

        if (sign < 0)
            string_append_c(&return_value, '-');
        string_flip(&return_value);
        
        return return_value;

    }

    String uint_to_string(size_t number) {

        String return_value = string_from("");
        while (number > 0) {
            string_append_c(&return_value, number%10+'0');
            number/=10;
        }
        string_flip(&return_value);
        
        return return_value;

    }

#pragma endregion

#endif
#endif