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

    FILE *file = fopen("text.txt", "r");  // ��������� ���� � ������������� ��� ������
    if (file == NULL) {
        printf("�� ������� ������� ����.\n");
        return 1;
    }

    char *text = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (text == NULL) {
        printf("������ ��������� ������.\n");
        return 1;
    }
    strcpy(text, "");  // �������������� ������ �������

    char *sentence = (char *)malloc(MAX_LENGTH * sizeof(char));
    if (sentence == NULL) {
        printf("������ ��������� ������.\n");
        free(text);
        return 1;
    }

    while (fgets(sentence, MAX_LENGTH, file) != NULL) {
        // ������� ������ ����� ������, ���� �� ������������
        sentence[strcspn(sentence, "\n")] = '\0';

        // ������� ����� ���������� �� �����������
        remove_punctuation(sentence);

        remove_spaces(sentence);  // ������� ������� ����� �������

        strcat(text, sentence);  // ��������� ����������� � ������
        strcat(text, " ");  // ��������� ������ ����� �����������

        // �������������� ������ � ������� ��������
        for (int i = 0; i < strlen(text); i++) {
            text[i] = tolower(text[i]);
        }

        // ����� � ������ ����������� � ������� �����������
        int length = strlen(text);
        int found = 0; // ����, �����������, ��� �� ������ ��������� � ������� �����������
        for (int i = 0; i < length; i++) {
            for (int j = i + 2; j <= length; j++) {
                char substring[MAX_LENGTH];
                strncpy(substring, text + i, j - i);
                substring[j - i] = '\0';
                if (is_palindrom(substring) && strlen(substring) > 3) {
                    printf("%s\n", substring);
                    found = 1; // ������������� ����, ��� ��������� ��� ������
                    break; // ��������� � ���������� �����������
                }
            }
            if (found) {
                break; // ���� ��������� ��� ������, ��������� � ���������� �����������
            }
        }

        // ������� ����� ��� ���������� �����������
        strcpy(text, "");
    }

    fclose(file);  // ��������� ����

    free(text);
    free(sentence);

    return 0;
}