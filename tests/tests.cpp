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

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}