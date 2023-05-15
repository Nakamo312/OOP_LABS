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

CharacterPtr Character::createKnight(const float health, const float armor, const float damage)
{
	return new Character(Type::Knight, health, armor, damage);
}

CharacterPtr Character::createAssasin(const float health, const float armor, const float damage)
{
	return new Character(Type::Assasin, health, armor, damage);
}
	
CharacterPtr Character::createBerserk(const float health, const float armor, const float damage)
{
	return new Character(Type::Berserk, health, armor, damage);
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
CharacterPtr Character::clone() const 
{
	return new Character(_type, health,armor,damage);
}

//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
CharacterList::CharacterList() : _size(0), _characters(nullptr)
{

}
CharacterList::CharacterList(const CharacterList& other) : _characters(new CharacterPtr[other._size]),_size(other._size)
{
	for (int i = 0; i < _size; ++i)
	{
		_characters[i] = other[i]->clone();
	}
}

int CharacterList:: size() const
{
	return _size;
}

void CharacterList::insert(CharacterPtr ch, int index)
{	

		auto new_characters = new CharacterPtr[_size + 1];
		for (int i = 0; i <= _size; ++i) 
		{
			if (i == index)
			{
				new_characters[i] = ch;
			}
			else if (i < index)
			{
				new_characters[i] = _characters[i];
			}
			else
			{
				new_characters[i] = _characters[i - 1];
			}
		} 
		delete[] _characters;
		_characters = new_characters;
		++_size;


}
void CharacterList::insert(CharacterPtr hero)
{
	auto new_characters = new CharacterPtr[_size + 1];

	for (int i = 0; i < _size; ++i) {
		new_characters[i] = _characters[i];
	}
	new_characters[_size] = hero;

	delete[] _characters;
	_characters = new_characters;

	++_size;

}
void CharacterList::swap(CharacterList& other) {
	std::swap(this->_characters, other._characters);
	std::swap(this->_size, other._size);
}
void CharacterList::remove(CharacterPtr other) 
{
	bool search = false;
	for (int i = 0; i <= _size; ++i)
	{
		if (_characters[i] == other)
		{
			search = true;
			break;
		}
	}
	if (search)
	{
		auto new_characters = new CharacterPtr[_size - 1];
		bool flag = true;
		for (int i = 0; i < _size; ++i)
		{
			if (_characters[i] != other && flag)
			{

				new_characters[i] = _characters[i];
			}
			else
			{
				flag = false;
				new_characters[i] = _characters[i + 1];
			}
		}
		
		delete _characters;
		_characters = new_characters;
		--_size;

	}
	else
	{
		throw runtime_error("[CharacterList::remove()] object not found");
	}

}
CharacterList& CharacterList:: operator=(const CharacterList& rhs) {
	CharacterList copy(rhs);
	copy.swap(*this);
	return *this;
}
CharacterPtr CharacterList::operator[](const int index) const {
	if (index >= _size || index < 0) {
		throw runtime_error("[CharacterList::operator[] ] invalid index");
	}
	return _characters[index];
}
CharacterList::~CharacterList() {
	for (int i = 0; i < _size; ++i) {
		delete _characters[i];
	}
	delete[] _characters;
}

int CharacterList::index_of_strongest_hero() const
{
	float max_damage = 0.f;
	int index = 0;
	for (int i = 0; i < _size; ++i)
	{
		if (_characters[i]->get_damage() > max_damage)
		{
			max_damage = _characters[i]->get_damage();
			index = i;
		}
	}
	return index;
}
//-------------------------------------------------------------------------------------------




