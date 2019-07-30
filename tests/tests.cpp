#include <memory>
#include "gtest/gtest.h"

#include "IFactory.h"
#include "ConsoleFactoryImpl.h"

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

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}