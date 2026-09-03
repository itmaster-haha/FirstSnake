#include <iostream>
#include <string>
#include <deque>

enum class Direction {
    up,
    right,
    down,
    left
};

class Point {
    private:
        int x;
        int y;

    public:
        Point(int x, int y) {
            this->x=x;
            this->y=y;
        }

        Point() {
            this->x=0;
            this->y=0;
        }

        int getX() {
            return this->x;
        }

        int getY() {
            return this->y;
        }

        void setY(int y) {
            this->y=y;
        }

        void setX(int x) {
            this->x=x;
        }

};

class Snake {
    private:
        std::deque<Point> body;
        Direction direction;
        bool isLive;

    public:
        Snake(){

            this->body.push_back(Point(7,7));
            this->body.push_back(Point(6,7));
            this->body.push_back(Point(5,7));
            this->body.push_back(Point(4,7));
            this->direction=Direction::right;
            this->isLive=true;
        }

        Direction getDirection() const {
            return this->direction;
        }

        bool getIsLive() const {
            return isLive;
        }

        void setDirection(Direction direction) {
            this->direction=direction;
        }

        void setLose() {
            this->isLive=false;
        }

};