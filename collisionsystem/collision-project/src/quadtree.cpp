#include <quadtree.h>


//bool Quadtree::circleIntersectsRect(const Vector2& center, float radius, const Rect& r)
//{
//    float closestX = std::max(r.x, std::min(center.x, r.x + r.w));
//    float closestY = std::max(r.y, std::min(center.y, r.y + r.h));
//
//    float dx = center.x - closestX;
//    float dy = center.y - closestY;
//
//    return (dx * dx + dy * dy) <= radius * radius;
//}
//
//Quadtree::Quadtree(int level, const Rect& bounds)
//    : level(level), bounds(bounds) {
//    nodes[0] = nodes[1] = nodes[2] = nodes[3] = nullptr;
//}
//
//void Quadtree::clear() {
//    objects.clear();
//    for (int i = 0; i < 4; ++i) {
//        if (nodes[i]) {
//            nodes[i]->clear();
//            delete nodes[i];
//            nodes[i] = nullptr;
//        }
//    }
//}
//
//void Quadtree::split() {
//    float halfW = bounds.w / 2.0f;
//    float halfH = bounds.h / 2.0f;
//
//    nodes[0] = new Quadtree(level + 1, Rect{ bounds.x,         bounds.y,         halfW, halfH });
//    nodes[1] = new Quadtree(level + 1, Rect{ bounds.x + halfW,   bounds.y,         halfW, halfH });
//    nodes[2] = new Quadtree(level + 1, Rect{ bounds.x,         bounds.y + halfH,   halfW, halfH });
//    nodes[3] = new Quadtree(level + 1, Rect{ bounds.x + halfW,   bounds.y + halfH,   halfW, halfH });
//}
//
//
//std::vector<int> Quadtree::getIndices(Particle* p)
//{
//    std::vector<int> indices;
//
//    Vector2 pos = p->getPosition();
//    float r = p->getRadius();
//
//    // Child node bounds
//    float halfW = bounds.w / 2.0f;
//    float halfH = bounds.h / 2.0f;
//
//    Rect child[4] = {
//        {bounds.x,         bounds.y,         halfW, halfH}, // 0
//        {bounds.x + halfW,   bounds.y,         halfW, halfH}, // 1
//        {bounds.x,         bounds.y + halfH,   halfW, halfH}, // 2
//        {bounds.x + halfW,   bounds.y + halfH,   halfW, halfH}  // 3
//    };
//
//    for (int i = 0; i < 4; i++) {
//        if (circleIntersectsRect(pos, r, child[i])) {
//            indices.push_back(i);
//        }
//    }
//
//    return indices;
//}
//
//
//
//void Quadtree::insert(Particle* p)
//{
//    // If we have children, try inserting into them
//    if (nodes[0] != nullptr) {
//        auto indices = getIndices(p);
//
//        if (!indices.empty()) {
//            for (int idx : indices) {
//                nodes[idx]->insert(p);
//            }
//            return;
//        }
//    }
//
//    // Otherwise store in this node
//    objects.push_back(p);
//
//    // Split if needed
//    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
//        if (nodes[0] == nullptr)
//            split();
//
//        // Re-distribute objects into children
//        auto it = objects.begin();
//        while (it != objects.end()) {
//            auto indices = getIndices(*it);
//
//            if (!indices.empty()) {
//                for (int idx : indices) {
//                    nodes[idx]->insert(*it);
//                }
//                it = objects.erase(it);
//            }
//            else {
//                ++it;
//            }
//        }
//    }
//}
//
//
//void Quadtree::retrieve(std::vector<Particle*>& out, Particle* p)
//{
//    auto indices = getIndices(p);
//
//    if (!indices.empty() && nodes[0] != nullptr) {
//        for (int idx : indices) {
//            nodes[idx]->retrieve(out, p);
//        }
//    }
//
//    // Add objects stored in this node
//    out.insert(out.end(), objects.begin(), objects.end());
//}
//
//void Quadtree::printLevelOrder() const
//{
//    std::queue<const Quadtree*> q;
//    q.push(this);
//
//    int level = 0;
//
//    while (!q.empty()) {
//        int nodesAtThisLevel = q.size();
//
//        std::cout << "Level " << level << ": ";
//
//        while (nodesAtThisLevel--) {
//            const Quadtree* node = q.front();
//            q.pop();
//
//            // Print this node's contents
//            std::cout << "[Objs: " << node->objects.size() << "] ";
//
//            // Enqueue children if they exist
//            for (int i = 0; i < 4; i++) {
//                if (node->nodes[i] != nullptr) {
//                    q.push(node->nodes[i]);
//                }
//            }
//        }
//
//        std::cout << std::endl;
//        level++;
//    }
//}




Quadtree::Quadtree(int level, const Rect& bounds)
        : level(level), bounds(bounds)
    {
        for (int i = 0; i < 4; i++) nodes[i] = nullptr;
    }

    void Quadtree::clear() {
        objects.clear();
        for (int i = 0; i < 4; i++) {
            if (nodes[i]) {
                nodes[i]->clear();
                delete nodes[i];
                nodes[i] = nullptr;
            }
        }
    }

    void Quadtree::split() {
        float subW = bounds.w / 2.0f;
        float subH = bounds.h / 2.0f;
        float x = bounds.x;
        float y = bounds.y;

        nodes[0] = new Quadtree(level + 1, Rect{ x + subW, y,       subW, subH });
        nodes[1] = new Quadtree(level + 1, Rect{ x,       y,       subW, subH });
        nodes[2] = new Quadtree(level + 1, Rect{ x,       y + subH,  subW, subH });
        nodes[3] = new Quadtree(level + 1, Rect{ x + subW,  y + subH,  subW, subH });
    }

    int Quadtree::getIndex(Particle* p) {
        Vector2 pos = p->getPosition();
        float midX = bounds.x + bounds.w / 2.0f;
        float midY = bounds.y + bounds.h / 2.0f;

        bool top = pos.y < midY;
        bool bottom = pos.y >= midY;
        bool left = pos.x < midX;
        bool right = pos.x >= midX;

        if (top && right) return 0;
        if (top && left)  return 1;
        if (bottom && left) return 2;
        if (bottom && right) return 3;

        return -1; // fits multiple nodes
    }

    void Quadtree::insert(Particle* p) {
        if (nodes[0] != nullptr) {
            int index = getIndex(p);
            if (index != -1) {
                nodes[index]->insert(p);
                return;
            }
        }

        objects.push_back(p);

        if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
            if (nodes[0] == nullptr)
                split();

            int i = 0;
            while (i < objects.size()) {
                int index = getIndex(objects[i]);
                if (index != -1) {
                    nodes[index]->insert(objects[i]);
                    objects.erase(objects.begin() + i);
                }
                else {
                    i++;
                }
            }
        }
    }

    void Quadtree::retrieve(std::vector<Particle*>& returnObjects, Particle* p) {
        int index = getIndex(p);
        if (index != -1 && nodes[0] != nullptr)
            nodes[index]->retrieve(returnObjects, p);

        returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());
    }
