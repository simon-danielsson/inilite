#include "main.h"
#define SDC_IMPLEMENTATION
#include "../../sdc/sdc.h"

// #define INILITE_DEBUG

#define INILITE_IMPLEMENTATION
#include "../inilite.h"

int main(void) {
    char content[64 * 1000];
    if (!SDC_io_read_entire_file(content, "input.ini")) {
        fprintf(stderr, "input file not found\n");
        return 0;
    }

    // DE-SERIALIZATION
    {
        Ini ini_in = {0};
        Ini_init(&ini_in, content);
        _Ini_print(&ini_in);

        // IniSection *ini_db = Ini_get_section(&ini_in, "gojo");
        // if (!ini_db) {
        //     fprintf(stderr, "section not found\n");
        //     return 0;
        // }
        //
        // char *v = IniSection_get_value(ini_db, "descr");
        // if (!v) {
        //     fprintf(stderr, "value not found\n");
        //     return 0;
        // }

        // printf("%s\n", v);

        Ini_free(&ini_in);
    }

    // SERIALIZATION
    {
        Ini ini_out = {0};
        Ini_init(&ini_out, NULL);

        Ini_append_section(&ini_out, "gojo");
        Ini_append_kv(&ini_out, "name", "Satoru Gojo");
        Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer");
        Ini_append_kv(&ini_out, "birthday", "December 7, 1989");
        Ini_append_kv(&ini_out, "description",
                "Satoru Gojo is known as the strongest jujutsu sorcerer "
                "within the modern jujutsu society.");

        Ini_append_section(&ini_out, "itadori");
        Ini_append_kv(&ini_out, "name", "Yuji Itadori");
        Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer, Student");
        Ini_append_kv(&ini_out, "birthday", "March 20, 2003");

        char new_content[128 * 100] = {0};
        Ini_build(&ini_out, new_content);
        Ini_free(&ini_out);

        // printf("%s", new_content);

        FILE *output = fopen("output.ini", "w");
        fprintf(output, "%s", new_content);
    }
    return 0;
}

/*

   Sketch of how the UX could look like =======================================

   ==> DE-SERIALIZATION

   {

   char *ini_content;
   Ini i_in = {0};
   Ini_init(&i_in, ini_content);

   IniSection my_section = Ini_get_section(&i_in, "name_of_section")

   print("%s\n", IniSection_get_value(&my_section, "name_of_key"));

   Ini_free(&i_in);

   }

   ==> SERIALIZATION

   {

   Ini i_out = {0};
   Ini_init(&i_out, NULL);

   Ini_append_section(&i_out, (IniSection){...});
   char *new_content = Ini_build(&i_out);

   Ini_free(&i_out);

   (proceed to write the `new_content` variable to a file or whatever else)

   }

   ============================================================================

*/
