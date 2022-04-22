/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2022
 * Author: Vu Van Tien
 * Date: 15.02.2022
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point
{
private:
    int x;
    int y;

public:
    Point(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    };
    string toString() const
    {
        stringstream ss;
        ss << "<Point[" << x << "," << y << "]>";
        return ss.str();
    };

    int distanceTo(const Point &otherPoint) const
    {
        float dist;
        dist = sqrt(pow(this->x - otherPoint.x, 2) + pow(this->y - otherPoint.y, 2));
        return ceil(dist);
    };
};

class Node
{
private:
    Point point;
    Node *next;

    friend class Path;

public:
    Node(const Point &point = Point(), Node *next = NULL)
    {
        this->point = point;
        this->next = next;
    };
    string toString() const
    {
        stringstream ss;
        ss << "<Node[" << this->point.toString() << "]>";
        return ss.str();
    };
};

class Path
{
private:
    Node *head;
    Node *tail;
    int count;
    int length;

public:
    Path()
    {
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
        this->length = -1;
    };
    ~Path()
    {
        Node *curr;
        curr = this->head;
        do
        {
            delete curr;
            curr = curr->next;
        } while (curr != NULL);
    };

    void addPoint(int x, int y)
    {
        Point *newPoint = new Point(x, y);
        Node *newNode = new Node(*newPoint);
        if (this->head == NULL)
        {
            this->head = this->tail = newNode;
            this->length = 0;
        }
        else
        {
            this->tail->next = newNode;
            this->length += newNode->point.distanceTo(this->tail->point);
            this->tail = newNode;
        }
        this->count++;
    };
    string toString() const
    {
        stringstream ss;
        ss << "<Path[count:" << this->count << ",length:" << this->length << ",[";
        stringstream ss2;
        if (this->head == NULL)
            ss2 << "";
        else
        {
            Node *curr = this->head;
            while (curr != NULL)
            {
                if (curr->next != NULL)
                    ss2 << curr->toString() << ",";
                else
                    ss2 << curr->toString();
                curr = curr->next;
            }
        }
        ss << ss2.str() << "]]>";
        return ss.str();
    };
    Point getLastPoint() const
    {
        string strX = "", strY = "";
        int flag = 0;
        string clue = this->tail->point.toString();
        for (int i = 0; i < clue.length(); i++)
        {
            switch (flag)
            {
            case 0:
                break;
            case 1:
                strX = strX + clue[i];
                break;
            case 2:
                strY = strY + clue[i];
                break;
            }
            if (clue[i] == '[')
                flag = 1;
            if (clue[i] == ',')
                flag = 2;
            if (clue[i] == ']')
                flag = 0;
        }
        Point *newPoint = new Point(stoi(strX), stoi(strY));
        return *newPoint;
    };
};

class Character
{
private:
    string name;
    Path *path;

public:
    Character(const string &name = "")
    {
        this->name = name;
        Path *newPath = new Path();
        this->path = newPath;
    };
    ~Character(){
        delete this->path;
    };
    string getName() const
    {
        return this->name;
    };
    void setName(const string &name)
    {
        this->name=name;
    };

    void moveToPoint(int x, int y)
    {
        this->path->addPoint(x,y);
    };
    string toString() const
    {
        stringstream ss;
        ss<<"<Character[name:"<<this->name<<",path:"<<this->path->toString()<<"]>";
        return ss.str();
    };
};

bool rescueSherlock(
    const Character &chMurderer,
    const Character &chWatson,
    int maxLength,
    int maxDistance,
    int &outDistance)
{
    string strL1="";
    string clue1=chMurderer.toString();
    for(int i=clue1.find("length")+2;i++;)
    if(clue1[i]-'0'>=0&&clue1[i]-'0'<=9)
    strL1=strL1+clue1[i];
    else break;
     string strL2="";
    string clue2=chWatson.toString();
    for(int i=clue2.find("length")+2;i++;)
    if(clue2[i]-'0'>=0&&clue2[i]-'0'<=9)
    strL2=strL2+clue2[i];
    else break;
    outDistance=abs(stoi(strL1)-stoi(strL2));
    if(outDistance>maxLength)
    {
        outDistance=-1;
        return false;
    }
    return true;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */