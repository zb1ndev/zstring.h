#include <stdio.h>

#define Z_STRING_IMPLEMENTATION
#include "include/zstring.h"

#pragma region Todo

    struct TodoItems {

        String* items;
        size_t length;
        size_t capacity;

    };

    int todo_append(struct TodoItems* ptr, String src) {

        if (src.length <= 0)        
            return 0;
        
        if (ptr->length++ >= ptr->capacity)
            ptr->capacity += (ptr->length * 2);

        ptr->items = (String*)realloc(ptr->items, sizeof(String) * ptr->capacity);
        if (ptr->items == NULL)
            return 1;   

        ptr->items[ptr->length-1] = src;

        return 0;
        
    }

    int todo_remove(struct TodoItems* ptr, int index) {

        if (index >= ptr->length) {
            printf("[ERROR] Cant remove index, does not exist\n");
            return 1;
        }

        for (size_t i = 0, j = 0; i < ptr->length; i++) {
            if (i == index) j++;
            ptr->items[i] =  ptr->items[i+j];
        }

        ptr->length--;
        return 0;

    }

    void Todo() {

        struct TodoItems todo_list = (struct TodoItems){ 0 };
        
        char buffer[1024];
        unsigned char quit = 0;

        while (quit == 0) {
            
            printf("\n ---- TODO LIST ---- \n");
            for (size_t i = 0; i < todo_list.length; i++)
                printf("%ld : %s", i, todo_list.items[i].content);

            printf("\nadd | remove | quit\n>> ");
            String s = string_from(fgets(buffer, 100, stdin));

            if (strcmp(s.content, "quit\n") == 0) {
                string_drop(&s);
                break;
            }
            
            if (strcmp(s.content, "add\n") == 0) {
                printf("%ld >> ", todo_list.length);
                todo_append(&todo_list, string_from(fgets(buffer, 100, stdin)));
            }

            else if (strcmp(s.content, "remove\n") == 0) {
                printf("Enter the index >> ");
                todo_remove(&todo_list, atoi(fgets(buffer, 100, stdin)));
            }

            string_drop(&s);

        }

    }

#pragma endregion

int main() { 

    

    return 0; 

}