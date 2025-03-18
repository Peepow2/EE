#include <bits/stdc++.h>
using namespace std;

// **************** Define Type of data ****************
class member_444
{
    public:
    string ID, Name;
    int Age;
    
    member_444(string _ID, string _Name = "Unknown", int _Age = -1)
    {
        ID = _ID; 
        Name = _Name;
        Age = _Age;
    }
};

bool By_Age(member_444 x, member_444 y) {
    return x.Age < y.Age;
}

// **************** Check Valid ID Name & Age ****************

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
map<string, pair<string, int>> getName_Age(map<string, string> ID_NAME, map<string, int> ID_Age)
{
    map<string, pair<string, int>> NAME_ID_Age;

    for(auto itr: ID_NAME)
    {
        string ID = itr.first; // get ID
        bool vaild_ID = check_vaild_ID(ID); // Check vaild_ID
        bool Repeat_ID = (NAME_ID_Age.find(ID) == NAME_ID_Age.end()); // Check repeat ID
        if (!vaild_ID && !Repeat_ID)
            continue;
        
        
        string Name = itr.second; // get Name
        bool vaild_Name = check_vaild_Name(Name); // Check Valid Name
        if(!vaild_Name) 
            Name = "Unknown";
        
        
        auto it = ID_Age.find(ID); // Find Age in ID_Age map
        int Age = -1;
        if(it != ID_Age.end())
        {
            Age = it->second;
            bool vaild_Age = check_vaild_Age(Age);
            if(!vaild_Age)
                Age = -1;
        }
        
        pair<string, int> NA = {Name, Age};
        NAME_ID_Age.insert({ID, NA});
    }
    
    for(auto itr: ID_Age)
    {
        string ID = itr.first;
        bool vaild_ID = check_vaild_ID(ID);
        bool Repeat_ID = (NAME_ID_Age.find(ID) != NAME_ID_Age.end());
        if (!vaild_ID && !Repeat_ID)
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
        pair<string, int> NA = {Name, Age};
        NAME_ID_Age.insert({ID, NA});
    }

    return NAME_ID_Age;
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
    
    map<string, pair<string, int>> map_ID_NAME_Age = getName_Age(map_ID_NAME, map_ID_Age);
    
    cout << "map_ID_NAME_Age\n";
    for(auto x: map_ID_NAME_Age)
        cout << x.first << " " << x.second.first << " " << x.second.second << endl;
        
    vector <member_444> V;
    for(auto x: map_ID_NAME_Age)
        V.push_back(member_444(x.first, x.second.first, x.second.second));
        
    sort(V.begin(), V.end(), By_Age);
    
    cout << "\nVector_ID_NAME_Age\n";
    for(auto itr: V)
        cout << itr.ID << " -> Name = " << itr.Name << ", Age = " << itr.Age << endl;
    
}
