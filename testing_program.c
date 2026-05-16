#include "input.h"
#include "OSIIA1_pattern.h"

#if defined(TEST_THIS_CODE)

int testing_program(int argc,char** argv) 
{
    struct extracted_strings *es = test_extracted_data_from_string();
    printf("INFO: %s. es -> %p ", (es) ? "success es allocated" : "error. es not allocated" , es);

    printf("Successfully tested\n");
    if (es==NULL)
    {
        test_free_extracted_strings(es);
        printf("INFO: Freed es\n");
    }
    return 0;
}
#endif // TEST_THIS_CODE