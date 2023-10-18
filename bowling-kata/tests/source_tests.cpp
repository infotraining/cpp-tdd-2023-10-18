#include <algorithm>
#include <string>
#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;



class BowlingGame
{
    std::vector<unsigned > rolls_;  

    unsigned int frame_score(const unsigned int index_roll) const
	{
    	return rolls_[index_roll] + rolls_[index_roll+1];
    }
public:
    BowlingGame() {}

    unsigned int score() const 
    {
        unsigned int result = 0;

        for(size_t i = 0; i < rolls_.size(); i += 2)
        {
            if (is_spare(i))
                result += spare_bonus(i);

            result += frame_score(i);
        }

        return result;
    }
    
    void roll(const unsigned int pins) 
    {
        assert(pins < all_pins);
        rolls_.push_back(pins);
    }

    bool is_spare(const unsigned int index_roll) const
    {
        return frame_score(index_roll) == all_pins;
    }

    unsigned int spare_bonus(const unsigned int index_roll) const
	{
    	return rolls_[index_roll+2];
    }

    static constexpr unsigned int all_pins = 10;	
};

class BowlingGameTests : public ::testing::Test
{
protected:
    BowlingGame game; // SUT

 //   void SetUp() override
	//{
 //       //...
 //   }

 //   void TearDown() override
 //   {
 //       //...
 //   }

    void roll_many(const int rolls, const int pins)
	{
        for (int i = 0; i < rolls; ++i)
    	    game.roll(pins);
    }

    void roll_spare()
    {
        game.roll(5);
        game.roll(5);
    }
};

TEST_F(BowlingGameTests, WhenStartScoreIsZero)
{
    EXPECT_EQ(game.score(), 0);
}



TEST_F(BowlingGameTests, WhenAllRollInGutterScoreIsZero)
{
    // Act
    roll_many(20, 0);

    // Assert
	EXPECT_EQ(game.score(), 0);
}

TEST_F(BowlingGameTests, WhenSimpleGameScoreIsSumOfAllPins)
{
    // Act
    roll_many(20, 1);

	EXPECT_EQ(game.score(), 20);
}

TEST_F(BowlingGameTests, WhenSpareNextRollIsCountedTwice)
{	
    roll_spare();
    
    game.roll(3); 
    roll_many(17, 1);
    
 	EXPECT_EQ(game.score(), 33);
}