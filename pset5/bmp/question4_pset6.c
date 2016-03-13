/****************************************************************************
 *  Question #4. 
 * 
 *  How main goes about reading words from a file. In other words, 
 *  convince us that you indeed understand how that function’s for loop works.
 ***************************************************************************/

/*--------------------my answer ----------------------------------------------

        The spell-check section of speller.c keeps on reading one character 
        each from a file. It ensures that a scanned character is an 
        alphabetical character or, unless being the first letter of a word,
        apostrophe. Then it stores the character in character array word[index]
        and update index for next character to be stored.

        There are two conditions that make the word invalid:

            - If index exceeds LENGTH (= 45), the character string is not an
            English word given the fact 45 is the longest of English words.
            Therefore we proceed to next word by consuming remainder of
            alphabetical string and resetting index.
            - If text includes numbers, it can be considered as invalid.
            Therefore we move on to following word by eating up remaining 
            alphanumeric string and zeroing index.

        When a scanned character is NOT an alphabetical one nor apostrophe, 
        index greater than zero means that we have found a whole word with
        length the index indicates. 
        
        To finish off with a current whole word, we add a null-terminater to
        it, then update word counter.
   
----------------------------------------------------------------------------*/

// prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];                                        /* LENGTH 45: defined in dictionary.h */  
                                                                /* based on the fact the longest English word is 45 word long*/
// spell-check each word in text
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))            /* read one char each from the file 'text' until reaching EOF */
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))             /* allow only alphabetical characters and apostrophes(') */
                                                                /* unless it's the first letter of a word */
        {
            // append character to word
            word[index] = c;                                    /* put the character in char array 'word[index]' */                                                                        
            index++;                                            /* update index by +1 for next character to be stored */    

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)                                 /* if the index is greater than LENGTH, it is presumably NOT a word */
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(fp)) != EOF && isalpha(c));
                                                                
                // prepare for new word
                index = 0;                                      /* reset index to 0 for next word, because current word is invalid */
            }
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))                                    /* if the letter is a number, ignore and consume until reaching EOF */
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;                                          /* reset index to 0 for next word, because current word is invalid */
        }

        // we must have found a whole word
        else if (index > 0)                                     /* if index is not reset to zero, it means we have found a whole word */
        {
            // terminate current word
            word[index] = '\0';                                 /* add a null-terminater to a current word */

            // update counter
            words++;                                            /* update word counter by +1. */

            // check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);                     /* check if word is in dictionary */
            getrusage(RUSAGE_SELF, &after);

            // update benchmark
            ti_check += calculate(&before, &after);             /* add time spent for check function to ti_check for each word */

            // print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);                           /* if misspelled, print the word and */
                misspellings++;                                 /* update mosspellings counter by +1. */
            }

            // prepare for next word
            index = 0;                                          /* reset index to 0 for next word */
        }
    }
