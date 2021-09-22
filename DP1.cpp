#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define NUM_POINTS = 100
using namespace std;

struct point{
    int x,y;
    //struct point *next, *prev;
};//plist[100];

void read(vector<point> &plist)
{
//reading in the file for our points

ifstream input_file("p100.txt");
if(!input_file.is_open())
    throw runtime_error("File not found.");
float a, c;
char b;
int i = 0;
while ((input_file >> a >> b >> c) && (b == ','))
{

    //cout << "a: " << a << " c: " << c << "\n";
    plist[i].x = a*100;
    plist[i].y = c*100;
    //cout << "x: " << plist[i].x << " y: " << plist[i].y << "\n";
    i++;
    //plist->*next = plist[i+1]
}

/*vector<string> data;
cout << "1st" << "\n";
int i = 0;
cout << "2nd\n";
string line;
        while(getline(input_file,line))
        {
            //cout << "Here?\n";
            data.push_back(line);
            //cout << data[i] << "\n";
            cout << i/100 << "\n";
            i++;
        }
        
//input_file.close();
    
//if() cout << "Unable to open file";
cout << (data[10]) << "\n";
cout << (data[1]) << "\n";*/
}

void write()
{
//writing back to our file the points we want
}

int comparex(point one, point two)
{
//comparison function for sort
    //cout << "IS this getting called? \n";
    if(one.x > two.x) return 1;
    else if (two.x > one.x) return 0;
    return 0;
}

int comparey(point one, point two)
{
//comparison function for sort
    //cout << "IS this getting called? \n";
    if(one.y > two.y) return 1;
    else if (two.y > one.y) return 0;
    return 0;
}

void algorithm()
{
//Here our algorithm runs to calc what points we need
}

int getLine(point x,point y,point c)
{
//Get the line that points can be above or below

return 0;
}

void removal(vector<point> &plist)
{
 // Here is where we are supposed to remove all points inbetween the original vertex and the point 
 //with the same x and greatest y coordinate. Not sure how to do that yet.
}

int main()
{
    vector<point>plist(100);
    read(plist);
    

    /*for (int i = 0; i < plist.size(); i++)
    std::cout << "x: " << plist[i].x << " y: " << plist[i].y << "           \n";
    std::cout << "\n";*/
    
    std::sort(plist.begin(),plist.end(),comparex);

    std::sort(plist.begin(),plist.end(),comparey);
    if(plist[0].x == plist[1].x) removal(plist);
    point vertex = plist[0];

    /*cout << " Sorted list: \n";
    for (int i = 0; i < plist.size(); i++)
    std::cout << "x: " << plist[i].x << " y: " << plist[i].y << "           \n";
    std::cout << "\n";*/

    return 0;
}