#include "main.h"
#define SDC_IMPLEMENTATION
#include "../../sdc/sdc.h"

// #define INILITE_DEBUG

#define INILITE_IMPLEMENTATION
#include "../inilite.h"

int main(void) {
    char content[8000];
    if (!SDC_io_read_entire_file(content, "output.ini")) {
        fprintf(stderr, "input file not found\n");
        return 0;
    }

    // DE-SERIALIZATION
    {
        Ini ini_in = {0};
        Ini_init(&ini_in, content);
        // _Ini_print(&ini_in);

#define N_TREES 4
        const char *trees[N_TREES] = {"birch", "oak", "spruce", "apple"};
        for (size_t i = 0; i < N_TREES; i++) {
            char tree[128];
            snprintf(tree, 128, "trees.%s", trees[i]);
            IniSection *ini_db = Ini_get_section(&ini_in, tree);
            if (!ini_db) {
                fprintf(stderr, "tree: %s not found\n", trees[i]);
                continue;
            }

            char *v = IniSection_get_value(ini_db, "color");
            if (!v) {
                fprintf(stderr, "tree: %s color not found\n", trees[i]);
                continue;
            }
            printf("tree: %s, color: %s\n", trees[i], v);
        }

        Ini_free(&ini_in);
    }

    // SERIALIZATION
    // {
    //     Ini ini_out = {0};
    //     Ini_init(&ini_out, NULL);
    //
    //     Ini_append_section(&ini_out, "gojo");
    //     Ini_append_kv(&ini_out, "name", "Satoru Gojo");
    //     Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer");
    //     Ini_append_kv(&ini_out, "birthday", "December 7, 1989");
    //     Ini_append_kv(
    //             &ini_out, "description",
    //             "Satoru Gojo is known as the strongest jujutsu sorcerer within
    //             the " "modern jujutsu society. He earned this alias in part due
    //             to the " "immense amounts of cursed energy he possesses. Gojo's
    //             vast cursed " "energy, combined with his cursed energy
    //             efficiency, allows him to " "expand his domain at least five
    //             times in one day, while most " "sorcerers and special grade
    //             cursed spirits can only use it once. " "Throughout his fight
    //             with Sukuna, Gojo used cursed energy to " "constantly reinforce
    //             himself and activate his cursed techniques " "multiple times,
    //             without ever showing signs of exhausting his " "reserves. ");
    //
    //     Ini_append_section(&ini_out, "itadori");
    //     Ini_append_kv(&ini_out, "name", "Yuji Itadori");
    //     Ini_append_kv(&ini_out, "occupation", "Jujutsu Sorcerer, Student");
    //     Ini_append_kv(&ini_out, "birthday", "March 20, 2003");
    //
    //     char new_content[128 * 100] = {0};
    //     Ini_build(&ini_out, new_content);
    //     Ini_free(&ini_out);
    //
    //     // printf("%s", new_content);
    //
    //     FILE *output = fopen("output.ini", "w");
    //     fprintf(output, "%s", new_content);
    // }
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
