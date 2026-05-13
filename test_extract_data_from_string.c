#include "pattern.h"

struct extracted_strings *test_extracted_data_from_string() /* \brief compress this into loops using dry */
{
#define BURST_TIME "19"
#define EXIT_MSG "Executed the test program"
#define EXIT_CODE "0"
#define TEST_STRING " "BURST_TIME" \"" EXIT_MSG "\" "EXIT_CODE" "
#if defined(TEST_STRING)
    struct extracted_strings *es = extract_data_from_string(TEST_STRING);
    if (!es)
    {
        printf("WARN: Could not allocate memory for extracted strings\n");
        return NULL;
    }

    struct extracted_strings ees = {
        .number_of_groups=4,
        .length_of_strings = calloc(ees.number_of_groups,sizeof(size_t)),
        .strings= calloc(ees.number_of_groups,sizeof(char))
    };

    char *expected_strings[] = {
        TEST_STRING,
        BURST_TIME,
        EXIT_MSG,
        EXIT_CODE
    };
    for (size_t group = 0; group < ees.number_of_groups; group++)
    {
        ees.length_of_strings[group] = (size_t)strlen(expected_strings[group]);
        ees.strings[group] = expected_strings[group];
    }

    char *context_words[] = {"whole", "first", "second", "third"};
    if (es->number_of_groups == ees.number_of_groups)
    {
        printf("INFO: successfully matched the number of groups. [%zu]\n", es->number_of_groups);
    }
    else
    {
        printf("WARN: did not match the number of groups. expected [%zu] but got [%zu]\n", ees.number_of_groups, es->number_of_groups);
    }

    for (size_t group = 0;group < ees.number_of_groups;group++) {
        char *what_string = (group) ? "substring" : "string";
        if (es->length_of_strings[group] == ees.length_of_strings[group])
        {
            printf("INFO: successfully got the expected length of the %s %s. [%zu]\n",context_words[group],what_string, es->length_of_strings[group]);
        }
        else
        {
            printf("WARN: did not get the expected length of the %s %s. expected [%zu] but got [%zu]\n",context_words[group],what_string, ees.length_of_strings[group], es->length_of_strings[group]);
        }

        if (strcmp(es->strings[group], ees.strings[group]) == 0)
        {
            printf("INFO: full match for test %s %s. \n\t%s\n\t%s\n",context_words[group],what_string, ees.strings[group], es->strings[group]);
        }
        else
        {
            printf("WARN: no match for test %s %s. \nexpected:\n\t%s\nbut got:\n\t%s\n", context_words[group],what_string , ees.strings[group], es->strings[group]);
        }
    }

    if (ees.length_of_strings)
        free(ees.length_of_strings);
    /* --- */
    if (ees.strings)
        free(ees.strings);
    /* --- */
    printf("we reach the end of test 1\n");

    return es;
#endif // TEST_STRING
#undef TEST_STRING 
}