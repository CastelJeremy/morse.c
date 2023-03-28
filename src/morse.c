#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct morse_text
{
    char* morse;
    char  letter;
};

struct morse_text dictionnary[] = {
    { ".-",    'A' },
    { "-...",  'B' },
    { "-.-.",  'C' },
    { "-..",   'D' },
    { ".",     'E' },
    { "..-.",  'F' },
    { "--.",   'G' },
    { "....",  'H' },
    { "..",    'I' },
    { ".---",  'J' },
    { "-.-",   'K' },
    { ".-..",  'L' },
    { "--",    'M' },
    { "-.",    'N' },
    { "---",   'O' },
    { ".--.",  'P' },
    { "--.-",  'Q' },
    { ".-.",   'R' },
    { "...",   'S' },
    { "-",     'T' },
    { "..-",   'U' },
    { "...-",  'V' },
    { ".--",   'W' },
    { "-..-",  'X' },
    { "-.--",  'Y' },
    { "--..",  'Z' },
    { "-----", '0' },
    { ".----", '1' },
    { "..---", '2' },
    { "...--", '3' },
    { "....-", '4' },
    { ".....", '5' },
    { "-....", '6' },
    { "--...", '7' },
    { "---..", '8' },
    { "----.", '9' },
};

static inline void
do_encode (char* text)
{
    size_t text_length = strlen (text);
    for (size_t i = 0; i < text_length; i++) {
        char c = toupper (text[i]);

        if (c == ' ')
        {
            printf ("/ ");
        }
        else
        {
            for (int j = 0; j < 34; j++) {
                if (dictionnary[j].letter == c) {
                    printf ("%s ", dictionnary[j].morse);
                }
            }
        }
    }

    printf ("\n");

    exit (EXIT_SUCCESS);
}

static inline void
do_decode (char* morse)
{
    size_t morse_length = strlen (morse);

    char* word = calloc (6, sizeof (char));
    int word_length = 0;

    for (size_t i = 0; i < morse_length + 1; i++)
    {
        char c = morse[i];

        if (c == ' ' || i == morse_length)
        {
            if (word_length == 1 && word[0] == '/')
            {
                printf (" ");
            }
            else
            {
                for (int j = 0; j < 36; j++)
                {
                    if (strcmp (dictionnary[j].morse, word) == 0)
                    {
                        printf ("%c", dictionnary[j].letter);
                    }
                }
            }

            free (word);
            word = calloc (6, sizeof (char));
            word_length = 0;
        }
        else if (word_length < 5)
        {
            word[word_length++] = c;
        }
    }

    printf ("\n");

    exit (EXIT_SUCCESS);
}

static inline void
print_try_help ()
{
    fprintf (stderr, "Try 'morse --help' for more information.\n");
}

static inline void
usage (int status)
{
    if (status != EXIT_SUCCESS)
    {
        print_try_help ();
    }
    else
    {
        printf ("\
Usage: morse [options...]\n\
 -e, --encode <text>  Encode the text and show the morse value\n\
 -d, --decode <morse> Decode the morse and show the text value\n\
 -h, --help           Show this help message and quit\n\
 -v, --version        Show version number and quit\n");
    }

    exit (status);
}

static void
version ()
{
    printf ("1.0.0\n");
    exit (EXIT_SUCCESS);
}

int
main (int argc, char* argv[])
{
    struct option options[] = {
        { "encode",  required_argument, NULL, 'e' },
        { "decode",  required_argument, NULL, 'd' },
        { "help",    no_argument,       NULL, 'h' },
        { "version", no_argument,       NULL, 'v' }
    };

    char opt;
    opt = getopt_long (argc, argv, "e:d:hv", options, NULL);

    char* encode = NULL;
    char* decode = NULL;

    switch (opt)
    {
        case 'e':
            encode = optarg;
            break;
        case 'd':
            decode = optarg;
            break;
        case 'h':
            usage (EXIT_SUCCESS);
            break;
        case 'v':
            version ();
            break;
        case ':':
        case '?':
            usage (EXIT_FAILURE);
            break;
        default:
            printf ("morse: missing required option\n");
            usage (EXIT_FAILURE);
            break;
    }

    if (encode != NULL)
    {
        do_encode (encode);
    }

    if (decode != NULL)
    {
        do_decode (decode);
    }

    return EXIT_SUCCESS;
}
