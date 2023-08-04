# Wordle-Dictionary

Wordle game dictionary which filters words according to the arguments given.

Accepted command line arguments as follows: 
./wordle-helper [-alpha|-best] [-len word-length ] [-with letters ] [-without letters ] [pattern ]

Some examples of how the program might be run include the following
: 
./wordle-helper 
./wordle-helper -alpha 
./wordle-helper -best 
./wordle-helper -len 6 
./wordle-helper -with abB 
./wordle-helper -without xyZ 
./wordle-helper R___E 
./wordle-helper -alpha -len 6 -with os -without Xyz r_p__e 
./wordle-helper r_P__e -alpha -without XyZ -len 6 -with OS

• -alpha – if specified, this argument indicates that the output words must be sorted in alphabetical order
and all duplicates must be removed. If this option is specified, then the -best option must not be specified.

• -best – if specified, this argument indicates that the output words must be sorted in decreasing order of 
likelihood (as determined by the provided guess_compare() function – described later). Words with the 
same likelihood must be sorted alphabetically. Duplicates must be removed. If this option is specified, 
then the -alpha option must not be specified. 

• -len – if specified, this argument must be followed by an integer between 4 and 9 inclusive that indicates 
the length of the word to be used. If the argument is not specified, a default word length of 5 shall be 
used. 

• -with – if specified, this argument is followed by a set of letters that must be present in matching words. 
Letters can be listed in any order and with any case (i.e. uppercase and/or lowercase). If a letter is 
listed more than once then it must be present at least that number of times in matching words. The 
set of letters may be empty – which is the same as not specifying the -with argument. All matching is 
case-independent – e.g. an ‘A’ or ‘a’ in this set will match an ‘A’ or ‘a’ in the word. 

• -without – if specified, this argument is followed by a set of letters that must not be present in matching 
words. Letters may be listed more than once but this has the same effect as listing them once. Letters 
may be listed in any order or with any case. The set of letters may be empty – which is the same as not 
specifying the -without argument. All matching is case-independent – e.g. an ‘A’ or ‘a’ in this set means 
that neither ‘A’ nor ‘a’ should be present in the word. 

• pattern – if specified, this argument must be a string of the same length of words to be matched. The 
string must contain only letters (any case) and underscores. Words must match the pattern – i.e. must 
contain letters in the same position as letters that are present in the pattern, and any letter may match 
an underscore. A pattern of the right length consisting only of underscores is the same as not specifying 
a pattern (i.e. everything of the right length is a match). All matching is case independent.

