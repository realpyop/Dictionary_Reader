/*
Author: An Van
Course: CSCI-135
Assignment: PROJECT1 - TaskA
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <string>
#include <stdlib.h>
using namespace std;

const int MAX_WORDS = 1000;
int word_count = 0;
string words[MAX_WORDS];
string definitions[MAX_WORDS];
string pos[MAX_WORDS];


/**
    @param : The string with the `filename`
    @post : Reads the words, definitions and pos into the global-arrays and set the value of `word_count to the number of words read

*/
void readWords(string filename)
{
    ifstream fin(filename);
    if (fin.fail())
    {
        cout << "File failed to open." << endl; 
    }

    string fileword, filepos,filedefinitions,filecolon,empty; 
    while (fin >> fileword >> filepos >> filecolon)
    {
        words[word_count] = fileword;
        pos[word_count] = filepos;
        getline(fin,filedefinitions); 
        definitions[word_count] = filedefinitions.substr(1);
        word_count++; 
    }
    fin.close();
}




/**
    @param            :   The string with a query word
    @return           :   Integer index of the word in
                          `words` global-array. Returns
                          -1 if the word is not found
    @post             :   Find the index of given `word`
                          in the `words` array. Return -1
                          if word is not in the array
*/
int getIndex(string word)
{
    int index;
    int counter = 0; 
    for (int i = 0; i < word_count; i++)
    {
        if (words[i] == word)
        {
            index = i; 
        }
        else
        {
            counter += 1; 
        }
    }
    if (counter == word_count)
    {
        index = -1; 
    }

    return index; 
}




/**
    @param            :   The string with a query word
    @return           :   Return the string definition of
                          the word from  `definitions`
                          global-array. Return "NOT_FOUND" if
                          word doesn't exist in the dictionary
    @post             :   Find the definition of the given `word`
                          Return "NOT_FOUND" otherwise
*/
string getDefinition(string word)
{
    int index = getIndex(word);
    if (index == -1)
    {
        return "NOT_FOUND"; 
    }

    string definition = definitions[index];
    return definition; 
}



/**
    @param            :   The string with a query word
    @return           :   Return the string part-of-speech(pos) 
                          from the `pos` global-array. Return
                          "NOT_FOUND" if the word doesn't exist
                          in the dictionary.
    @post             :   Find the pos of the given `word`
                          Return "NOT_FOUND" otherwise
*/
string getPOS(string word)
{
    int index = getIndex(word);
    if (index == -1)
    {
        return "NOT_FOUND"; 
    }

    string wanted_pos = pos[index];
    return wanted_pos; 
}




/**
    @param            :   The string prefix of a word (the prefix
                          can be of any length)
    @return           :   Integer number of words found that starts
                          with the given `prefix`
    @post             :   Count the words that start with the given
                          `prefix`
*/
int countPrefix(string prefix)
{
    int PREFIX_SIZE = prefix.length();
    int PREFIX_COUNT = 0; 
    for ( int i = 0; i < MAX_WORDS; i++)
    {
        if(words[i].substr(0, PREFIX_SIZE) == prefix)
        {
            PREFIX_COUNT++;
        }
    }

    return PREFIX_COUNT; 
}



/**
    @param new_word         :   The string with a new word
    @param new_definition   :   The string with the definition of the
                                `new_word`
    @param new_pos          :   The string with the pos of the `new_word`
    @return                 :   return `true` if the word is
                                successfully added to the dictionary
                                return `false` if failed (word already
                                exists or dictionary is full)
    @post                   :   Add the given `new_word`, `new_definition`, 
                                `new_pos` to the end of the respective
                                global-arrays.
                                The word should not be added to the
                                global-arrays if it already exists 
                                or if the array reached maximum 
                                capacity(`MAX_WORDS`).
                                Update `word_count` if the word is
                                successfully added
*/
bool addWord(string new_word, string new_definition, string new_pos)
{
    int index = getIndex(new_word);
    if (index == -1)
    {
        words[word_count] = new_word; 
        definitions[word_count] = new_definition;
        pos[word_count] = new_pos;
        word_count++;
        return true;
    }
    else
    {
        return false; 
    }
}


/**
    @param word             :   The string with the word that is to
                                be edited
    @param new_definition   :   The string with the new definition of 
                                the `word`
    @param new_pos          :   The string with the new pos of the `word`
    @return                 :   return `true` if the word is successfully
                                edited, return `false` if the `word`
                                doesn't exist in the dictionary
    @post                   :   Replace the given `word`'s  definition
                                and pos with the given `new_definition` and
                                `new_pos` (by modifying global-arrays
                                `definitions` and `pos`).
                                The modification will fail if the word
                                doesn't exist in the dictionary
*/
bool editWord(string word, string new_definition, string new_pos)
{
    int index = getIndex(word);
    if (index != -1)
    {
        words[index] = word; 
        definitions[index] = new_definition;
        pos[index] = new_pos;
        return true;
    }
    else
    {
        return false; 
    }
}


/**
    @param            :   The string with the word that is to
                          be removed
    @return           :   return `true` if the word is successfully
                          removed from the dictionary return `false`
                          if the word doesn't exist in the dictionary
    @post             :   Remove the given `word`, `word`'s
                          definition and `word`'s pos from the
                          respective global-arrays if the word
                          exists.  
                          Update `word_count` if the word is
                          successfully removed
*/
bool removeWord(string word)
{
    int index = getIndex(word);
    if (index != -1)
    {
        for (int i = index; i < word_count; i++)
        {
            words[i] = words[i+1];
            definitions[i] = definitions[i+1];
            pos[i] = pos[i+1];
        }
    }
    else
    {
        return false; 
    }

    word_count -= 1; 
    return true; 
}

