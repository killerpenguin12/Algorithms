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

}

void write(vector<Point> p,int size)
{

ofstream output_file("p100_out.txt");

if(!output_file.is_open())
    throw runtime_error("File not found.");
//cout << "Do we get into write?" << endl;
//cout << "Here: " << p[1].x << endl;
//cout << "did it like that?" << endl;
for(int i = 0; i < 10; i++ )
    {
    //cout << p[i].x << endl;
    output_file << p[i].x << " , " << p[i].y ;
    
    }
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

int cross(Point& one,Point& two, Point& c)
{
//Get the line that Points can be above or below
   float x1 = two.x - one.x;
   float y1 = two.y - one.y;

   float x2 = two.x - c.x;
   float y2 = two.y - c.y;
   float xp = x1*y2 - y1*x2;
   if(xp > 0) return 1; //below, or to the right of the line from one to two.
   else if(xp < 0) return -1; //above, or to the left of the line.
   else return 0; //on the same line

return 0;
}
//Need to make a new resize function as this one does not work with point. SO thats a bummer.
void resizeVec(vector<Point> &p,int newCap)
{
 //I dont want to do this. SO i wont for now.
}

int main()
{
    int n = 100;
    //b = bucketSize;
    int b = 10;
    vector<Point>plist(n);
    read(plist);
    vector<Point>savedPoints(4); //contains all our best highest values of each bucket.
    vector<Point>finalShapecw(b*4); //dont want to resize this. not sure how big we should make it.
    vector<Point>finalShapeccw(b*4); // we will merge these at the end
    
    std::sort(plist.begin(),plist.end(),comparex);
    // next we seperate into buckets, which will change our resolution based on how big these buckets are
    
    finalShapecw[0].x = plist[0].x;
    finalShapecw[0].y = plist[0].y; // our highest x should be included in our shape
    finalShapeccw[0].x = plist[0].x;
    finalShapeccw[0].y = plist[0].y;
    //Point last = plist.back(); // saving our smallest x
    //cout << "Here it is: " << plist.back() << endl;
    int sizecw = 1;
    int capcw = b*4;
    
    int sizeccw = 1;
    int capccw = b*4;

    //cout << "Here is the size: " << sizeccw << " Here is the capacity: " << capccw << endl; 
    //int i = 0;
    vector<Point>bucket(b);
    for (int i;i < n;i++)
    {
        if(i%b > 0){
            bucket[(i%b)] = plist[i]; //filling up our bucket
            cout << (i%b) << endl;
        }
        else if(i %b == 0)
            {
            //bucket is full so we can compare
            std::sort(bucket.begin(),bucket.end(),comparey); //deciding what order the values go.
            //for(int i = 0; i < b; i++)
            //{
                //cout << "Bucket: " << bucket[i].x  << " , " << bucket[i].y << endl;
            //}
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
            if(capccw == sizeccw)
            {
                //cout << "Let me know if this triggers 1" << endl;
                resizeVec(finalShapeccw,finalShapeccw.capacity()*2); //this does not work. Throws an error. Maybe just use an array? 
                capccw = capccw*2;
            }
            else if(cross(finalShapeccw[sizeccw],savedPoints[0],savedPoints[1]) == -1) //topside going ccw
                { 
                finalShapeccw[sizeccw+1].x = savedPoints[0].x; //this would make 0 the correct one
                finalShapeccw[sizeccw+1].y = savedPoints[0].y;
                //cout << "does cross 1 trigger?" << endl;
                
                sizeccw += 1;
                }
            else
                {
                finalShapeccw[sizeccw+1].x = savedPoints[1].x; //1 would be outside the line.
                finalShapeccw[sizeccw+1].y = savedPoints[1].y;
                //cout << "does cross 2 trigger?" << endl;
                //cout << "x: " << savedPoints[0].x << " y: " << savedPoints[0].y << endl;
                sizeccw += 1;
                } 
            if(capcw == sizecw)
            {
                //cout << "Let me know if this triggers 2" << endl;
                resizeVec(finalShapecw,finalShapecw.capacity()*2);
                capcw = capcw*2;
            }
            else if(cross(finalShapecw[sizecw],savedPoints[3],savedPoints[2]) == 1) // then 2 would be inside
                {
                    finalShapecw[sizecw+1].x = savedPoints[3].x; 
                    finalShapecw[sizecw+1].y = savedPoints[3].y;
                    //cout << "does cross 3 trigger?" << endl;
                    sizecw += 1;
                }
            else 
                {
                    finalShapecw[sizecw+1].x = savedPoints[2].x; 
                    finalShapecw[sizecw+1].y = savedPoints[2].y;
                    //cout << "does cross 4 trigger?" << endl;
                    sizecw += 1;
                }
            } 
    }

    //Finally merge our two lists of important Points.
    //the two vectors have identical initial Points so we will delete one.
    //finalShapeccw.erase(finalShapeccw.begin()); //erasing duplicate
    //have to check if it can fit
    //cout << "Here is the size CCW: " << sizeccw << " Here is the capacity CCW: " << capccw << endl; 
    //cout << "Here is the size CW: " << sizecw << " Here is the capacity CW: " << capcw << endl;
    for(int i = 1; i < sizecw-1; i++) //dodge the first value, its a duplicate.
    {
        if(sizeccw == capccw)
        {
           // cout << "Let me know if this triggers 3" << endl;
            //finalShapeccw.resize(capccw*2); //double our capacity
            capccw = capccw*2;
        }
        else
        {
            //std::cout << "x: " << finalShapeccw[i].x << " y: " << finalShapeccw[i].y << "           \n";
            //cout << "Let me know if this triggers 4" << endl;
            finalShapeccw[sizeccw + i - 1].x = finalShapecw[i].x; 
            finalShapeccw[sizeccw + i - 1].y = finalShapecw[i].y;
            //cout << "Let me know if this triggers 5" << endl;
        }
    }
    //cout << "Do we make it here? " << endl;

    //finally write the results*/
    finalShapeccw[sizeccw-1].x  = plist[n].x;
    finalShapeccw[sizeccw-1].y  = plist[n].y;
    sizeccw += 1;
    //for (int i = 0; i < sizecw; i++)
    //    std::cout << "x: " << finalShapecw[i].x << " y: " << finalShapecw[i].y << "           \n";

    //cout << "What about here?" << endl;


    //finalShapeccw.push_back(last);
    write(finalShapeccw,sizeccw);

    

    /*cout << " Sorted list: \n";
    for (int i = 0; i < plist.size(); i++)
    std::cout << "x: " << plist[i].x << " y: " << plist[i].y << "           \n";
    std::cout << "\n";*/

    return 0;
}
