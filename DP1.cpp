#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define NUM_POINTS = 100
using namespace std;

struct Point{
    int x{0};
    int y{0};
    //struct point *next, *prev;
};//plist[100];

void read(vector<Point> &plist)
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

void write(vector<Point> p)
{
ofstream output_file("p100_out.txt");
if(!output_file.is_open())
    throw runtime_error("File not found.");
for(int i = 0; i < p.size(); i++ )
    output_file << p[i].x << " , " << p[i].y ;
//writing back to our file the points we want
}

int comparex(Point one, Point two)
{
//comparison function for sort
    //cout << "IS this getting called? \n";
    if(one.x > two.x) return 1;
    else if (two.x > one.x) return 0;
    return 0;
}

int comparexLow(Point one, Point two)
{
//comparison function for sort
    //cout << "IS this getting called? \n";
    if(one.x > two.x) return 0;
    else if (two.x > one.x) return 1;
    return 1;
}

int comparey(Point one, Point two)
{
//comparison function for sort
    //cout << "IS this getting called? \n";
    if(one.y > two.y) return 1;
    else if (two.y > one.y) return 0;
    return 0;
}

void algorithm()
{
//Here our algorithm runs to calc what Points we need
}

int getLine(Point one,Point two,Point c)
{
//Get the line that Points can be above or below
// y = mx + b for original line.
   // float m = two.y - one.y/(two.x - one.x); //getting our m
    //get our b:
   // b = one.y - m * one.x;
   Point v1.x = 1;

   Point v2 {0,0};
   Point v1.x = two.x - one.x;
   Point v1.y = two.y - one.y;

   Point v2.x = two.x - c.x;
   Point v2.y = two.y - c.y;
   float xp = v1.x*v2.y - v1.y*v2.x;
   if(xp > 0) return 1; //below, or to the right of the line from one to two.
   else if(xp < 0) return -1; //above, or to the left of the line.
   else return 0; //on the same line

return 0;
}

void removal(vector<Point> &plist)
{
 // Here is where we are supposed to remove all Points inbetween the original vertex and the Point 
 //with the same x and greatest y coordinate. Not sure how to do that yet.
}

int main()
{
    n = 100;
    //b = bucketSize;
    b = 10;
    vector<Point>plist(n);
    read(plist);
    vector<Point>savedPoints(4); //contains all our best highest values of each bucket.
    vector<Point>finalShapecw(2*b); //dont want to resize this. not sure how big we should make it.
    vector<Point>finalShapeccw(2*b); // we will merge these at the end

    /*for (int i = 0; i < plist.size(); i++)
    std::cout << "x: " << plist[i].x << " y: " << plist[i].y << "           \n";
    std::cout << "\n";*/
    
    std::sort(plist.begin(),plist.end(),comparex);
    // next we seperate into buckets, which will change our resolution based on how big these buckets are
    int i = 0;
    finalShapecw[0].x = plist[0].x;
    finalShapecw[0].y = plist[0].y; // our highest x should be included in our shape
    finalShapecww[0].x = plist[0].x;
    finalShapecww[0].y = plist[0].y;
    vector<Point>bucket(b);
    for (i;i < n;i++)
    {
        if(i%b > 0)
            bucket[i%b] = plist[i]; //filling up our bucket
        else if(i %b == 0)
            {
            //bucket is full so we can compare
            std::sort(bucket.begin(),bucket.end,comparey) //deciding what order the values go.
            savedPoints[0].x = bucket[0].x; //smallest and largets Points from our bucket.
            savedPoints[0].y = bucket[0].y;
            savedPoints[1].x = bucket[1].x; //taking top and bottom two to make sure we are not missing any.
            savedPoints[1].y = bucket[1].y;
            savedPoints[3].x = bucket[b-1].x; 
            savedPoints[3].y = bucket[b-1].y;
            savedPoints[2].x = bucket[b-2].x; 
            savedPoints[2].y = bucket[b-2].y;
            // now we need to see if the Points should be included in the shape.
            //  We will use our getline function to see which ones will be best. 
            //going on top ccw and bottom cw. so if it is within on the top it is -1.
            //going on bottom cw so if it is within the line it is 1.
            if(getline(finalShapeccw[i],savedPoints[0],savedPoints[1]) == -1) //topside going ccw
                { 
                finalShapeccw[i+1].x = savedPoints[0].x; //this would make 0 the correct one
                finalShapeccw[i+1].y = savedPoints[0].y;
                }
            else
                {
                finalShapeccw[i+1].x = savedPoints[1].x; //1 would be outside the line.
                finalShapeccw[i+1].y = savedPoints[1].y;
                } 
            if(getline(finalShapecw[i],savedPoints[3],savedPoints[2]) == 1) // then 2 would be inside
                {
                    finalShapecw[i+1].x = savedPoints[3].x; 
                    finalShapecw[i+1].y = savedPoints[3].y;
                }
            else 
                {
                    finalShapecw[i+1].x = savedPoints[2].x; 
                    finalShapecw[i+1].y = savedPoints[2].y;
                }
            } 
    }

    //Finally merge our two lists of important Points.
    //the two vectors have identical initial Points so we will delete one.
    finalShapeccw.erase(finalShapeccw.begin()); //erasing duplicate
    //have to check if it can fit
    while(finalShapecw.size() + finalShapeccw.size() > finalShapecw.capacity()) 
        finalShapecw.resize(finalShapecw.capacity()*2);
    a.insert(finalShapecw.end(), finalShapeccw.begin(), finalShapeccw.end());
    //finally write the results
    write(finalShapecw);

    //std::sort(plist.begin(),plist.end(),comparey);
    //if(plist[0].x == plist[1].x) removal(plist);
    //Point vertex = plist[0];

    /*cout << " Sorted list: \n";
    for (int i = 0; i < plist.size(); i++)
    std::cout << "x: " << plist[i].x << " y: " << plist[i].y << "           \n";
    std::cout << "\n";*/

    return 0;
}
