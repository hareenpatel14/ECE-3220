//  Lab7
//  Created by Hareen Patel on 10/26/16.


#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

int counter =0,buffer=0;
int file_flag = 0;

class Signal
{
private:
    vector <char> fbuffer;
    vector <char> fileString;// creating vectors for file buffer and data holder
    int len;
    int max;
    int avg;
    vector<double> data;

    void findavg()
    {
        int i;
        for (i= 1; i<=len; i++)
        {
            avg = avg + data[i];
        }
        if(len != 0)
        {
        avg = avg/len;
        }
        
        
    }
    void findmax()
    {
        int i;
        if(counter == buffer)
        {
            max = 0;
        }
        for (i=1;i<=len;i++)
        {
            if(data[i]>max)
            {
                
                max = data[i];
            }
        }
        buffer++;
        counter++;
    }
    
public:
    void Scale( double scale );
    void Offset( double offset );
    void Stat(void);
    void Center( double mean );
    void Normalize( double max );
    void Sig_Info(void);
    void Save_File( const char* Filename );
    void Operations( Signal );
    void operator+(int);
    void operator-(int);
    void operator*(float);
    void operator/(float);
    Signal (void);
    Signal ( int num );
    Signal ( const char* Filename );
    ~Signal(void);
    
};

Signal::Signal ( int num )
{
    int i=1,j=1;
    fbuffer.resize(15);
    cout<<"this is the number involved!!"<<num<<endl;
    sprintf(&fbuffer[j], "A%d.txt", num);
    FILE *fptr = fopen(&fbuffer[j], "r");
    
    fscanf( fptr , "%d %d" , &len , &max);
    
    while(i <= len)
    {
        int temp;
        fscanf(fptr,"%d\n",&temp);
        data[i] = temp;
        i++;
    }
    findavg();
    
    
    fclose(fptr);
   
    //Fills out Signal with data from number files
}
//default constructor
Signal::Signal ()
{
    int k=1,j=1;
    fbuffer.resize(15);
    if (file_flag != 1)
    {
        sprintf(&fbuffer[j], "A1.txt");
        FILE *fptr = fopen(&fbuffer[j], "r");
        
     
        avg = 0;
        
        
        data.resize(15);
        while(k <= len)
        {
            int temp=0; // putting zeros in spaces for the default vector
            data[k] = temp;
            k++;
        }
        findavg();
        
        fclose(fptr);
    }
    len = 0;
    max = 0;
    avg = 0;
    // Fills out Signal with default data
}
//parametric constructor
Signal::Signal ( const char* Filename)
{
    int j=1,k=1;
    
   fbuffer.resize(15);
    sprintf(&fbuffer[j],"A%s.txt",Filename);
    FILE *fp = fopen(&fbuffer[j], "r");
    
    cout<<"this is filenume!:   "<<fbuffer[j]<<endl;
     ;
    if(fp==NULL)
    {
        cout<<"File is null"<<endl;
    }
     
    fscanf(fp,"%d %d",&len ,&max);
    
    data.resize(len);
     
    while(k <= len)
    {
        int temp;
        fscanf(fp,"%d\n",&temp);
        data[k] = temp;
        k++;
        
    }
    findavg();
    
    fclose(fp);
    delete[] Filename;
    //Fills out Signal with data from user inputted file
}
//destructor, causing seg faults for some reason
Signal::~Signal()
{
    //delete[] data;
}


void Signal::Stat( )
{
    findavg();
    findmax();
    //Finds Average and Max of data
}
//calling different operators for different functions
void Signal::operator+(int add)
{
    int i;
    for(i=1;i<=len;i++)
    {
        data[i] = data[i] + add;
    }
}
void Signal::operator-(int sub)
{
    int i;
    for(i=1;i<=len;i++)
    {
        data[i] = data[i] - sub;
    }
}
void Signal::operator*(float times)
{
    int i;
    for(i=1;i<=len;i++)
    {
        data[i] = data[i] * times;
    }
}
void Signal::operator/(float divide)
{
    int i;
    for(i=1;i<=len;i++)
    {
        data[i] = data[i] / divide;
    }
}



void Signal::Sig_Info( )
{
    cout << "Length: " << Signal::len << endl;
    cout << "Max: " << Signal::max << endl;
    cout << "Average: " << Signal::avg << endl;
    // prints some info from the signal
}

