#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;
/*
Partners: hc55, jihwank4, nahyunk2
*/
//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		length_ = length;
		width_ = width;
	}
	
  	double getArea() const {
		return length_ * width_;
	}
	
  	double getVolume() const {
		return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle(rec.width_+width_, rec.length_+length_);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		double newWidth = (width_-rec.width_) > 0 ? width_-rec.width_:0;
		double newLength = (length_-rec.length_) > 0 ? length_-rec.length_:0;
		return Rectangle(newWidth, newLength);
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
        T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		double area = radius_ * radius_ * M_PI;
		return area;
	}
	
 	double getVolume() const{
		return 0;
	}
	
  	Circle operator + (const Circle& cir){
		return Circle(cir.radius_+radius_);
	}
	
	Circle operator - (const Circle& cir){
		return Circle((radius_-cir.radius_) > 0 ? radius_-cir.radius_:0);
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;
	}

  	double getVolume() const {
		double volume = (4.0/3.0)*M_PI*radius_*radius_*radius_;
		return volume;
	}	
	
  	double getArea() const {
		double area = 4.0*M_PI*radius_*radius_;
		return area;
	}

	Sphere operator + (const Sphere& sph) {
		return Sphere(sph.radius_+radius_);
	}

	Sphere operator - (const Sphere& sph) {
		return Sphere((radius_-sph.radius_) > 0 ? radius_-sph.radius_:0);
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		height_ = height;
		length_ = length;
		width_ = width;
	}
	
  	double getVolume() const {
		double volume = height_*width_*length_;
		return volume;
	}
  	
	double getArea() const {
		double area = 2*length_*width_ + 2*length_*height_ + 2*width_*height_;
		return area;
	}
	
	RectPrism operator + (const RectPrism& rectp){
		return RectPrism(rectp.width_+width_,rectp.length_+length_,rectp.height_+height_);
	}
	
	RectPrism operator - (const RectPrism& rectp){
		double temp = 0;
		return RectPrism(max(temp,width_-rectp.width_),max(temp,length_-rectp.length_),max(temp,height_-rectp.height_));
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
    ifstream file(file_name);
    int total, i;
    file >> total;

    if (!file) {
        return list<Shape*>(0, NULL);
    }

    list<Shape*> list;

    for (i = 0; i < total; i++) {
        string typeShape;
        file >> typeShape;

        if (typeShape == "Circle") {
            double circleRadius;
            file >> circleRadius;
            Shape* circlePointer = new Circle(circleRadius);
            list.push_back(circlePointer);
        }
        if (typeShape == "Rectangle") {
            double rectangleWidth, rectangleHeight;
            file >> rectangleWidth;
            file >> rectangleHeight;
            Shape* rectanglePointer = new Rectangle<double>(rectangleWidth, rectangleHeight);
            list.push_back(rectanglePointer);
        }
        if (typeShape == "Sphere") {
            double sphereRadius;
            file >> sphereRadius;
            Shape* spherePointer = new Sphere(sphereRadius);
            list.push_back(spherePointer);
        }
        if (typeShape == "RectPrism") {
            double rectWidth, rectLength, rectHeight;
            file >> rectWidth;
            file >> rectLength;
            file >> rectHeight;
            Shape* rectPointer = new RectPrism(rectWidth, rectLength, rectHeight);
            list.push_back(rectPointer);
        }
    }

    return list;
}


// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if (max_area < (*it)->getArea()) {
			max_area = (*it)->getArea();
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it!=shapes.end(); it++) {
		if(max_volume < (*it)->getVolume()) {
			max_volume = (*it)->getVolume();
		}
	}
	return max_volume;
}
#endif

