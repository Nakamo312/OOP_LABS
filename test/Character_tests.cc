#include <gtest/gtest.h>

#include <Character/Character.h>

#define CAPACITY 10

using namespace character;
using namespace std;



TEST(CharacterTests, calcDamage)
{
    const auto berserk = Character::createBerserk(350, 7, 60);
    const auto knight = Character::createKnight(350, 7, 60);
    int damage = 0;
    int count = 0;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        damage = berserk->CalcDamage();
        if (damage == 180)
        {
            count++;
        }
    }
    EXPECT_EQ(knight->CalcDamage(), 60);
    EXPECT_NEAR(count, 15,10);
    delete berserk;
    delete knight;
}
TEST(CharacterTests, Ability)
{
    auto knight = Character::createKnight(350, 10, 60);
    auto Assasin = Character::createAssasin(350, 10, 60);
    auto Berserk = Character::createBerserk(350, 10, 60);
    knight->ability();
    Assasin->ability();
    Assasin->takeDamage(*knight);
    Berserk->ability();
    
    EXPECT_EQ(knight->get_armor(), 1.25f * 10 +2);
    EXPECT_EQ(knight->get_damage(), 60 *0.65f);

    int damage = 0;
    int count = 0;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        damage = Berserk->CalcDamage();
        if (damage == Berserk->get_damage()*3)
        {
            count++;
        }
    }
    EXPECT_EQ(Assasin->get_health(),350);
    EXPECT_EQ(Berserk->get_armor(), 0.5f *10 + 1);
    EXPECT_EQ(Berserk->get_damage(), 1.5f * 60);
    EXPECT_NEAR(count, 45,10);
    delete Berserk;
    delete knight;
    delete Assasin;
}
TEST(CharacterTests, TakeDmage)
{
    const auto knight = Character::createKnight(350, 10, 60);
    auto knight1 = Character::createKnight(350, 10, 60);
    srand(time(NULL));
    knight1->takeDamage(*knight);
    EXPECT_NEAR(knight1->get_health(),296,27);

    delete knight;
    delete knight1;

}
TEST(CharacterTests, Attack)
{
    auto berserk = Character::createBerserk(350, 7, 60);
    auto Assasin = Character::createAssasin(350, 10, 60);
    srand(time(NULL));
    int count = 0;
    float mean_damage = 0;
    for (int i = 0; i < 100; i++)
    {
        mean_damage += berserk->get_health();
        Assasin->Attack(*berserk);
        mean_damage -= berserk->get_health();
    }
    mean_damage /= 100;
    EXPECT_NEAR(mean_damage, 60,25);
    delete berserk;
    delete Assasin;
}

TEST(CharacterListTests, insert)
{
    CharacterList list = CharacterList();
    auto knight = Character::createKnight(350, 10, 60);
    auto Assasin = Character::createAssasin(200, 10, 60);
    auto Berserk = Character::createBerserk(300, 10, 60);

    list.insert(knight);
    list.insert(Berserk);
    list.insert(Assasin);

    EXPECT_EQ(list[0]->get_type(), knight->get_type());
    EXPECT_EQ(list[1]->get_type(), Berserk->get_type());
    EXPECT_EQ(list[2]->get_type(), Assasin->get_type());
    delete Berserk;
    delete knight;
    delete Assasin;
}

TEST(CharacterListTests, remove)
{
    CharacterList list = CharacterList();
    auto knight = Character::createKnight(350, 10, 60);
    auto Assasin = Character::createAssasin(200, 10, 60);
    auto Berserk = Character::createBerserk(300, 10, 60);

    list.insert(knight);
    list.insert(Berserk);
    list.insert(Assasin);
    list.remove(Berserk);
    EXPECT_EQ(list[0]->get_type(), knight->get_type());
    EXPECT_EQ(list[1]->get_type(), Assasin->get_type());

}

TEST(CharacterListTests, index_of_strongest_hero)
{
    CharacterList list = CharacterList();
    auto knight = Character::createKnight(350, 10, 60);
    auto Assasin = Character::createAssasin(200, 10, 50);
    auto Berserk = Character::createBerserk(300, 10, 90);    
    list.insert(knight);
    list.insert(Berserk);
    list.insert(Assasin);
    int index = list.index_of_strongest_hero();
    
    EXPECT_EQ(index, 1);

}
