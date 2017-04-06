

#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

//string letters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
// 't','u','v','w','x','y','z'};

string letters = {"abcdefghijklmnopqrstuvwxyz"};

string morseCode[] = {"._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___",
    "_._", "._..", "__", "_.", "___", ".__.", "__._", "._.", "...", "_",
    ".._", "..._", ".__", "_.._", "_.__", "__.."};







class Message
{
public:
    
    void printmessage(void);
    Message(); // this is the constructor
    Message(string buffer);
    ~Message();
protected:
    string translatemsg;
};

class MorseCodeMessage:Message
{
public:
    MorseCodeMessage();
    ~MorseCodeMessage();
    void TranslateFunction();
    void printmessage(void);
protected:
    string *FinalTranslate;
    
};

class Messagestack
{
public:
    Messagestack();
    ~Messagestack();
    void printstack(void);
    void popstack();
    void pushstack(string *stackmessage);
    void askmessage();
protected:
    string *stackmessage;
    int counter;
    //stack <string> mystack;
    string *stack[10];//stack size is 10
};


Messagestack::Messagestack()
{
    stackmessage = new string;
    
    counter = 0;
    //nothing to allocate
}

Messagestack::~Messagestack()
{
    delete [] stackmessage;
    cout<< "destructing "<<endl;
    
    //nothing to delete
}

void Messagestack::askmessage()
{
    int choice;
    string input;
    cout<<"Would you like to push(1) a message, pop(2) a message, or print the stack(3)? Press(0) to exit"<<endl;
    cin >> choice;
    while(choice!=0)
    {
        if (choice == 1)
        {
            cout<<"Please give a message to push on to stack"<<endl;
            cin >> input;
            
            *stackmessage = input;
            
            //   cout<<"this is the address of input"<<&input<<endl;
            //   cout<<"this is the value of stackmessage"<<stackmessage<<endl;
            
            //  cout<<"this is input: "<< input<<endl;
            //  cout<<"This is stack message: "<<*stackmessage<<endl;
            
            pushstack(stackmessage);
            //cout << "This is the stack: "<<endl<< stack.top()<<endl;
        }
        
        if (choice == 2)
        {
            cout << "You chose to pop the message!"<< endl;
            popstack();
        }
        if(choice == 3)
            printstack();
        cout<<"Would you like to push(1) a message, pop(2) a message, or print the stack(3)? Press(0) to exit"<<endl;
        cin >> choice;
    }
    exit(EXIT_SUCCESS);
}

void Messagestack::popstack()
{
    if(counter == 0)
        cout<<"There is nothing to pop"<<endl;
    
    else{
        ;
        counter--;
    }
    
}

void Messagestack::pushstack(string *stackmessage)
{
    
    if(counter == 10)
        cout<<"Stack is full (maximum of 10 objects)"<<endl;
    
    else
    {
        
        cout<<"this is the message"<<*stackmessage<<endl;
        stack[counter] = new string;
        
        *stack[counter] = *stackmessage;//set index to message input by user
        
        
        counter++;
    }
    
}
void Messagestack::printstack(void)
{
    cout<<"...Printing stack..."<<endl;
    
    for (int i=0;i<counter; i++)
    {
        cout<<"this is the counter"<<counter<<endl;
        cout<<"Element "<<(i+1)<<":"<<endl;
        cout<< *stack[i] << endl;
        
    }
}
MorseCodeMessage::MorseCodeMessage()
{
    cout << "Please give a message to translate:" << endl;
    cin >> translatemsg;
    
    FinalTranslate = new string[translatemsg.length()];
    TranslateFunction();
}

MorseCodeMessage::~MorseCodeMessage()
{
    //nothing to make go bye bye, jk free finaltranslate
    delete [] FinalTranslate;
}


void MorseCodeMessage::printmessage(void)

{
    
    
    cout<<"This is the original message:"<<translatemsg<<endl;
    cout<<"This is the translated message: ";
    for(int i=0;i<translatemsg.length();i++)
    {
        cout<<""<<FinalTranslate[i]<<"  ";
    }
    cout<<endl<<endl;
    
    
    
    
    
    
    
    
    
}

void MorseCodeMessage::TranslateFunction()
{
    int i;
    int j;
    for(i=0;i<translatemsg.length();i++)
    {
        for(j=0;j<24;j++)
        {
            
            if (translatemsg[i] == letters[j])
            {
                FinalTranslate[i] = morseCode[j];
            }
            
        }
    }
    
}

Message::Message()
{
    /*moved the cout for original message from here to constructor of MorseCodeMessage, if  kept it here the message was being asked two different times, now it will only ask user for 1 word.*/
}

Message::~Message()
{
    // no variables that need memory allocation
}

Message::Message(string buffer)
{
    translatemsg = buffer;
}

void Message::printmessage(void)
{
    //cout<<"this is the original message:"<<translatemsg<<endl;
}

int main(int argc, const char * argv[]) {
    
    Message message1;
    MorseCodeMessage morse1;
    message1.printmessage();
    morse1.printmessage();
    Messagestack stack;
    stack.askmessage();
    
    
    return 0;
}
