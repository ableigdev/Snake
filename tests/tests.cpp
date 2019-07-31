#include <memory>
#include <vector>
#include "gtest/gtest.h"

#include "IFactory.h"
#include "ConsoleFactoryImpl.h"
#include "IViewer.h"
#include "ConsoleViewerImpl.h"
#include "ConsoleSnakeImpl.h"
#include "ConsoleFruitImpl.h"
#include "SecondConsoleFruitImpl.h"
#include "SnakeModelImpl.h"
#include "constants.h"

TEST(FactoryTest, Test1)
{
    auto factory(std::make_unique<factory_impl::console_factory_impl::ConsoleFactoryImpl>());

    EXPECT_TRUE(factory != nullptr);    
}

TEST(FactoryTest, Test2)
{
    auto factory(std::make_unique<factory_impl::console_factory_impl::ConsoleFactoryImpl>());

    EXPECT_TRUE(factory != nullptr);

    auto snake(factory->createSnake());
    auto fruits(factory->createFruits());

    EXPECT_TRUE(snake != nullptr);
    EXPECT_TRUE(!fruits.empty());
}

TEST(FactoryTest, Test3)
{
    auto factory(std::make_unique<factory_impl::console_factory_impl::ConsoleFactoryImpl>());

    EXPECT_TRUE(factory != nullptr);

    auto snake(factory->createSnake());
    auto fruits(factory->createFruits());

    EXPECT_TRUE(snake != nullptr);
    EXPECT_TRUE(!fruits.empty());

    auto viewer(factory->createViewer(std::move(snake), std::move(fruits)));

    EXPECT_TRUE(viewer != nullptr);
}

TEST(ConsoleViewerImpl, SnakeBodySize)
{
    auto snake(std::make_unique<snake_impl::console_snake_impl::ConsoleSnakeImpl>());
    auto fruit1(std::make_unique<fruit_impl::console_fruit_impl::ConsoleFruitImpl>());
    auto fruit2(std::make_unique<fruit_impl::console_fruit_impl::SecondConsoleFruitImpl>());

    std::vector<std::unique_ptr<interfaces::IFruit>> fruits;
    fruits.push_back(std::move(fruit1));
    fruits.push_back(std::move(fruit2));

    auto consoleViewer(std::make_unique<viewer_impl::console_viewer_impl::ConsoleViewerImpl>(std::move(snake), std::move(fruits)));
    consoleViewer->resetSnake();

    EXPECT_EQ(consoleViewer->getAllSnakeBody().size(), 3);

    consoleViewer->addPointOfBody({ 5, 5 });
    EXPECT_EQ(consoleViewer->getAllSnakeBody().size(), 4);

    consoleViewer->addPointOfBodyToBegin({ 6, 7 });
    EXPECT_EQ(consoleViewer->getAllSnakeBody().size(), 5);
}

TEST(ConsoleViewerImpl, SnakeBodySize2)
{
    auto snake(std::make_unique<snake_impl::console_snake_impl::ConsoleSnakeImpl>());
    auto fruit1(std::make_unique<fruit_impl::console_fruit_impl::ConsoleFruitImpl>());
    auto fruit2(std::make_unique<fruit_impl::console_fruit_impl::SecondConsoleFruitImpl>());

    std::vector<std::unique_ptr<interfaces::IFruit>> fruits;
    fruits.push_back(std::move(fruit1));
    fruits.push_back(std::move(fruit2));

    auto consoleViewer(std::make_unique<viewer_impl::console_viewer_impl::ConsoleViewerImpl>(std::move(snake), std::move(fruits)));
    consoleViewer->resetSnake();

    EXPECT_EQ(consoleViewer->getAllSnakeBody().size(), 3);

    consoleViewer->removeOldTail();
    EXPECT_EQ(consoleViewer->getAllSnakeBody().size(), 2);
}

