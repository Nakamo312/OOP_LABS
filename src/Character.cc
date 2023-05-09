#include <Character/Character.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <iostream> 
using namespace character;
using namespace std;



//-------------------------------------------------------------------------------------------
Character::Character() : _type(Type::Knight), health(300), armor(5), damage(56), abilityChance(character:: KnightAbilityChance), abilityScale(1), dodge(0)
{ 
	
}

Character:: Character(const Type type, const float health, const float armor, const float damage) : _type(type), health(health), armor(armor), damage(damage), abilityScale(1), dodge(0), abilityChance(0)
{
	if (type == Type::Knight)
	{
		abilityChance = character::KnightAbilityChance;
	}
	else if (type == Type::Assasin)
	{
		abilityChance = character::AssasinAbilityChance;
	}
	else if (type == Type::Berserk)
	{
		abilityChance = character:: BerserkAbilityChance;
	}
}

Character Character::createKnight(const float health, const float armor, const float damage)
{
	return Character(Type::Knight, health, armor, damage);
}

Character Character::createAssasin(const float health, const float armor, const float damage)
{
	return Character(Type::Assasin, health, armor, damage);
}
	
Character Character::createBerserk(const float health, const float armor, const float damage)
{
	return Character(Type::Berserk, health, armor, damage);
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
float Character::get_health() const
{
	return health;
}

float Character::get_armor() const
{
	return armor;
}

float Character::get_damage() const
{
	return damage;
}

int Character::get_abilityChance() const
{
	return abilityChance;
}
Type Character::get_type() const
{
	return _type;
}
void Character::set_health(float _health)
{
	health = _health;
}

void Character::set_armor(float _armor)
{
	armor = _armor;
}

void Character::set_damage(float _damage)
{
	damage = _damage;
}

//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
float Character:: CalcDamage() const
{
	if (_type == Type::Berserk)
	{
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			return damage * 3;
		}
		return damage;
	}
	return damage;
}
void Character::Attack(Character& otherHero) const
{
	
	otherHero.takeDamage(*this);
	if (_type == Type::Assasin)
	{
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			Attack(otherHero);
		}
	}
}
void Character::takeDamage(const Character& otherHero)
{

	if (_type == Type::Knight)
	{
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			health -=  ((otherHero.CalcDamage() - otherHero.CalcDamage() *(armor/100))/ 2);
		}
		else
		{
			health -=  (otherHero.CalcDamage() - otherHero.CalcDamage() *  (armor / 100));
		}
	}
	else if (_type == Type::Assasin)
	{
		if (dodge)
		{
			health -=  ((otherHero.CalcDamage() - otherHero.CalcDamage() *  (armor / 100)) * 0);
		}
		else
		{
			health -=  (otherHero.CalcDamage() - otherHero.CalcDamage() *  (armor / 100));
		}
	}
	else
	{
		health -=  (otherHero.CalcDamage() - otherHero.CalcDamage() * (armor / 100));
	}
}

void Character:: ability()
{
	if (_type == Type::Knight)
	{
		armor = (1.25f * armor) + 2;
		damage = (0.65f * damage);
	}
	else if (_type == Type::Assasin)
	{
		dodge = 1;
	}
	else if (_type == Type::Berserk)
	{
		armor =  (0.5f * armor) + 1;
		damage =  (1.5f * damage);
		abilityScale = 3;
	}
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
CharacterList::CharacterList() : _size(0)
{

}
CharacterList::CharacterList(Character _character[], int _size) {
	this->_size = _size;
	for (int i = 0; i <= _size; i++) 
	{
		_characters[i] = Character(_character[i].get_type(), _character[i].get_health(), _character[i].get_armor(), _character[i].get_damage());
	}

}
int CharacterList::size() const
{
	return _size;
}

void CharacterList::insert(int index, Character ch) {
	if (index >= CAPACITY || index < 0) {
		throw runtime_error("error1");
	}
	for (int i = _size; i >= index; --i) {
		_characters[i] = _characters[i - 1];

	} ++_size;
	_characters[index] = ch;
}

void CharacterList::remove(int index) {
	if (index >= CAPACITY || index < 0) {
		throw runtime_error("error1");
	}
	for (int i = index; i < _size - 1; ++i) {
		_characters[i] = _characters[i + 1];
	}  --_size;
}

Character& CharacterList::operator[](int index)  {
	if (index >= CAPACITY || index < 0) {
		throw runtime_error("error1");
	}
	return _characters[index];
}

int CharacterList::search_strongest() const
{
	float max_damage = 0.f;
	int index = 0;
	for (int i = 0; i < _size - 1; i++)
	{
		if (_characters[i].get_damage() > max_damage)
		{
			max_damage = _characters[i].get_damage();
			index = i;
		}
	}
	return index;
}
//-------------------------------------------------------------------------------------------