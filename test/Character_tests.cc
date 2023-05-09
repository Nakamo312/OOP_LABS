#include <gtest/gtest.h>

#include <Character/Character.h>

#define CAPACITY 10

using namespace character;
using namespace std;


TEST(CharacterTests, Getters) {
    // Arrange
    Character ch(Type::Knight, 300, 15,50);

    // Act
    Type _type = ch.get_type();
    float health = ch.get_health();
    float armor = ch.get_armor();
    float damage = ch.get_damage();
    int chance = ch.get_abilityChance();
    // Assert
    EXPECT_EQ(_type, Type::Knight);
    EXPECT_EQ(health, 300);
    EXPECT_EQ(armor, 15);
    EXPECT_EQ(damage, 50);
    EXPECT_EQ(chance, 15);
}

TEST(CharacterTests, ctors) {
    // Arrange
    Character ch;
    const Character knight = Character::createKnight(400, 20, 50);
    const Character assasin = Character::createAssasin(250, 5, 75);
    const Character berserk = Character::createBerserk(350,7, 60);

    // Assert
    EXPECT_EQ(ch.get_type(), Type::Knight);
    EXPECT_EQ(ch.get_health(), 300);
    EXPECT_EQ(ch.get_armor(), 5);
    EXPECT_EQ(ch.get_damage(), 56);
    EXPECT_EQ(ch.get_abilityChance(), 15);

    EXPECT_EQ(assasin.get_type(), Type::Assasin);
    EXPECT_EQ(knight.get_type(), Type::Knight);
    EXPECT_EQ(berserk.get_type(), Type::Berserk);

}

TEST(CharacterTests, setters)
{
    Character ch;
    ch.set_health(500);
    ch.set_armor(30);
    ch.set_damage(100);

    EXPECT_EQ(ch.get_health(), 500);
    EXPECT_EQ(ch.get_armor(), 30);
    EXPECT_EQ(ch.get_damage(), 100);
}

TEST(CharacterTests, calcDamage)
{
    const Character berserk = Character::createBerserk(350, 7, 60);
    const Character knight = Character::createKnight(350, 7, 60);
    int damage = 0;
    int count = 0;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        damage = berserk.CalcDamage();
        if (damage == 180)
        {
            count++;
        }
    }
    EXPECT_EQ(knight.CalcDamage(), 60);
    EXPECT_NEAR(count, 15,10);

}
TEST(CharacterTests, Ability)
{
    Character knight = Character::createKnight(350, 10, 60);
    Character Assasin = Character::createAssasin(350, 10, 60);
    Character Berserk = Character::createBerserk(350, 10, 60);
    knight.ability();
    Assasin.ability();
    Assasin.takeDamage(knight);
    Berserk.ability();
    
    EXPECT_EQ(knight.get_armor(), 1.25f * 10 +2);
    EXPECT_EQ(knight.get_damage(), 60 *0.65f);

    int damage = 0;
    int count = 0;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        damage = Berserk.CalcDamage();
        if (damage == Berserk.get_damage()*3)
        {
            count++;
        }
    }
    EXPECT_EQ(Assasin.get_health(),350);
    EXPECT_EQ(Berserk.get_armor(), 0.5f *10 + 1);
    EXPECT_EQ(Berserk.get_damage(), 1.5f * 60);
    EXPECT_NEAR(count, 45,10);

}
TEST(CharacterTests, TakeDmage)
{
    const Character knight = Character::createKnight(350, 10, 60);
    Character knight1 = Character::createKnight(350, 10, 60);
    srand(time(NULL));
    knight1.takeDamage(knight);
    EXPECT_NEAR(knight1.get_health(),296,27);
}
TEST(CharacterTests, Attack)
{
    Character berserk = Character::createBerserk(350, 7, 60);
    Character Assasin = Character::createAssasin(350, 10, 60);
    srand(time(NULL));
    int count = 0;
    float mean_damage = 0;
    for (int i = 0; i < 100; i++)
    {
        mean_damage += berserk.get_health();
        Assasin.Attack(berserk);
        mean_damage -= berserk.get_health();
    }
    mean_damage /= 100;
    EXPECT_NEAR(mean_damage, 60,25);
        
}
TEST(CharacterListTests, ctors)
{
    CharacterList cl1;
    EXPECT_EQ(cl1.size(), 0);

    Character characterList[CAPACITY] = {Character::createKnight(350, 10, 60), Character::createAssasin(350, 10, 60),Character::createBerserk(350, 10, 60)};
    CharacterList cl2 = CharacterList(characterList,3);
    EXPECT_EQ(cl2.size(), 3);
}
TEST(CharacterListTests, operators)
{
    CharacterList cl;

    Character knight = Character::createKnight(350, 10, 60);
    Character Assasin = Character::createAssasin(350, 10, 60);
    Character Berserk = Character::createBerserk(350, 10, 60);

    cl[1] = knight;
    cl[2] = Assasin;
    cl[3] = Berserk;

    EXPECT_EQ(cl[3].get_type(), Berserk.get_type());

}
TEST(CharacterListTests, insert)
{
    Character characterList[CAPACITY];

    Character knight = Character::createKnight(350, 10, 60);
    Character Assasin = Character::createAssasin(350, 10, 60);
    Character Berserk = Character::createBerserk(350, 10, 60);

    characterList[0] = knight;
    characterList[1] = Assasin;
    characterList[2] = Berserk;
    CharacterList cl = CharacterList(characterList, 3);
    cl.insert(1, Character::createKnight(500, 20, 160));
   
    EXPECT_THROW(cl.insert(11, knight), runtime_error);
    EXPECT_EQ(cl[0].get_type(), knight.get_type());
    EXPECT_EQ(cl[1].get_type(), knight.get_type());
    EXPECT_EQ(cl[2].get_type(), Assasin.get_type());
    EXPECT_EQ(cl[3].get_type(), Berserk.get_type());

}

TEST(CharacterListTests, remove)
{
    Character characterList[CAPACITY];

    Character knight = Character::createKnight(350, 10, 60);
    Character Assasin = Character::createAssasin(350, 10, 60);
    Character Berserk = Character::createBerserk(350, 10, 60);

    characterList[0] = knight;
    characterList[1] = Assasin;
    characterList[2] = Berserk;
    CharacterList cl = CharacterList(characterList, 3);
    cl.remove(1);
    EXPECT_EQ(cl[1].get_type(), Type:: Berserk);
    EXPECT_THROW(cl.remove(-1), runtime_error);
    EXPECT_THROW(cl.remove(10), runtime_error);
}

TEST(CharacterListTests, search_strongest)
{
    Character characterList[CAPACITY];

    Character knight = Character::createKnight(350, 10, 60);
    Character Assasin = Character::createAssasin(350, 10, 90);
    Character Berserk = Character::createBerserk(350, 10, 60);

    characterList[0] = knight;
    characterList[1] = Assasin;
    characterList[2] = Berserk;
    CharacterList cl = CharacterList(characterList, 3);
    int index = cl.search_strongest();
    EXPECT_EQ(cl[index].get_type(), Type::Assasin);

}