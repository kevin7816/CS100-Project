#include "Object_Stub.hpp"
#include "Ball_Stub.hpp"
#include "Player_Stub.hpp"

#include <vector>

#include "gtest/gtest.h"

TEST(ObjectTest, BallDefault) {
    Ball* ball = new Ball();
    EXPECT_EQ(0, ball->getX());
    EXPECT_EQ(0, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
}

TEST(ObjectTest, BallConstructor) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
}

TEST(ObjectTest, BallModifyX) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    ball->setX(1);
    EXPECT_EQ(1, ball->getX());
}

TEST(ObjectTest, BallModifyY) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    ball->setY(2);
    EXPECT_EQ(2, ball->getY());
}

TEST(ObjectTest, BallModifyH) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    ball->setH(10);
    EXPECT_EQ(10, ball->getH());
}

TEST(ObjectTest, BallModifyW) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    ball->setW(3);
    EXPECT_EQ(3, ball->getW());
}

TEST(ObjectTest, BallModifySpeed) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    EXPECT_EQ(16.0, ball->getSpeed());
    ball->setSpeed(20.0);
    EXPECT_EQ(20.0, ball->getSpeed());
}

TEST(ObjectTest, BallModifyVelX) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    EXPECT_EQ(0, ball->getVelX());
    ball->setVelX(20.0);
    EXPECT_EQ(20.0, ball->getVelX());
}

TEST(ObjectTest, BallModifyVelY) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    EXPECT_EQ(0, ball->getVelY());
    ball->setVelY(20.0);
    EXPECT_EQ(20.0, ball->getVelY());
}

TEST(ObjectTest, BallGetRect) {
    Ball* ball = new Ball(10, 20);
    EXPECT_EQ(10, ball->getX());
    EXPECT_EQ(20, ball->getY());
    EXPECT_EQ(16, ball->getH());
    EXPECT_EQ(16, ball->getW());
    EXPECT_EQ(0, ball->getVelY());
    ball->setVelY(20.0);
    EXPECT_EQ(20.0, ball->getVelY());
    std::vector<double> stub = ball->getRect();
    EXPECT_EQ(10, stub.at(0));
    EXPECT_EQ(20, stub.at(1));
    EXPECT_EQ(16, stub.at(2));
    EXPECT_EQ(16, stub.at(3));
}

TEST(ObjectTest, PlayerConstructor) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
}

TEST(ObjectTest, PlayerModifyX) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
    player->setX(50);
    EXPECT_EQ(50, player->getX());
}

TEST(ObjectTest, PlayerModifyY) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
    player->setY(50);
    EXPECT_EQ(50, player->getY());
}

TEST(ObjectTest, PlayerModifyH) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
    player->setH(50);
    EXPECT_EQ(50, player->getH());
}

TEST(ObjectTest, PlayerModifyW) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
    player->setW(50);
    EXPECT_EQ(50, player->getW());
}

TEST(ObjectTest, PlayerGetRect) {
    Player* player = new Player(10, 20, 30, 40);
    EXPECT_EQ(10, player->getX());
    EXPECT_EQ(20, player->getY());
    EXPECT_EQ(30, player->getH());
    EXPECT_EQ(40, player->getW());
    player->setY(50);
    EXPECT_EQ(50, player->getY());
    std::vector<double> stub = player->getRect();
    EXPECT_EQ(10, stub.at(0));
    EXPECT_EQ(50, stub.at(1));
    EXPECT_EQ(30, stub.at(2));
    EXPECT_EQ(40, stub.at(3));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}