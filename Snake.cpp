#include <iostream>
#include <string>

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

        int getY {
            return this->y;
        }

        void setY(int y) {
            this->y=y;
        }

        void setX(int x) {
            this->x=x;
        }
}

class Snake {
    private:
        int size;
        bool isLive;

    public:
        Snake(int size, bool isLive){

            this->size=size;
            this->isLive=isLive;
        }

        int getSize() const {
            return this->size;
        }

        bool getIsLive() const {
            return isLive;
        }

        void setSize() {
            this->size+=1;
        }

        void setLose() {
            this->isLive=false;
        }

}
