#ifndef QUADTREE_H
#define QUADTREE_H

#include <coreMath.h>
#include <vector>
#include <particle.h>
#include <queue>
#include <iostream>


//struct Rect {
//    float x, y, w, h;
//
//    bool contains(const Vector2& p) const {
//        return p.x >= x && p.x <= x + w &&
//            p.y >= y && p.y <= y + h;
//    }
//
//    bool intersects(const Rect& other) const {
//        return !(other.x > x + w ||
//            other.x + other.w < x ||
//            other.y > y + h ||
//            other.y + other.h < y);
//    }
//};
//
//
//class Quadtree {
//private:
//    bool circleIntersectsRect(const Vector2& center, float radius, const Rect& r);
//
//public:
//    static const int MAX_OBJECTS = 4;
//    static const int MAX_LEVELS = 5;
//
//    int level;
//    Rect bounds;
//    std::vector<Particle*> objects;
//    Quadtree* nodes[4];
//
//
//    Quadtree(int level, const Rect& bounds);
//
//    void clear();
//
//    void split();
//
//    std::vector<int> getIndices(Particle* p);
//
//    void insert(Particle* p);
//
//    void retrieve(std::vector<Particle*>& out, Particle* p);
//
//    void printLevelOrder() const;
//};


struct Rect {
    float x, y, w, h;

    bool contains(const Vector2& p) const {
        return p.x >= x && p.x <= x + w &&
            p.y >= y && p.y <= y + h;
    }

    bool intersects(const Rect& other) const {
        return !(other.x > x + w ||
            other.x + other.w < x ||
            other.y > y + h ||
            other.y + other.h < y);
    }
};

class Quadtree {
public:
    static const int MAX_OBJECTS = 4;
    static const int MAX_LEVELS = 5;

    int level;
    std::vector<Particle*> objects;
    Rect bounds;
    Quadtree* nodes[4];

    Quadtree(int level, const Rect& bounds);
    void clear();
    void split();
    int getIndex(Particle* p);
    void insert(Particle* p);
    void retrieve(std::vector<Particle*>& returnObjects, Particle* p);
};





#endif // QUADTREE_H