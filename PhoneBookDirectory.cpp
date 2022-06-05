#include <bits/stdc++.h>
#include <string>
using namespace std;
map<string, long long int> contacts; // A map to store the key value pair of the contacts with the name

struct trie
{ // Defining a structure for the trie nodes
    struct trie *ch[26];
    bool islast;
};
// This is used to define a root for trie here we define the 26 letter nodes as NULL and islast for all of them as false
struct trie *getnode(void)
{
    struct trie *p = new trie;
    for (int i = 0; i < 26; i++)
        p->ch[i] = NULL;
    p->islast = false;
}
struct trie *root = getnode(); // Defining the root node
void insert(string key)
{ // Function for insertion in a trie
    struct trie *temp = root;
    for (int i = 0; i < key.length(); i++)
    {
        // Ascii value of the individual letters are subtracted from 'a' so as to find the index value for trie
        int id = key[i] - 'a';
        // If the node is empty at that index meaning no word with that certain letter has been entered
        if (temp->ch[id] == NULL)
            temp->ch[id] = getnode();
        temp = temp->ch[id];
    }
    // When the word gets finished we change the value of islast to true meaning the word has ended
    temp->islast = true;
}
// It is function to find all the suggestion with given prefix. It is a recursive function
void sug(struct trie *word, string prefix)
{
    /* The base case for this recursive function is to check whether the islast of that node is true or not if it is
    true then it prints contact from the given map contact corresponding to that prefix */
    if (word->islast == true)
        cout << prefix << " " << contacts[prefix] << "\n";
    /* Here we traverse further on the word node, we find all the suggestions for "word" or "prefix" by
    checking whether there are any children node for word node */
    for (int i = 'a'; i <= 'z'; i++)
    {
        // We check for all 26 letters of the alphabet by using the above for loop this will form a recursion tree
        struct trie *next = word->ch[i - 'a'];
        if (next != NULL)
            // Here prefix is updated if a string is with that prefix is found and the new prefix is passed in the  recursion
            sug(next, prefix + (char)i);
    }
}
void displaycontacts(string str)
{
    // A string is used to caompare with the strings entered in the directory
    string prefix = "";
    int i;
    struct trie *prev = root;
    for (i = 0; i < str.length(); i++)
    {
        prefix += str[i];
        // Ascii value of the individual letters are subtracted from 'a' so as to find the index value for trie
        int id = prefix[i] - 'a';
        // Here it is checked whether the character at the above calculated index is present. If it is not present then return "Not Found"
        struct trie *current = prev->ch[id];
        if (current == NULL)
        {
            i++;
            cout << "Not found ";
            break;
        }
        // If we have traversed the whole string then we check the suggestion by passing the prefix to sug function
        if (i == str.length() - 1)
        {
            cout << "suggestions of " << prefix << " are\n";
            sug(current, prefix);
        }
        prev = current;
    }
    for (; i < str.length(); i++)
    {
        prefix += (char)str[i];
        cout << "No Results Found for " << prefix << "\n";
    }
}
int main()
{
    while (1)
    {
        // Entering the general details of for the directory
        string name, choice;
        long long int phno;
        cout << "Enter the contact's Name - ";
        cin >> name;
        cout << "\nEnter the phone number of the contact - ";
        cin >> phno;
        insert(name);
        // Entering details in the map
        contacts[name] = phno;
        // Ask the user whether he/she wants to add more contacts or not
        cout << "\nDo You Want To Add More Contacts\n";
        cin >> choice;
        if (choice == "no")
            break;
    }
    // Enter the string that needs to be searched
    string choice;
    choice = "yes";
    while (choice == "yes")
    {
        string search;
        cout << "\nName or Prefix of the contact's name you want to search - ";
        cin >> search;
        displaycontacts(search);
        cout << "\nDo You Want To search more alternatives?\n";
        cin >> choice;
        if (choice == "no")
            break;
    }
}