#include "pattern.h"

struct extracted_strings *test_extracted_data_from_string() /* \brief compress this into loops using dry */
{
#define EXIT_MSG "Executed the test program"
#define TEST_STRING " 19 \"" EXIT_MSG "\" 0 "
#if defined(TEST_STRING)
    struct extracted_strings *es = extract_data_from_string(TEST_STRING);
    if (!es)
    {
        printf("WARN: Could not allocate memory for extracted strings\n");
        return NULL;
    }

    size_t expected_number_of_groups = 4;
    if (es->number_of_groups == expected_number_of_groups)
    {
        printf("INFO: successfully matched the number of groups. [%zu]\n", es->number_of_groups);
    }
    else
    {
        printf("WARN: did not match the number of groups. expected [%zu] but got [%zu]\n", expected_number_of_groups, es->number_of_groups);
    }

    size_t expected_length_of_test_string = strlen(TEST_STRING);
    if (es->length_of_strings[0] == expected_length_of_test_string)
    {
        printf("INFO: successfully got the expected length of the whole string. [%zu]\n", es->length_of_strings[0]);
    }
    else
    {
        printf("WARN: did not get the expected length of the whole string. expected [%zu] but got [%zu]\n", expected_length_of_test_string, es->length_of_strings[0]);
    }

    size_t expected_length_of_first_substring = 2;
    if (es->length_of_strings[1] == expected_length_of_first_substring)
    {
        printf("INFO: successfully matched the length of the first substring. [%zu]\n", es->length_of_strings[1]);
    }
    else
    {
        printf("WARN: did not match the expected length of the first substring. expected [%zu] but got [%zu]\n", expected_length_of_first_substring, es->length_of_strings[1]);
    }

    size_t expected_length_of_second_substring = 28;
    if (es->length_of_strings[2] == expected_length_of_second_substring)
    {
        printf("INFO: successfully matched the length of the second substring. [%zu]\n", es->length_of_strings[2]);
    }
    else
    {
        printf("WARN: did not match the length of the second substring. expected [%zu] but got [%zu]\n", expected_length_of_second_substring, es->length_of_strings[2]);
    }

    int expected_length_of_third_substring = 1;
    if (es->length_of_strings[3] == expected_length_of_third_substring)
    {
        printf("INFO: successfully matched the length of the third substring. [%zu]\n", es->length_of_strings[3]);
    }
    else
    {
        printf("WARN: did not match the length of the third substring. expected [%zu] but got [%zu]\n", expected_length_of_third_substring, es->length_of_strings[3]);
    }

    char *expected_string = TEST_STRING;
    if (strcmp(es->strings[0], expected_string) == 0)
    {
        printf("INFO: full match for test string. \n\t%s\n%s\t\n", expected_string, es->strings[0]);
    }
    else
    {
        printf("WARN: no match for test string. \nexpected:\n\t%s\nbut got:\n\t%s\n", expected_string, es->strings[0]);
    }

    char *expected_first_substring = "19";
    if (strcmp(es->strings[1], expected_first_substring) == 0)
    {
        printf("INFO: full match for first test substring. \n\t%s\n\t%s\n", expected_first_substring, es->strings[1]);
    }
    else
    {
        printf("WARN: no match for first test substring. \nexpected:\n\t%s\nbut got:\n\t%s\n", expected_first_substring, es->strings[1]);
    }

    char *expected_second_substring = EXIT_MSG;
    if (strcmp(es->strings[2], expected_second_substring) == 0)
    {
        printf("INFO: full match for second test substring. \n\t%s\n\t%s\n", expected_second_substring, es->strings[2]);
    }
    else
    {
        printf("WARN: no match for second test substring. \nexpected:\n\t%s\nbut got:\n\t%s\n", expected_second_substring, es->strings[2]);
    }

    char *expected_third_substring = "0";
    if (strcmp(es->strings[3], expected_third_substring) == 0)
    {
        printf("INFO: full match for third test substring. \n\t%s\n\t%s\n", expected_third_substring, es->strings[3]);
    }
    else
    {
        printf("WARN: no match for third test substring. \nexpected:\n\t%s\nbut got:\n\t%s\n", expected_third_substring, es->strings[3]);
    }
    return es;
#endif // TEST_STRING
#undef TEST_STRING 
}