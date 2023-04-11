#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateStrings(string& word, int index, int size, int numberSpaces, int floatingSize, std::map<char,int>& floatingMap, std::set<std::string>& stringSet, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    //Declare useful data structures and variables

    //Declare results set
    std::set<std::string> results;

    //create floating map
    std::map<char,int> floatingMap;

    //populate map
    for(unsigned int i = 0; i < floating.size(); i++){
        floatingMap[floating[i]]++;
    }

    //get size
    int size = in.length();

    //floatingSize
    int floatingSize = floating.length();

    //word
    std::string word = in;

    int numberSpaces = 0;

    //numberSpaces
    for(int i = 0; i < size; i++){
        if(word[i] == '-'){
            numberSpaces++;
        }
    }

    // //set word
    // for(int i = 0; i < in.length()-1; i++)
    // {
    //     if(in[i] != '_'){
    //         //fixed letter
    //         word += in[i];
    //     }
    //     else{
    //         //blank space
    //         word += '_';
    //     }
    // }

    //generate substrings
    generateStrings(word, 0, size, numberSpaces, floatingSize, floatingMap, results, dict);

        //check if substrings are valid
        //if at least 1 of each floating letters are present

    //check if substrings are in dictionary
        //if valid --> keep in results set

    return results;

}

// Define any helper functions here

//generateString
void generateStrings(string& word, int index, int size, int numberSpaces, int floatingSize, std::map<char,int>& floatingMap, std::set<std::string>& stringSet, const std::set<std::string>& dict){
    //BC
    if(numberSpaces < floatingSize)
        return;
    if(index >= size){
        if(dict.find(word) != dict.end()){
            stringSet.insert(word);
        }
        return;
    }
    //check empty
    else if(word[index] != '-'){
        // word[index] = fixed[index];
        //recurse and increment index (don't change value)
        generateStrings(word, index+1, size, numberSpaces, floatingSize, floatingMap, stringSet, dict);
    }
    else{
        //if empty

        //1. try floating first
        auto copy = floatingMap;
        for(auto p: floatingMap){
            char curr = p.first;
            if(p.second <= 0){
                continue;
            }
            
            word[index] = curr;
            copy[curr]--;
            //recurses down this substring
            
            generateStrings(word, index+1, size, numberSpaces-1, floatingSize-1, copy, stringSet, dict);
            //backtracks
            word[index] = '-';
            copy[curr]++;
            copy = floatingMap;
        }

        if(numberSpaces > floatingSize){
             //2. check rest of alphabet
            for(char i = 'a'; i <= 'z'; i++){
                if(floatingMap.find(i) != floatingMap.end() && floatingMap[i] > 0)
                    continue;
                word[index] = i;
                //recurses down this substring
                generateStrings(word, index+1, size, numberSpaces-1, floatingSize, floatingMap, stringSet, dict);
                //backtracks
                word[index] = '-';
               
            }
        }

        // word[index = 'a'];
        // return generateStrings(word, index++, size, stringSet, dict);
        // //end of alphabet
        // else if(word[index] == 'z'){
        //     return generateStrings(word, index++, size, stringSet, dict);
        // }
        // //next letter
        // else {
        //     word[index] = word[index]++;
        //     return generateStrings(word, index++, size, stringSet, dict);
        // }
        
    }
    return;

}