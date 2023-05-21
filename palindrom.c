#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int is_palindrom(const char *word) {
    int length = strlen(word);
    for (int i = 0; i < length / 2; i++) {
        if (word[i] != word[length - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void remove_punctuation(char *sentence) {
    int length = strlen(sentence);
    for (int i = 0; i < length; i++) {
        if (ispunct(sentence[i])) {
            for (int j = i; j < length - 1; j++) {
                sentence[j] = sentence[j + 1];
            }
            sentence[length - 1] = '\0';
            length--;
            i--;
        }
    }
}

void remove_spaces(char *sentence) {
    int length = strlen(sentence);
    int i = 0;
    int j = 0;
    while (i < length) {
        if (sentence[i] != ' ') {
            sentence[j] = sentence[i];
            j++;
        }
        i++;
    }
    sentence[j] = '\0';
}

int main() {
    setlocale(LC_ALL, "Russian");

    FILE *file = fopen("text.txt", "r");  // Открываем файл с предложениями для чтения
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    char *text = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (text == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }
    strcpy(text, "");  // Инициализируем пустым текстом

    char *sentence = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (sentence == NULL) {
        printf("Ошибка выделения памяти.\n");
        free(text);
        return 1;
    }

    while (fgets(sentence, MAX_LENGTH, file) != NULL) {
        // Удаляем символ новой строки, если он присутствует
        sentence[strcspn(sentence, "\n")] = '\0';

        // Удаляем знаки препинания из предложения
        remove_punctuation(sentence);

        remove_spaces(sentence);  // Удаляем пробелы между словами

        strcat(text, sentence);  // Добавляем предложение к тексту
        strcat(text, " ");  // Добавляем пробел после предложения

        // Преобразование текста к нижнему регистру
        for (int i = 0; i < strlen(text); i++) {
            text[i] = tolower(text[i]);
        }

        // Поиск и печать палиндромов в текущем предложении
        int length = strlen(text);
        int found = 0; // Флаг, указывающий, был ли найден палиндром в текущем предложении
        for (int i = 0; i < length; i++) {
            for (int j = i + 2; j <= length; j++) {
                char substring[MAX_LENGTH];
                strncpy(substring, text + i, j - i);
                substring[j - i] = '\0';
                if (is_palindrom(substring) && strlen(substring) > 3) {
                    printf("%s\n", substring);
                    found = 1; // Устанавливаем флаг, что палиндром был найден
                    break; // Переходим к следующему предложению
                }
            }
            if (found) {
                break; // Если палиндром был найден, переходим к следующему предложению
            }
        }

        // Очищаем текст для следующего предложения
        strcpy(text, "");
    }

    fclose(file);  // Закрываем файл

    free(text);
    free(sentence);

    return 0;
}