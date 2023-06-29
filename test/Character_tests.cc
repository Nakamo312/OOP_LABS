#include <gtest/gtest.h>

#include <Character/Character.h>

using namespace character;
using namespace std;



TEST(CharacterTests, Knight_calcDamage)
{
    auto knight = make_shared<character::Knight>(350, 7, 60,"knight");
    
    EXPECT_EQ(knight->CalcDamage(), 60);
}


TEST(CharacterTests, Berserk_calcDamage)
{
    auto Berserk = make_shared<character::Berserk>(350, 7, 60, "Berserk");

    srand(time(NULL));
    float damage = Berserk->CalcDamage();
    if (Berserk->get_abylity_proc() == 1)
    {
        EXPECT_EQ(damage, 180);
    }
    else
    {
        EXPECT_EQ(damage, 60);
    }

}
TEST(CharacterTests, Assasin_calcDamage)
{
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "assasin");

    EXPECT_EQ(assasin->CalcDamage(), 60);
}

TEST(CharacterTests, Knight_takeDamage)
{
    auto knight1 = make_shared<character::Knight>(350, 7, 60, "knight");
    auto knight2= make_shared<character::Knight>(350, 7, 60, "knight");
    srand(time(NULL));
    knight1->takeDamage(*knight2);
    if (knight1->get_abylity_proc() == 1)
    {
        EXPECT_EQ(knight1->get_health(), 322.1f);
    }
    else
    {
        EXPECT_EQ(knight1->get_health(), 294.2f);
    }
}
TEST(CharacterTests, Assasin_takeDamage)
{
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "knight");
    auto knight = make_shared<character::Knight>(350, 7, 60, "knight");
    assasin->takeDamage(*knight);

    EXPECT_EQ(assasin->get_health(), 294.2f);
}

TEST(CharacterTests, Berserk_takeDamage)
{
    auto berserk = make_shared<character::Berserk>(350, 7, 60, "knight");
    auto knight = make_shared<character::Knight>(350, 7, 60, "knight");
    berserk->takeDamage(*knight);

    EXPECT_EQ(berserk->get_health(), 294.2f);
}

TEST(CharacterTests, Knight_Abylity)
{
    auto knight = make_shared<character::Knight>(350, 7, 60, "knight");
    knight->ability();
    EXPECT_EQ(knight->get_damage(), 0.65f*60);
    EXPECT_EQ(knight->get_armor(),1.25f * 7 +2);
}

TEST(CharacterTests, Assasin_Abylity)
{
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "knight");
    auto knight = make_shared<character::Knight>(350, 7, 60, "knight");
    assasin->ability();
    knight->Attack(*assasin);
    EXPECT_EQ(assasin->get_health(), 350);

}
TEST(CharacterTests, Berserk_Abylity)
{
    auto berserk = make_shared<character::Berserk>(350, 7, 60, "knight");
    berserk->ability();
    EXPECT_EQ(berserk->get_damage(), 1.5f * 60);
    EXPECT_EQ(berserk->get_armor(), (0.5f * 7) + 1);
}

TEST(CharacterTests, Knight_Attack)
{
    auto knight = make_shared<character::Knight>(350, 7, 60, "knight");
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "knight");
    
    knight->Attack(*assasin);

   EXPECT_EQ(assasin->get_health(), 294.2f);

}
TEST(CharacterTests, Assasin_Attack)
{
    auto assasin1 = make_shared<character::Assasin>(350, 7, 60, "knight");
    auto assasin2 = make_shared<character::Assasin>(350, 7, 60, "knight");
    srand(time(NULL));
    assasin1->Attack(*assasin2);
    if (assasin1->get_abylity_proc())
    {
        assasin1->Attack(*assasin2);
        EXPECT_NEAR(assasin2->get_health(), 238.4,0.001);

    }
    else
    {
        EXPECT_NEAR(assasin2->get_health(), 294.2f, 0.001);
    }
}

TEST(CharacterTests, Berserk_Attack)
{
    auto berserk = make_shared<character::Berserk>(350, 7, 60, "knight");
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "knight");
    srand(time(NULL));
    berserk->Attack(*assasin);
    if (berserk->get_abylity_proc())
    {
        EXPECT_EQ(assasin->get_health(), 182.6f);

    }
    else
    {
        EXPECT_EQ(assasin->get_health(), 294.2f);
    }
}

TEST(CharacterTests, equals)
{
    auto berserk1 = make_shared<character::Berserk>(350, 7, 60, "knight");
    auto berserk2 = make_shared<character::Berserk>(350, 1, 60, "knight");
    auto assasin = make_shared<character::Assasin>(350, 7, 60, "knight");


    EXPECT_TRUE(berserk1->equals(berserk2));
    EXPECT_FALSE(berserk1->equals(assasin));

}
TEST(CharacterTests, list_insert)
{
    CharacterList characters;
    characters.insert(make_shared<character::Assasin>(350, 7, 60, "b1"));
    characters.insert(make_shared<character::Berserk>(350, 7, 110, "b2"));
    characters.insert(make_shared<character::Knight>(350, 7, 90, "b3"));
    characters.insert(make_shared<character::Assasin>(350, 7, 60, "b4"),2);

    EXPECT_EQ(characters.size(),4);

    EXPECT_EQ(characters[0]->get_name(), "b1");
    EXPECT_EQ(characters[1]->get_name(), "b2");
    EXPECT_EQ(characters[2]->get_name(), "b4");
    EXPECT_EQ(characters[3]->get_name(), "b3");

}

TEST(CharacterListTests, index_of_strongest_heroes)
{
    CharacterList characters;
    characters.insert(make_shared<character::Assasin>(350, 7, 60, "b1"));
    characters.insert(make_shared<character::Berserk>(350, 7, 110, "b2"));
    characters.insert(make_shared<character::Knight>(350, 7, 90, "b3"));
    characters.insert(make_shared<character::Assasin>(350, 7, 60, "b4"));
    int index = index_of_strongest_hero(characters);

    ASSERT_EQ(index,1);
}