#include "main.h"
#define SDC_IMPLEMENTATION
#include "../../sdc/sdc.h"

// #define INILITE_DEBUG

#define INILITE_IMPLEMENTATION
#include "../inilite.h"

int main(void) {
    char content[512];
    SDC_io_read_entire_file(content, "input.ini");

    // DE-SERIALIZATION
    {
        Ini ini_in = {0};
        Ini_init(&ini_in, content);
        // _Ini_print(&i_in);

        IniSection *ini_db = Ini_get_section(&ini_in, "database");
        printf("name: %s\n", IniSection_get_value(ini_db, "name"));

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

        Ini_append_section(&ini_out, "itadori");
        Ini_append_kv(&ini_out, "name", "Yuji Itadori");
        Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer, Student");
        Ini_append_kv(&ini_out, "birthday", "March 20, 2003");

        char new_content[128 * 100] = {0};
        Ini_build(&ini_out, new_content);
        Ini_free(&ini_out);

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