void Signal::Save_File( const char* Filename)
{
    int i = 1,j=1;
    fileString.resize(10);
    sprintf(&fileString[j],"A%s.txt",Filename);
    FILE *fp = fopen(&fileString[j], "w");
    
    fscanf( fp , "%d %d\n" , &len , &max);
    
    while(i <= len)
    {
        fprintf(fp,"%.2lf\n\n",data[i]);
        i++;
    }
    
    fclose(fp);
    //Saves the updated file under a new name
}
//this function handles the user's menu choice and performs correct operation
void Signal::Operations( Signal Sig )
{
    int choice =0;
    double Scale_factor , Offset_factor;
    char new_name[50];
    while( choice != 8 )
    {
        //ask user for operation choice
        cout<<"Select an Option: \n1. Scale \n2. Offset \n3. Statistics \n4. Center \n5. Normalize \n6. Info \n7. Save \n8. Exit \nPlease Choose Operation:  "<<endl;
        cin>>choice;
        
        if( choice < 1 || choice > 8)
        {
            //error check
            cout<<"Invalid choice, please try again. "<<endl;
        }
        // scale, write to file
        if( choice == 1 )
        {
            cout<<"Enter a scaling factor: "<<endl;
            cin>>Scale_factor;
            
            cout<<"Scaling"<<endl;
            Sig.operator*(Scale_factor);
            Sig.Stat();
            
        }
        //offset, write to file
        if( choice == 2 )
        {
            cout<<"Enter a number to offset data by: "<<endl;
            cin>>Offset_factor;
            
            cout<<"Offsetting"<<endl;
            Sig.operator+(Offset_factor);
            Sig.Stat();
        }
        //find mean and max, print to file
        if( choice == 3 )
        {
            cout<<"Printing Stats"<<endl;
            Sig.Stat();
        }
        //center array, print to file
        if( choice == 4)
        {
            cout<<"Centering"<<endl;
            Sig.operator-( Sig.avg );
            Sig.Stat();
        }
        // normalize, print to file
        if( choice == 5)
        {
            cout<<"Normalizing"<<endl;
            cout<<"this is max:: "<< Sig.max<<endl;
            Sig.operator/( Sig.max );
            Sig.Stat();
        }
        //print info
        if( choice == 6)
        {
            cout<<"Printing Info"<<endl;
            Sig.Sig_Info();
        }
        //save file
        if( choice == 7)
        {
            cout<<"Enter new file name:"<<endl;
            cin>>new_name;
            cout<<"Saving"<<endl;
            
            Sig.Save_File(new_name);
        }
        //exit the program
        if( choice == 8)
        {
            cout <<"Exiting"<< endl;
        }
        
    }
}

int main(int argc , char **argv)
{
    int num = 0;
    int def_flag = 0;
    
    int num_flag = 0;
    int i =1;
    int name = 0;
    char *Filename = new char[100];
    
    //handles command line
    if( argc > 1 )
    {
        
        if (strcmp(argv[i], "-n") == 0)
        {	// command line input file number
            if (argc - i <= 1 || atoi(argv[i + 1]) == 0)
            {	// checks number after -n
                printf("\n%s needs a modifier after it\n", argv[i]);
                i++;
                
                return 0;
            }
            if ( atoi(argv[i + 1]) > 15 || atoi(argv[i + 1]) < 1)
            {
                printf("Please run the program again with file range between values 1 and 15.\n");
                return 0;
            }
            
            num = atoi(argv[i + 1]);
            num_flag = 1;
            Signal signal;
            signal.Operations(num);
            //bump counter by 2 to get to next space
            i = i + 2;
        }
        
        if (strcmp(argv[i], "-f") == 0)
        {	// command line input file number
            if (argc - i <= 1 || atoi(argv[i + 1]) == 0)
            {	// checks number after -n
                printf("\n%s needs a modifier after it\n", argv[i]);
                i++;
                
                return 0;
            }
            if ( atoi(argv[i + 1]) > 15 || atoi(argv[i + 1]) < 1)
            {
                printf("Please run the program again with file range between values 1 and 15.\n");
                return 0;
            }
            
            Filename = argv[i + 1];
            file_flag = 1;
            Signal signal1;
            signal1.Operations(Filename);
            //bump counter by 2 to get to next space
            i = i + 2;
        }
        
        i++;
    }
    
    //if there are no command line arguments, do this
    if(num == 0 && file_flag == 0)
    {
        cout<<"Please enter a filename or choose default: \n1. Enter Filename \n2. Default "<<endl;
        cin>>name;
        if( name == 1)
        {
            cout<<"Enter name of file: "<<endl;
            cin>>Filename;
            file_flag = 1;
        }
        else if( name == 2)
        {
            def_flag = 1;
        }
        //Gets filename or uses default
    }
    
    
    if( def_flag == 1 )
    {
        Signal Sig;
        Sig.Operations(Sig);
        // makes default signal
    }
    else if( num_flag == 1 )
    {
        Signal Sig ( num );
        Sig.Operations(Sig);
        //makes num file signal
    }
    else if( file_flag == 1 )
    {
        cout<<"this is the name  involved!! :    "<<Filename<<endl;
        Signal Sig ( Filename );
        Sig.Operations(Sig);
        //makes user file signal
    }
    
    return 0;
}

