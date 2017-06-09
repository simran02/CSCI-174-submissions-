//
//  main.cpp
//  beautifulStrings_skarora
//
//  Created by Simran Kaur Arora on 8/24/16.
//  Copyright © 2016 Simran Kaur Arora. All rights reserved.
//

#include <iostream>
#include <string>
//#include <ctype>
#include <fstream>



using namespace std;
string str;
int counter[100];
int letter(string);
//int array(string);

int main()
{
    ifstream myfile;
    myfile.open("beautifulStrings.txt");
    
    // read string and convert string into lower case
    while(!myfile.eof())
    {
        //cout<<"entered while"<<endl;
        getline(myfile,str);
            for(int i=0;i<=str.length();i++)
                {
                    str[i]=tolower(str[i]);
                }
            cout<<"the string in lower case is "<<str<<endl;
            letter(str);
    }
    cout<<"calling array function now"<<endl;
    array(
return 0;
}


//finding the frequency of distingush characters in the string
int letter(string str)
{
    int i;
    cout<<"entering letter"<<endl;
    int count=0;
    char ch = '\0';
    
    for( i=0;i<=str.length()-1;i++)
    {
        ch = str[i];
        cout<<"ch -"<<ch<<endl;
            for(int j=0;j<=str.length()-1;j++)
                {
                    if(ch == str[j])
                        {
                            cout<<"entering if"<<endl;
                            //cout<<ch<<"="<<str[i];
                            count++;
                        }
                    cout<<"ch = "<<ch<<"  count"<<count<<endl;
                }
        counter[i]=count;
        count = 0;
    }
    for(int x=0;x<=str.length()-1;x++)
    {
        cout<<counter[x];
    }
    return 0;
}

//removing redundant elements from the array
int array(int counter[])
{
    int strz[100],arr[100];
    int num,count_num;
    for(int x=0;x<=str.length()-1;x++)
    {
        num = str[x];
        strz[x]=num;
        for(int y=0;y<=str.length()-1;y++)
        {
            if(num ==str[y])
            {
                if(num==strz[y])
                    break;
                else
                    strz[y]= num;
            }
            else
            {
                count_num++;
                arr[y]=count_num++;
            }
        }
          }
    for(int x=0;x<=str.length()-1;x++)
    {
        cout<<"unsorted array = "<<arr[x]<<endl;
    }

    return 0;
}

