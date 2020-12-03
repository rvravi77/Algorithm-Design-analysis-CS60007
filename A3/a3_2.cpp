/*
--------------------------------------------------------------
ADA Coding Assignment 3

Group - 11
Members name and Roll number

Pratibha Singh      20CS60R12
Vaibhav Saxena      20CS60R57
Ravi Pratap Singh   20CS60R60
Sahil Jain          20CS60R64
--------------------------------------------------------------

------------------------------------------------------------------------------------
Problem Description:   Construct Convex Hull using divide and conquer
------------------------------------------------------------------------------------

--------------------------------------------------------------
Compilation Instruction:

To complie :    g++ <source_filename> -o <Any name>
            eg: g++ a3_2.cpp -o q_a

To Run :        ./<Any name> <input_file name>
            eg: ./q_b points.txt
---------------------------------------------------------------

*/

//header files

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include<sstream>
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

pair<int, int> mid;     //to store the centre of the polygon 
ofstream out("hull_3.svg");

int quad(pair<int, int> p)          //to determine quadrant of a point
{
    if (p.first >= 0 && p.second >= 0)
        return 1;

    if (p.first <= 0 && p.second >= 0)
        return 2;

    if (p.first <= 0 && p.second <= 0)
        return 3;

    return 4;
}

// Checks whether the line is crossing the polygon
int orientation(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    int res = (b.second-a.second)*(c.first-b.first) - (c.second-b.second)*(b.first-a.first);

    if (res == 0)
        return 0;

    if (res > 0)
        return 1;

    return -1; 
}

// compare function for sorting
bool compare(pair<int, int> p1, pair<int, int> q1)
{
    pair<int, int> p = make_pair(p1.first - mid.first, p1.second - mid.second);

    pair<int, int> q = make_pair(q1.first - mid.first, q1.second - mid.second);

    int one = quad(p);
    int two = quad(q);

    if (one != two)
        return (one < two);

    return (p.second*q.first < q.second*p.first);
}


void draw_svg(vector<pair<int, int>> a , int lr)
{
    int s=a.size();
   char *color;
   if(lr==0){
       strcpy(color,"red");
   }
   if(lr==1)
   {
       strcpy(color,"blue");
   }
   if(lr==2)
   {
       return;
   }
   if(s<2)
    return;
   if(s ==2)
        {   sort(a.begin(), a.end());
           std :: string str1;
            std :: string str2;
            std :: string str3;
            std :: string str4;

              str1 = to_string(a[0].first);
              str2 = to_string(a[0].second);
              str3 = to_string(a[1].first);
              str4 = to_string(a[1].second);
              out<<"<circle cx=\""<<str1<<"\" cy=\""<<str2<<"\" r=\"3\" fill=\"black\" />\n";
              out<<"<circle cx=\""<<str3<<"\" cy=\""<<str4<<"\" r=\"3\" fill=\"black\" />\n";
              out<<"<line id=\"line\" x1=\""<<str1<<"\" "<<"y1=\""<<str2<<"\" "<<"x2=\""<<str3<<"\" "<<"y2=\"" <<str4<<"\" stroke-width=\"1\" stroke=\""<<color<<"\"/>";
              //cout<<"line"<<str1<<","<<str2<<","<<str3<<","<<str4<<"\n";
              //
            return;
        }
   if(s>2)
        {
            //sort(a.begin(), a.end());
            std :: string str;
            std :: string str2;

            std :: string str4;

            for (int i=0; i<a.size()-1; i++)
             {

              str2 = to_string(a[i].first);

              str4 = to_string(a[i].second);
              out<<"<circle cx=\""<<str2<<"\" cy=\""<<str4<<"\" r=\"3\" fill=\"black\"/>\n";
              str.append(str2);
              str.append(",");
              str.append(str4);
              str.append(",");

              str2.clear();

              str4.clear();
             }
             out<<"<circle cx=\""<<a[a.size()-1].first<<"\" cy=\""<<a[a.size()-1].second<<"\" r=\"3\" fill=\"black\"/>\n";
             str2 = to_string(a[a.size()-1].first);

              str4 = to_string(a[a.size()-1].second);

              str.append(str2);
              str.append(",");
              str.append(str4);
             //cout<<"polygon"<<str<<"\n";
             if(lr==0)
             {
             out<<"<polygon points=\""<<str<<"\" style=\"fill:black;fill-opacity:0.0;stroke:red;stroke-width:1\"/>";
            }
            else{
              out<<"<polygon points=\""<<str<<"\" style=\"fill:black;fill-opacity:0.0;stroke:blue;stroke-width:1\"/>";
            }
             //out<<"<polygon points=\""<<str<<"\" style=\"stroke:"<<color<<";stroke-width:1\"/>";
             //cout<<color<<endl;
             str.clear();
             return;
        }


}


// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<pair<int, int>> merger(vector<pair<int, int> > a, vector<pair<int, int> > b,int i)
{
    // n1 -> number of points in polygon a
    // n2 -> number of points in polygon b

    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;

    for (int i=1; i<n1; i++)

       {
           if (a[i].first > a[ia].first)
            ia = i;}

    // ib -> leftmost point of b

    for (int i=1; i<n2; i++)
       {
           if (b[i].first < b[ib].first)
            ib=i; }

    // finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >=0)
            inda = (inda + 1) % n1;

        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <=0)
        {
            indb = (n2+indb-1)%n2;
            done = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb=ib;
    done = 0;
    int g = 0;
    while (!done)//finding the lower tangent
    {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb+1)%n2])>=0)
            indb=(indb+1)%n2;

        while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1])<=0)
        {
            inda=(n1+inda-1)%n1;
            done=0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<pair<int, int>> ret;

    /*ret contains the convex hull after merging the two convex hulls
    with the points sorted in anti-clockwise order
    */

    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera)
    {
        ind = (ind+1)%n1;                       
        ret.push_back(a[ind]);
    }
    //draw_svg(a,0);
    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind+1)%n2;                       
        ret.push_back(b[ind]);
    }
    //draw_svg(b,1);
    //draw_svg(ret,0);
    return ret;

}

