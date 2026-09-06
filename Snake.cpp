#include <iostream>
#include <string>
#include <deque>
#include <random>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

enum class Direction {
    up,
    right,
    down,
    left
};

enum class GameState {
    Playing,
    GameOver
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
        int score;
    
    public:
        Game() : snake(), field(snake), score(0) {
        }

        Snake getSnake() {
            return this->snake;
        }

        Field getField() {
            return this->field;
        }

        int getScore() {
            return this->score;
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
                    this->score += 10 + this->score;
                }
            }
        }

        void render(sf::RenderWindow& window) {
            Point point = Point();
            sf::RectangleShape shape(sf::Vector2f(30, 30));
            for(int i = 0; i < 15; i++) {
                for(int j = 0; j < 15; j++) {
                    point.setXY(i, j);
                    bool isSnake = false;
                    shape.setPosition(j*30, i*30);
                    for(int k = 0; k < snake.getBody().size(); k++) {
                        if(point == snake.getBody()[k]) {
                            isSnake = true;
                        }
                    }
                    if(isSnake) {
                        shape.setFillColor(sf::Color::Black);
                    }
                    else if(point == field.getFood()) {
                        shape.setFillColor(sf::Color::Green);
                    }
                    else {
                        shape.setFillColor(sf::Color::White);
                    }
                    window.draw(shape); 
                }
            } 
        }

        void up(){
            if(snake.getDirection() != Direction::down){
                snake.setDirection(Direction::up);
            }
        }

        void right(){
            if(snake.getDirection() != Direction::left){
                snake.setDirection(Direction::right);
            }            
        }
        
        void down(){
            if(snake.getDirection() != Direction::up){
                snake.setDirection(Direction::down);
            }
        }

        void left(){
            if(snake.getDirection() != Direction::right){
                snake.setDirection(Direction::left);
            }
        }
};

int main() {
    
    srand(time(0));
    Game game = Game();
    GameState state = GameState::Playing;
    sf::RenderWindow window(sf::VideoMode(450, 450), "Snake Game");
    sf::Font fontGameOver;
    fontGameOver.loadFromFile("Shrifts/ha Font.ttf");
    sf::Font fontScore;
    fontScore.loadFromFile("/home/rey/MyWorks/First/Shrifts/GR.ttf");
    sf::RectangleShape button1(sf::Vector2f(250, 100));
    sf::Text text("Game Over", fontGameOver, 40);
    text.setPosition(30, 20);
    text.setFillColor(sf::Color::White);
    sf::Text textScore(" ", fontScore, 40);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(100, 80);
    button1.setPosition(100, 150);
    button1.setFillColor(sf::Color::White);
    sf::Text text1("Repeat, please", fontScore, 40);
    text1.setPosition(110, 170);
    text1.setFillColor(sf::Color::Blue);
    sf::RectangleShape button2(sf::Vector2f(250, 100));
    button2.setPosition(100, 300);
    button2.setFillColor(sf::Color::White);
    sf::Text text2("Exit", fontScore, 40);
    text2.setPosition(110, 320);
    text2.setFillColor(sf::Color::Blue);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::W) {
                    game.up();
                }
                else if(event.key.code == sf::Keyboard::D) {
                    game.right();
                }
                else if(event.key.code == sf::Keyboard::S) {
                    game.down();
                }
                else if(event.key.code == sf::Keyboard::A) {
                    game.left();
                }
                else {
                    std::cout << "NOT THAT";
                }
            }
        }
        window.clear();
        if(state == GameState::Playing) {
            if(game.getSnake().getIsLive() == true) {
                game.update();
            }
            else {
                state = GameState::GameOver;
            }
            window.clear();
            game.render(window);
        }
        else if (state == GameState::GameOver) {
            std::string scoreText = "Your Score: " + std::to_string(game.getScore());
            textScore.setString(scoreText);
            window.draw(button1);
            window.draw(button2);
            window.draw(text);
            window.draw(textScore);
            window.draw(text1);
            window.draw(text2);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    game = Game();
                    state = GameState::Playing;
                    if(game.getSnake().getIsLive() == true) {
                        game.update();
                    }
                    else {
                        state = GameState::GameOver;
                    }
                    window.clear();
                    game.render(window);
                }
                if(button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
            }
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    /*do{
        game.update();
        game.render();
        //game.handleInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }while(game.getSnake().getIsLive() == true);*/
    return 0;
}