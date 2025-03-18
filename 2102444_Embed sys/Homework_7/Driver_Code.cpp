#include <bits/stdc++.h>
using namespace std;

//**************** Check Valid ID Name & Age ****************

// Check Valid ID
bool check_vaild_ID(string ID) 
{
    if(ID.length() != 13) // ID lenth must be 13
        return false;
    
    for(int i=0;i<13;i++)
    {
        if(!(ID[i] >= '0' &&  ID[i] <= '9')) // Number must be between 0 and 9;
            return false;
    }
    return true;
}

// Check Valid Name
bool check_vaild_Name(string NAME)
{
    int len = NAME.length();
    for(int i=0;i<len;i++)
    {
        char c = tolower(NAME[i]);  // set it to lower
        if(!(c >= 'a' && c <= 'z')) // Is it a letter? 
            return false;
    }
    return true;
}

// Check Valid Age
bool check_vaild_Age(int Age)
{
    return (Age >= 0 && Age <= 150); // 0 <= Age < = 150
}

//  **************** end Check Valid ID Name & Age ****************


//  **************** Combine 2 map ****************
map<string, int> getName_Age(map<string, string> ID_NAME, map<string, int> ID_Age)
{
    map<string, int> NAME_Age;

    for(auto itr: ID_NAME)
    {
        string ID = itr.first;
        bool vaild_ID = check_vaild_ID(ID);
        if (!vaild_ID)
            continue;
        
        
        string Name = itr.second;
        bool vaild_Name = check_vaild_Name(Name);
        if(!vaild_Name)
            Name = "Unknown";
        
        
        auto it = ID_Age.find(ID);
        int Age = -1;
        if(it != ID_Age.end())
        {
            Age = it->second;
            bool vaild_Age = check_vaild_Age(Age);
            if(!vaild_Age)
                Age = -1;
        }
        
        NAME_Age.insert({Name, Age});
    }
    
    for(auto itr: ID_Age)
    {
        string ID = itr.first;
        bool vaild_ID = check_vaild_ID(ID);
        if (!vaild_ID)
            continue;
        
        
        int Age = itr.second;
        bool vaild_Age = check_vaild_Age(Age);
        if (!vaild_Age)
            Age = -1;      
        
        
        auto it = ID_NAME.find(ID);
        string Name = "Unknown";
        if (it != ID_NAME.end())
        {
            Name = it->second;
            bool vaild_Name = check_vaild_Name(Name);
            if (!vaild_Name)
                Name = "Unknown";
        }
        
        NAME_Age.insert({Name, Age});
    }

    return NAME_Age;
}
//  **************** End of Combine 2 map ****************

int main()
{
    map<string, string> map_ID_NAME =
    {
        {"1234567890123", "Alice"},  // Only in map1
        {"2345678901234", "Bob"},
        {"3456789012345", "Charlie"},
        {"4567890123456", "David"},
        {"5678901234567", "Eve"}
    };

    map<string, int> map_ID_Age =
    {
        {"2345678901234", 45},  // Bob
        {"3456789012345", 78},  // Charlie
        {"4567890123456", 3},  // David
        {"5678901234567", 89},  // Eve
        {"6789012345678", 23}   // only in map2
    };
    
    map<string, int> map_NAME_Age = getName_Age(map_ID_NAME, map_ID_Age);
    
    for(auto x: map_NAME_Age)
        cout << x.first << " " << x.second << endl;
}