// Brute force algorithm to find convex hull for a set of less than 6 points
vector<pair<int, int>> bruteHull(vector<pair<int, int>> a, int i)
{
    /*
    Take any pair of points from the set and check whether it is the edge of the convex hull or not.
    if all the remaining points are on the same side of the line then the line is the edge of convex hull otherwise not
    */

    set<pair<int, int> >s; // to contains only unique elements

    for (int i=0; i<a.size(); i++)
    {
        for (int j=i+1; j<a.size(); j++)
        {
            int x1 = a[i].first, x2 = a[j].first;
            int y1 = a[i].second, y2 = a[j].second;

            int a1 = y1-y2;
            int b1 = x2-x1;
            int c1 = x1*y2-y1*x2;
            int pos = 0, neg = 0;
            for (int k=0; k<a.size(); k++)
            {
                if (a1*a[k].first+b1*a[k].second+c1 <= 0)
                    neg++;
                if (a1*a[k].first+b1*a[k].second+c1 >= 0)
                    pos++;
            }
            if (pos == a.size() || neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<pair<int, int>>ret;
    for (auto e:s)
        ret.push_back(e);

    // Sorting the points in the anti-clockwise order
    mid = {0, 0};
    int n = ret.size();
    for (int i=0; i<n; i++)
    {
        mid.first += ret[i].first;
        mid.second += ret[i].second;
        ret[i].first *= n;
        ret[i].second *= n;
    }
    sort(ret.begin(), ret.end(), compare);
    for (int i=0; i<n; i++)
        ret[i] = make_pair(ret[i].first/n, ret[i].second/n);

    return ret;
}

// Returns the convex hull for the given set of points
vector<pair<int, int>> divide(vector<pair<int, int>> a,int i)
{
    /* If the number of points is less than 6 then the
    function uses the brute algorithm to find the convex hull */
    if (a.size() <= 5)
        return bruteHull(a,i);

    // left contains the left half points
    // right contains the right half points
    vector<pair<int, int>>left, right;
    for (int i=0; i<a.size()/2; i++)
        left.push_back(a[i]);
    for (int i=a.size()/2; i<a.size(); i++)
        right.push_back(a[i]);

    // convex hull for the left and right sets
    vector<pair<int, int>>left_hull = divide(left,i);

    vector<pair<int, int>>right_hull = divide(right,i);

    // merging the convex hulls
    return merger(left_hull, right_hull,i);
}
bool isInside(vector<pair<int, int> > points,
              pair<int, int> query,int i)
{
    // Include the query point in the
    // polygon points
    points.push_back(query);

    // Form a convex hull from the points
    points =divide(points,i);

    // Iterate over the points
    // of convex hull
    for (auto x : points) {

        // If the query point lies
        // on the convex hull
        // then it wasn't inside
        if (x == query)
            return false;
    }

    // Otherwise it was Inside
    return true;
}


void solution(vector<pair<int, int>> a,int i)
{

  if (a.size() <= 2)
      return;

  vector<pair<int, int> > left;
  vector<pair<int, int> > right;
  for (int i=0; i<a.size()/2; i++)
      left.push_back(a[i]);
  for (int i=a.size()/2; i<a.size(); i++)
      right.push_back(a[i]);

  // convex hull for the left and right sets


  vector<pair<int, int>>left_hull = divide(left,0);

  //draw svg withh red color
  //cout<<"hello red"<<endl;
  draw_svg(left_hull,0);


  //remove left hull points from left
  vector<pair<int, int>>new_left;

    for(int i=0;i<left.size();i++)
    {
         // Query Points
     pair<int, int> query = { left[i].first, left[i].second };

    // Check if its inside
    if (isInside(left_hull, query,2)) {
        new_left.push_back(make_pair(left[i].first, left[i].second));
        }
    }

  vector<pair<int, int>>right_hull = divide(right,1);

  //draw svg of right_hull with blue color
  //cout<<"hello blue"<<endl;
  draw_svg(right_hull,1);


    //remove right hull points from right
   vector<pair<int, int>>new_right;
     for(int i=0;i<right.size();i++)
    {
         // Query Points
     pair<int, int> query = { right[i].first, right[i].second };

    // Check if its inside
    if (isInside(right_hull, query,2)) {
        new_right.push_back(make_pair(right[i].first, right[i].second));
        }
    }

    //call solution recursively on right and left part
  solution(new_right,1);
  solution(new_left,0);

}

// Driver code

int main(int argc, char * argv[])
{

  
  out<< "<?xml version=\"1.0\" standalone=\"no\" ?>\n";
  out<< "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n";
  out<< "<svg width=\"800px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n";

  vector< pair<int, int> > co_point;      //to store coordinates(x,y) points from input file

    ifstream input_file;

    if(argv[1] == NULL)
    {
        cout << "ERROR !!!, Input file not found" <<endl;
        return 0;
    }
    
        string line;
        input_file.open(argv[1]);

        getline(input_file, line);
        while(getline(input_file, line))
        {   
        stringstream ss(line);
        string word;
        //cout <<line<<endl;
        ss>>word;
        int x = stoi(word);
        ss>>word;
        int y = stoi(word);
        co_point.push_back(make_pair(x,y));
        }

        input_file.close();
    
    
    sort(co_point.begin(), co_point.end());     //sorting the coordinates points according to x-coordinate

    solution(co_point, 0);

    out << "</svg>" <<endl;
    out.close();

    return 0;

}
