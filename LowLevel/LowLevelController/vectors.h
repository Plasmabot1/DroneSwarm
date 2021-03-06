#define __ASSERT_USE_STDERR

#include <assert.h>
#include <math.h>

float fixangle(float angle, float reference) {
  float out = angle;
  if(reference < angle) {
    for(; abs(out-reference-360.0) < abs(out-reference); out -= 360.0);
    return out;
  } else {
    for(; abs(out-reference+360.0) < abs(out-reference); out += 360.0);
    return out;
  }
}

struct Vector3D {
    union {float x, roll;};
    union {float y, pitch;};
    union {float z, yaw;};
    
    Vector3D() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3D(float x1,float y1,float z1=0) {
        x = x1;
        y = y1;
        z = z1;
    }

    /*Vector3D(float v[3]) {
        vec=v;
    }*/

    Vector3D(const Vector3D &v) { //copy constructor
      x = v.x;
      y = v.y;
      z = v.z;
    }
    
    Vector3D operator+(const Vector3D &v) {    //addition
      return Vector3D(x+v.x,y+v.y,z+v.z);
    }
    
    Vector3D &operator+=(const Vector3D &v) {  //assigning new result to the vector
      x+=v.x;
      y+=v.y;
      z+=v.z;
      return *this;
    }
    
    Vector3D operator-(const Vector3D &v) {    //substraction
      return Vector3D(x-v.x,y-v.y,z-v.z);
    }
    
    Vector3D &operator-=(const Vector3D &v) {  //assigning new result to the vector
      x-=v.x;
      y-=v.y;
      z-=v.z;
      return *this;
    }
    
    Vector3D operator*(float value) {    //multiplication
      return Vector3D(x*value,y*value,z*value);
    }
    
    Vector3D &operator*=(float value) {  //assigning new result to the vector.
      x*=value;
      y*=value;
      z*=value;
      return *this;
    }
    
    Vector3D operator/(float value) {    //division
      assert(value!=0);
      return Vector3D(x/value,y/value,z/value);
    }
    
    Vector3D &operator/=(float value) {  //assigning new result to the vector
      assert(value!=0);
      x/=value;
      y/=value;
      z/=value;
      return *this;
    }
    
    Vector3D &operator=(const Vector3D &v) {
      x = v.x;
      y = v.y;
      z = v.z;
      return *this;
    }
    
    float dot(const Vector3D &v) { //scalar dot_product
      return x*v.x+v.y*y+v.z*z;
    }
    
    Vector3D cross(const Vector3D &v) {    //cross_product
      return Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
    }
    
    float square() { //gives square of the vector
      return x*x+y*y+z*z;
    }
    
    float magnitude() {  //magnitude of the vector
      return sqrt(square());
    }
    
    Vector3D normalize() {   //normalized vector
      float m = magnitude();
      assert(m!=0);
      *this/=m;
      return *this;
    }

    float distance(const Vector3D &v) {    //gives distance between two vectors
      Vector3D dist=*this-v;
      return dist.magnitude();
    }

    Vector3D componentMultiply(float a, float b, float c) {
      return Vector3D(x*a,y*b,z*c);
    }

    void fix(Vector3D ref) {
      yaw = fixangle(yaw, ref.yaw);
      roll = fixangle(roll, ref.roll);
      pitch = fixangle(pitch, ref.pitch);
    }

    float scalarProject(Vector3D v) { //magnitude of projection of this onto v
      return dot(v)/v.magnitude(); // ||this||*||v||*cos(theta)/||v||
    }

    Vector3D project(Vector3D v) { //project this onto v
      return *this*dot(v)/v.square();
    }

    float toEuler(Vector3D v) {//sets this to euler angles, returns magnitude
      float r = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
      roll = atan2(v.y, v.x) * 180.0/PI;
      pitch = acos(v.z/r) * 180.0/PI;
      return r;
    }

    void print() {
      Serial.print(x);
      Serial.print(", ");
      Serial.print(y);
      Serial.print(", ");
      Serial.print(z);
    }

    void println() {
      print();
      Serial.println();
    }
};
