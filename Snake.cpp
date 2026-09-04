#include <iostream>
#include <string>
#include <deque>
#include <random>
#include <chrono>
#include <thread>

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

        int getX() const {
            return this->x;
        }

        int getY() const {
            return this->y;
        }

        void setY(int y) {
            this->y=y;
        }

        void setX(int x) {
            this->x=x;
        }

        void setXY(int x, int y) {
            this->x = x;
            this->y = y;
        }

        bool operator==(const Point& other) const {
            if(this->x == other.x && this->y == other.y) {
                return true;
            }
            else {
                return false;
            }
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

        const std::deque<Point>& getBody() const {
            return this->body;
        }

        void setDirection(Direction direction) {
            this->direction=direction;
        }

        void setLose() {
            this->isLive=false;
        }

        void grow() {
            int x;
            int y;
            if(this->direction==Direction::up) {
                y = this->body[0].getY();
                x = this->body[0].getX()-1;
            }
            else if(this->direction==Direction::right) {
                y = this->body[0].getY()+1;
                x = this->body[0].getX();
            }
            else if(this->direction==Direction::down) {
                y = this->body[0].getY();
                x = this->body[0].getX()+1;
            }
            else if(this->direction==Direction::left) {
                y = this->body[0].getY()-1;
                x = this->body[0].getX();
            }
            this->body.push_front(Point(x, y));
        }

        void step() {
            grow();
            this->body.pop_back();
        }

};

class Field {
    private:
        Point food;
    
    public:

        Point randPoint() {
            int x = rand()%15;
            int y = rand()%15;
            Point point(x, y);
            return point;
        }

        void newPoint(const Snake& snake) {
            Point point = randPoint();
            std::deque<Point> snakeD = snake.getBody();
            bool op = false;
            do{
                op = true;
                for(int i = 0; i < snakeD.size(); i++) {
                    if(point==snakeD[i]) {
                        point = randPoint();
                        op = false;
                        break;
                    }
                }
            }while(op == false);
            this->food = point;
        }

        /*Field() {
            this->food=randPoint();
            while((this->food.getX()==7 || this->food.getX()==6 || this->food.getX()==5 || this->food.getX()==4) && this->food.getY()==7) {
                this->food=randPoint();
            }
        }*/

        Field(const Snake& snake) {
            newPoint(snake);
        }

        Point getFood() {
            return food;
        }
};

class Game {
    private:
        Snake snake;
        Field field;
    
    public:
        Game() : snake(), field(snake) {
        }

        Snake getSnake() {
            return this->snake;
        }

        Field getField() {
            return this->field;
        }

        void isGameOver() {
            if(snake.getBody()[0].getX()==-1 || snake.getBody()[0].getX()==15 || snake.getBody()[0].getY()==-1 || snake.getBody()[0].getY()==15) {
                snake.setLose();
                return;
            }
            for(int i = 3; i < snake.getBody().size(); i++) {
                if(snake.getBody()[0] == snake.getBody()[i]) {
                    snake.setLose();
                    return;
                }
            }
        }

        void update() {
            if(snake.getIsLive() == true) {
                snake.step();
                isGameOver();
                if(snake.getBody()[0] == field.getFood()) {
                    snake.grow();
                    field.newPoint(snake);
                }
            }
        }

        void render() {
            Point point = Point();
            for(int i = 0; i < 15; i++) {
                for(int j = 0; j < 15; j++) {
                    point.setXY(i, j);
                    bool isSnake = false;
                    for(int k = 0; k < snake.getBody().size(); k++) {
                        if(point == snake.getBody()[k]) {
                            isSnake = true;
                        }
                    }
                    if(isSnake) {
                        std::cout << 0;
                    }
                    else if(point == field.getFood()) {
                        std::cout << "*";
                    }
                    else {
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }            
        }

        void handleInput() {
            char key;
            std::cin >> key;
            if(key == 'w') {
                if(snake.getDirection() != Direction::down){
                    snake.setDirection(Direction::up);
                }
            }
            if(key == 'a') {
                if(snake.getDirection() != Direction::right){
                    snake.setDirection(Direction::left);
                }
            }
            if(key == 's') {
                if(snake.getDirection() != Direction::up){
                    snake.setDirection(Direction::down);
                }
            }
            if(key == 'd') {
                if(snake.getDirection() != Direction::left){
                    snake.setDirection(Direction::right);
                }
            }
        }
};

int main() {
    srand(time(0));
    Game game = Game();
    do{
        game.update();
        game.render();
        game.handleInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }while(game.getSnake().getIsLive() == true);
    return 0;
}