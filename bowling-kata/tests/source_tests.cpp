#include <algorithm>
#include <string>
#include <memory>
#include <array>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;



class BowlingGame
{
    static constexpr size_t max_rolls = 21;
    std::array<unsigned int, max_rolls> rolls_{};
    size_t current_roll_ = 0;
public:
    BowlingGame() {}

    unsigned int score() const 
    {
        unsigned int result = 0;
        unsigned int roll_index = 0;

        for(size_t frame_index = 0; frame_index < all_frames; ++frame_index)
        {
            if (is_strike(roll_index))
            {
                result += all_pins + strike_bonus(roll_index);
                ++roll_index;            
            }
            else 
            {
                result += frame_score(roll_index);

                if (is_spare(roll_index))
                    result += spare_bonus(roll_index);   
                
                roll_index += 2;
            }                               
        }

        return result;
    }
    
    void roll(const unsigned int pins) 
    {
        assert(pins <= all_pins);
        rolls_[current_roll_++] = pins;
    }

    bool is_spare(const unsigned int index_roll) const
    {
        return frame_score(index_roll) == all_pins;
    }

    bool is_strike(const unsigned int index_roll) const
    {
        return rolls_[index_roll] == all_pins;
    }

    unsigned int spare_bonus(const unsigned int index_roll) const
	{
    	return rolls_[index_roll+2];
    }

    unsigned int strike_bonus(const unsigned int index_roll) const
    {
        return rolls_[index_roll + 1] + rolls_[index_roll + 2];
    }

    unsigned int frame_score(const unsigned int index_roll) const
    {
        return rolls_[index_roll] + rolls_[index_roll + 1];
    }

    static constexpr unsigned int all_pins = 10;	
    static constexpr unsigned int all_frames = 10;
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

    void roll_strike()
	{
    	game.roll(10);
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

TEST_F(BowlingGameTests, WhenStrikeNextTwoRollsAreCountedTwice)
{
    roll_strike();

	game.roll(3);
	game.roll(4);
	roll_many(16, 1);

	EXPECT_EQ(game.score(), 40);
}

TEST_F(BowlingGameTests, SpareInLastFrameOneExtraRoll)
{
    roll_many(18, 1);
	roll_spare();
	game.roll(3);

	EXPECT_EQ(game.score(), 31);
}

TEST_F(BowlingGameTests, StrikeInLastFrameTwoExtraRolls)
{
    roll_many(18, 1);
    roll_strike();
    game.roll(3);
    game.roll(7);

    EXPECT_EQ(game.score(), 38);
}

TEST_F(BowlingGameTests, WhenPerfectGameScoreIs300)
{
	roll_many(12, 10);

	EXPECT_EQ(game.score(), 300);
}

struct BowlingGameParams
{
    std::vector<size_t> rolls;
    unsigned int score;
};

class BowlingGameParamTests : public ::testing::TestWithParam<BowlingGameParams>
{
protected:
    BowlingGame game; // SUT

};

TEST_P(BowlingGameParamTests, RealExamplesWithScore)
{    
    const auto& param = GetParam();
	for (const auto& roll : param.rolls)
		game.roll(roll);

	EXPECT_EQ(game.score(), param.score);
}

BowlingGameParams params[] = {
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 20},
    {{10, 3, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 44},
	{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 5, 5}, 38},
	{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10}, 48},
    {{1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 1, 9, 10}, 119},
    {{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 300}
};

INSTANTIATE_TEST_SUITE_P(PackOfBowlingTests, BowlingGameParamTests, ::testing::ValuesIn(params));