/**
    @param            :   The string with a word from the dictionary 
    @return           :   string of "_" based on the number of
                          characters in the given `word` 
    @post             :   Return string of "_" based on the length
                          of the given `word`.
                          For example, if the word is "game", then
                          the function would return "____". In other
                          words, a string of four "_"s.
*/
string maskWord(string word)
{
    string mask;
    int word_size = word.length();
    for (int i = 0; i < word_size ; i++)
    {
        mask = mask + "_"; 
    }

    return mask;
}

/**
    @param            :   The integer for the difficulty of the game
                          (0 for easy, 1 for normal, and 2 for hard) 
    @return           :   The number of tries given the `difficulty`
                          (9 for easy, 7 for normal, and 5 for hard)
    @post             :   Return the number of tries based on given
                          difficulty (0-easy: 9 tries, 1-normal: 7
                          tries, 2-Hard: 5 tries) 
*/
int getTries(int difficulty)
{
    int tries; 
    if (difficulty == 0)
    {
        tries = 9; 
    }
    else if (difficulty == 1)
    {
        tries = 7; 
    }
    else if (difficulty == 2)
    {
        tries = 5; 
    }
    
    return tries; 
}


/*
    @param tries      :   The integer for remaining tries 
    @param difficulty :   The integer for the difficulty of the game 
                          (0 for easy, 1 for normal, and 2 for hard) 
    @post             :   prints the number of lives left and number
                          of lives used using "O" and "X". DO NOT
                          PRINT AN ENDLINE

    For example : calling `printAttemps(2, 1)` would print "OOXXXXX". 
                  Based on given `difficulty`, we know the total tries
                  is 7 (from `getTries(1)`). Also, the player has 2
                  `tries` remaining based on the given parameter.
                  Therefore, the function prints two "O"s to indicate
                  the remaining tries and 5 "X"s to indicate the tries
                  that have been used (7-2=5)          
*/
void printAttempts(int tries, int difficulty)
{
    int level = getTries(difficulty);
    for(int i = 0; i < tries; i++)
    {
        cout << "O";
    }
    if (tries != level)
    {
        for (int n = tries; n < level; n++)
        {
            cout << "X"; 
        }
    }
}


/*
    @param word       :   The string word from the dictionary
    @param letter     :   The char letter that that will be revealed
    @param(&) current :   The string representing a masked word
    @return           :   `true` if the `letter` exists in `word`,
                          otherwise return `false`  
    @post             :   If the given `letter` exists in `word`
                          reveal the `letter` in `current` masked word
                          and return `true`. Otherwise, return `false`

    For example : Let's say we have the following main function:
                  int main(){
                      string w = "g___";
                      cout << revealLetter("good", 'o', "g___") << endl;
                      cout <<  w << endl;
                  }
                  The first `cout` will print 1 because the letter 'o'
                  exists in "good". Thus, the function returned `true`.
                  The second `cout` will print "goo_". The variable `w`
                  has been modified by the function to reveal all the
                  `o`s in "good" resulting in "goo_"           
*/
bool revealLetter(string word, char letter, string &current)
{
    int counter = 0;
    int word_size = word.length(); 
    for ( int i = 0; i < word_size; i++)
    {
        if(word[i] == letter)
        {
            counter += 1; 
        }
    }

    if (counter < word_size)
    {
        for (int n = 0; n < word_size; n++)
        {
            if(word[n] == letter)
            {
                current[n] = word[n]; 
            }
        }
        return true;
    }
    else
    {
        return false; 
    }
}

string getRandomWord() {
    srand((unsigned) time(NULL));
    int index = rand() % word_count;
    return words[index];
}

/**     
    @post   :       The game-loop for Hangman   
*/
void gameLoop() {
    int difficulty, tries;
    string word, current;
    char letter;
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout <<  "0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
        cin >> difficulty;
        while (difficulty < 0 || difficulty > 3) {
            cout <<  "Enough horseplay >_< !\n0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
            cin >> difficulty;
        }
        if (difficulty == 3) {
            cout << "If you're hangry, go grab a bite! See what I did there?" << endl;
            break;
        }
        word = getRandomWord();
        current = maskWord(word);
        tries = getTries(difficulty);
        while (tries != 0) {
            cout << "Life: ";
            printAttempts(tries, difficulty);
            cout << endl << "Word: "<< current << endl;
            cout << "Enter a letter: ";
            cin >> letter;
            
            if (!revealLetter(word, letter, current)) {
                tries--;
            }
            if (current == word) {
                break;
            }
            if (tries == 2) {
                cout << "The part of speech of the word is "<< getPOS(word) << endl;
            }
            if (tries == 1) {
                cout << "Definition of the word: " << getDefinition(word) << endl;
            }
        }
        if (tries == 0) {
            cout << "The word is \"" << word << "\". Better luck next time! You're getting the ..ahem.. hang of it." << endl;
        }
        else {
            cout << "Congrats!!!" << endl;
        }
    }
}






int main()  
{
    gameLoop(); 
}