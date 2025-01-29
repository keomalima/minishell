enum state {
    STATE_GENERAL,
    STATE_IN_FILENAME,
    OTHER,
};

// Many characters are treated the same (e.g. 'x' and 'y') - so use categories
enum character_category
{
    CHAR_GENERAL, // can appear in filenames
    CHAR_WHITESPACE = ' ',
    CHAR_AMPERSAND = '&',
    CHAR_PIPE = '|',
    CHAR_EOF = EOF,
    ...
};

character_category translate(int c)
{
    switch (c) {
    case '&': return CHAR_AMPERSAND;
    case ' ': case '\t': case '\n': return CHAR_WHITESPACE;
    ...
    default: return CHAR_GENERAL;
    }
}

void do_stuff()
{
    character_category cat;
    state current_state = STATE_GENERAL;
    state next_state;
    char token[100];
    char token_length = 0;
    do {
        int c = getchar();
        cat = translate(c);
        // The following implements a switch on 2 variables
        int selector = 1000 * current_state + cat;

        switch (selector)
        {
        case 1000 * STATE_GENERAL + CHAR_GENERAL:
            next_state = STATE_IN_FILENAME;
            token[token_length++] = c; // append a character to a filename token
            break;

        case 1000 * STATE_GENERAL + CHAR_WHITESPACE:
            next_state = STATE_GENERAL; // do nothing
            break;

        case 1000 * STATE_GENERAL + CHAR_PIPE:
            next_state = STATE_IN_OR_TOKEN; // the first char in '||' or just '|'
            break;

        // Much repetitive code already; define a macro for the case constants?
        // Have to cover all states and all character categories; good luck...

        case 1000 * STATE_IN_FILENAME + EOF:
        case 1000 * STATE_IN_FILENAME + CHAR_WHITESPACE:
            next_state = STATE_GENERAL;
            printf("Filename token: %s\n", token);
            break;

        default:
            printf("Bug\n"); // forgot one of the cases?
        }

        current_state = next_state;

    } while (cat != CHAR_EOF);
}