TEST(ConsoleViewerImpl, Score)
{
    auto snake(std::make_unique<snake_impl::console_snake_impl::ConsoleSnakeImpl>());
    auto fruit1(std::make_unique<fruit_impl::console_fruit_impl::ConsoleFruitImpl>());
    auto fruit2(std::make_unique<fruit_impl::console_fruit_impl::SecondConsoleFruitImpl>());

    std::vector<std::unique_ptr<interfaces::IFruit>> fruits;
    fruits.push_back(std::move(fruit1));
    fruits.push_back(std::move(fruit2));

    auto consoleViewer(std::make_unique<viewer_impl::console_viewer_impl::ConsoleViewerImpl>(std::move(snake), std::move(fruits)));
    
    EXPECT_EQ(consoleViewer->score(), 0);
    consoleViewer->updateScore(15);
    EXPECT_EQ(consoleViewer->score(), 15);
}

TEST(SnakeModelImpl, SizeOfMatrix)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    EXPECT_EQ(model->getValueOfXSize(), 30);
    EXPECT_EQ(model->getValueOfYSize(), 24);
}

TEST(SnakeModelImpl, GetPoint)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    EXPECT_EQ(model->getPoint(0, 0), helpers::tagsOfTheGameSpace::WALL);
    EXPECT_EQ(model->getPoint(3, 3), helpers::tagsOfTheGameSpace::FREE_SPACE);
}

TEST(SnakeModelImpl, GetPointException)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    EXPECT_THROW(model->getPoint(31, 25), std::out_of_range);
}

TEST(SnakeModelImpl, AddPoint)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    model->addPoint(3, 3, helpers::tagsOfTheGameSpace::FRUIT);
    model->addPoint(4, 4, helpers::tagsOfTheGameSpace::SNAKE_TAIL);
    model->addPoint(4, 5, helpers::tagsOfTheGameSpace::SNAKE_BODY);
    model->addPoint(4, 6, helpers::tagsOfTheGameSpace::SNAKE_HEAD);

    EXPECT_EQ(model->getPoint(3, 3), helpers::tagsOfTheGameSpace::FRUIT);
    EXPECT_EQ(model->getPoint(4, 4), helpers::tagsOfTheGameSpace::SNAKE_TAIL);
    EXPECT_EQ(model->getPoint(4, 5), helpers::tagsOfTheGameSpace::SNAKE_BODY);
    EXPECT_EQ(model->getPoint(4, 6), helpers::tagsOfTheGameSpace::SNAKE_HEAD);
}

TEST(SnakeModelImpl, AddPointToWall)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    model->addPoint(0, 0, helpers::tagsOfTheGameSpace::FRUIT);

    EXPECT_NE(model->getPoint(0, 0), helpers::tagsOfTheGameSpace::FRUIT);
    EXPECT_EQ(model->getPoint(0, 0), helpers::tagsOfTheGameSpace::WALL);
}

TEST(SnakeModelImpl, DeletePoint)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    model->addPoint(3, 3, helpers::tagsOfTheGameSpace::FRUIT);
    EXPECT_EQ(model->getPoint(3, 3), helpers::tagsOfTheGameSpace::FRUIT);

    model->deletePoint(3, 3);
    EXPECT_EQ(model->getPoint(3, 3), helpers::tagsOfTheGameSpace::FREE_SPACE);
}

TEST(SnakeModelImpl, DeletePointException)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));

    EXPECT_THROW(model->deletePoint(50, 25), std::out_of_range);
}

TEST(SnakeModelImpl, DeletePointTheWall)
{
    auto model(std::make_unique<snake_model_impl::SnakeModelImpl>(30, 24));
    model->deletePoint(0, 0);

    EXPECT_EQ(model->getPoint(0, 0), helpers::tagsOfTheGameSpace::WALL);
    EXPECT_NE(model->getPoint(0, 0), helpers::tagsOfTheGameSpace::FREE_SPACE);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}